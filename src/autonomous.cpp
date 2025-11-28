#include "lemlib/api.hpp"
#include "pros/rtos.hpp"
#include <cmath>
#include "main.h"
#include "chassis.h"
#include "drive.h"
#include "autonomous.h"

namespace Autonomous {
    // Starting position management
    lemlib::Pose startingPose = {0, 0, 0};
    
    void initialize() {
        // Set starting position to origin
        setStartingPose(0, 0, 0);
    }
    
    void basicRoutine() {
        // Reset to starting position
        resetToStartingPose();
        
        // Follow the right path
        // Lookahead: 15 inches (adjust based on testing)
        // Timeout: 15000ms (15 seconds)
        // Forwards: true (robot follows path going forward)
        Chassis::follow(right_match_txt, 15, 15000, true);
        Chassis::waitUntilDone();
    }

    // Separate match routines using static assets
    void leftMatch() {
        resetToStartingPose();
        // Follow the left-side match path
        Chassis::follow(left_match_txt, 15, 15000, true);
        Chassis::waitUntilDone();
    }

    void rightMatch() {
        resetToStartingPose();
        // Follow the right-side match path
        Chassis::follow(right_match_txt, 15, 15000, true);
        Chassis::waitUntilDone();
    }
    
    void AWP() {
        // move forward two inches
        driveDistance(2.0);
        waitUntilDone();
    }
    
    void testRoutine() {
        // Test PID precision
        resetToStartingPose();
        
        // Test forward movement
        driveDistance(12);  // 12 inches forward
        waitUntilDone();
        waitMS(1000);
        
        // Test backward movement
        driveDistance(-12); // 12 inches backward
        waitUntilDone();
        waitMS(1000);
        
        // Test turning
        turnToHeading(90);  // Turn to 90 degrees
        waitUntilDone();
        waitMS(1000);
        
        turnToHeading(0);   // Turn back to 0 degrees
        waitUntilDone();
    }

    void skills15p () {
        pros::delay(1000);
        Drive::conveyor_motor_2.move(50);
        pros::delay(5000);
        Drive::conveyor_motor_2.move(0);
    }
    
    // PID-based movement functions with precise positioning
    void driveToPoint(float x, float y, int timeout, bool forwards) {
        Chassis::moveToPoint(x, y, timeout, forwards, 127);
    }
    
    void driveToPose(float x, float y, float heading, int timeout, bool forwards) {
        Chassis::moveToPose(x, y, heading, timeout, forwards, 127);
    }
    
    void turnToHeading(float heading, int timeout) {
        Chassis::turnToHeading(heading, timeout, 127);
    }
    
    void driveDistance(float distance, int timeout, bool forwards) {
        lemlib::Pose currentPose = getCurrentPose();
        
        // Calculate target position based on current heading
        float heading_rad = currentPose.theta * M_PI / 180.0;
        float target_x = currentPose.x + distance * std::cos(heading_rad);
        float target_y = currentPose.y + distance * std::sin(heading_rad);
        
        if (distance >= 0) {
            driveToPoint(target_x, target_y, timeout, true);
        } else {
            driveToPoint(target_x, target_y, timeout, false);
        }
    }
    
    // Relative movement functions
    void driveForward(float inches) {
        driveDistance(inches, 4000, true);
        waitUntilDone();
    }
    
    void driveBackward(float inches) {
        driveDistance(-inches, 4000, false);
        waitUntilDone();
    }
    
    void turnRight(float degrees) {
        lemlib::Pose currentPose = getCurrentPose();
        float targetHeading = currentPose.theta + degrees;
        turnToHeading(targetHeading);
        waitUntilDone();
    }
    
    void turnLeft(float degrees) {
        lemlib::Pose currentPose = getCurrentPose();
        float targetHeading = currentPose.theta - degrees;
        turnToHeading(targetHeading);
        waitUntilDone();
    }
    
    void strafeRight(float inches) {
        // For future mecanum implementation
        lemlib::Pose currentPose = getCurrentPose();
        float heading_rad = (currentPose.theta + 90) * M_PI / 180.0;
        float target_x = currentPose.x + inches * std::cos(heading_rad);
        float target_y = currentPose.y + inches * std::sin(heading_rad);
        driveToPoint(target_x, target_y);
        waitUntilDone();
    }
    
    void strafeLeft(float inches) {
        strafeRight(-inches);
    }
    
    // Position and pose management
    void setStartingPose(float x, float y, float heading) {
        startingPose = {x, y, heading};
        Chassis::setPose(x, y, heading);
    }
    
