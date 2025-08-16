#include "autonomous.h"
#include "chassis.h"
#include "drive.h"
#include <cmath>

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
        
        // PID-based autonomous routine using precise positioning
        // Move to position (36, 0) - 36 inches forward
        driveToPoint(36, 0);
        waitUntilDone();
        
        // Turn to face 90 degrees (right)
        turnToHeading(90);
        waitUntilDone();
        
        // Move forward 12 inches in the new direction
        driveDistance(12);
        waitUntilDone();
        
        // Move back 12 inches
        driveDistance(-12);
        waitUntilDone();
        
        // Return to starting pose (position and heading)
        resetToStartingPose();
        waitUntilDone();
    }
    
    void skillsRoutine() {
        // Square pattern using precise PID positioning
        resetToStartingPose();
        
        // Define square corners
        float squareSize = 24; // 24 inch square
        
        driveToPose(squareSize, 0, 0);      // Move to (24, 0), face 0°
        waitUntilDone();
        
        driveToPose(squareSize, squareSize, 90);  // Move to (24, 24), face 90°
        waitUntilDone();
        
        driveToPose(0, squareSize, 180);    // Move to (0, 24), face 180°
        waitUntilDone();
        
        driveToPose(0, 0, 270);             // Move to (0, 0), face 270°
        waitUntilDone();
        
        turnToHeading(0);                   // Face original heading
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
}