    void resetToStartingPose() {
        Chassis::setPose(startingPose.x, startingPose.y, startingPose.theta);
    }
    
    void resetPosition() {
        setStartingPose(0, 0, 0);
        Drive::resetEncoders();
    }
    
    lemlib::Pose getCurrentPose() {
        return Chassis::getPose();
    }
    
    // Utility functions
    void waitUntilDone() {
        Chassis::waitUntilDone();
    }
    
    void waitUntilDistance(float distance) {
        Chassis::waitUntil(distance);
    }
    
    void waitMS(int milliseconds) {
        pros::delay(milliseconds);
    }
    
    // PID tuning functions
    void tuneLinearPID() {
        resetPosition();
        
        // Test linear PID - should move exactly 24 inches
        driveDistance(24);
        waitUntilDone();
        waitMS(2000);
        
        // Move back to test accuracy
        driveDistance(-24);
        waitUntilDone();
        
        // Check final position - should be close to (0, 0)
        lemlib::Pose finalPose = getCurrentPose();
        // Display pose for tuning feedback
    }
    
    void tuneAngularPID() {
        resetPosition();
        
        // Test angular PID - should turn exactly 90 degrees
        turnToHeading(90);
        waitUntilDone();
        waitMS(2000);
        
        turnToHeading(180);
        waitUntilDone();
        waitMS(2000);
        
        turnToHeading(270);
        waitUntilDone();
        waitMS(2000);
        
        turnToHeading(0);
        waitUntilDone();
        
        // Check final heading - should be close to 0
        lemlib::Pose finalPose = getCurrentPose();
        // Display pose for tuning feedback
    }
    
    void pidTest() {
        // Comprehensive PID testing routine for path following accuracy
        // Tests linear movement, angular movement, and combined motions
        
        Controller::rumble("-");
        pros::delay(500);
        
        // Test 1: Linear Movement Test (24 inches forward and back)
        Controller::setText(0, 0, "Test 1: Linear");
        resetPosition();
        
        // Forward 24 inches
        driveDistance(24, 3000, true);
        waitUntilDone();
        pros::delay(1000);
        
        // Backward 24 inches
        driveDistance(-24, 3000, true);
        waitUntilDone();
        pros::delay(1000);
        
        Controller::rumble(".");
        pros::delay(2000);
        
        // Test 2: Angular Movement Test (90 degree turns)
        Controller::setText(0, 0, "Test 2: Turns");
        resetPosition();
        
        // Turn right 90 degrees
        turnToHeading(90, 2000);
        waitUntilDone();
        pros::delay(1000);
        
        // Turn back to 0 degrees
        turnToHeading(0, 2000);
        waitUntilDone();
        pros::delay(1000);
        
        // Turn left 90 degrees
        turnToHeading(-90, 2000);
        waitUntilDone();
        pros::delay(1000);
        
        // Turn back to 0 degrees
        turnToHeading(0, 2000);
        waitUntilDone();
        pros::delay(1000);
        
        Controller::rumble("..");
        pros::delay(2000);
        
        // Test 3: Extended Linear Test (20 inches)
        Controller::setText(0, 0, "Test 3: 20in");
        resetPosition();
        
        // Forward 20 inches
        driveDistance(20, 3000, true);
        waitUntilDone();
        pros::delay(1000);
        
        // Backward 20 inches
        driveDistance(-20, 3000, true);
        waitUntilDone();
        pros::delay(1000);
        
        Controller::rumble("...");
        pros::delay(2000);
        
        // Test 4: Full Rotation Test (Angular PID)
        Controller::setText(0, 0, "Test 4: 360");
        resetPosition();
        
        // Turn 90 degrees increments for full rotation
        turnToHeading(90, 2000);
        waitUntilDone();
        pros::delay(500);
        
        turnToHeading(180, 2000);
        waitUntilDone();
        pros::delay(500);
        
        turnToHeading(270, 2000);
        waitUntilDone();
        pros::delay(500);
        
        turnToHeading(0, 2000);
        waitUntilDone();
        pros::delay(1000);
        
        Controller::rumble("----");
        Controller::setText(0, 0, "Tests Done!");
        
        // Display final position error
        lemlib::Pose finalPose = getCurrentPose();
        char buf[32];
        snprintf(buf, sizeof(buf), "X:%.1f Y:%.1f", finalPose.x, finalPose.y);
        Controller::setText(1, 0, buf);
        snprintf(buf, sizeof(buf), "H:%.1f", finalPose.theta);
        Controller::setText(2, 0, buf);
    }
}
