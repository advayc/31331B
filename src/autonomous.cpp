#include "autonomous.h"
#include "chassis.h"
#include <cmath>

namespace Autonomous {
    // Starting position tracking
    lemlib::Pose startingPose = {0, 0, 0};
    
    void initialize() {
        // Set starting position
        Chassis::setPose(0, 0, 0);
        startingPose = Chassis::getPose();
    }
    
    void basicRoutine() {
        // Reset position to ensure accuracy
        resetPosition();
        
        // Move forward 1 foot (12 inches)
        driveForward(12);
        
        // Turn right 90 degrees
        turnRight(90);
        
        // Move forward 6 inches
        driveForward(6);
        
        // Return to starting position and heading
        returnToStart();
    }
    
    void skillsRoutine() {
        // Extended routine for skills challenge
        resetPosition();
        
        // Example: Square pattern
        for (int i = 0; i < 4; i++) {
            driveForward(24);    // 2 feet forward
            turnRight(90);       // Turn right 90 degrees
        }
        
        returnToStart();
    }
    
    void testRoutine() {
        // Simple test routine
        resetPosition();
        
        driveForward(6);     // 6 inches forward
        driveBackward(6);    // 6 inches back
        turnRight(90);       // Turn right
        turnLeft(90);        // Turn back
    }
    
    // Helper functions for easy autonomous programming
    void driveForward(float distance, int timeout) {
        lemlib::Pose currentPose = Chassis::getPose();
        float targetX = currentPose.x + distance * std::cos(currentPose.theta * M_PI / 180.0);
        float targetY = currentPose.y + distance * std::sin(currentPose.theta * M_PI / 180.0);
        
        Chassis::moveToPoint(targetX, targetY, timeout, true, 127);
        Chassis::waitUntilDone();
    }
    
    void driveBackward(float distance, int timeout) {
        lemlib::Pose currentPose = Chassis::getPose();
        float targetX = currentPose.x - distance * std::cos(currentPose.theta * M_PI / 180.0);
        float targetY = currentPose.y - distance * std::sin(currentPose.theta * M_PI / 180.0);
        
        Chassis::moveToPoint(targetX, targetY, timeout, false, 127);
        Chassis::waitUntilDone();
    }
    
    void turnRight(float degrees, int timeout) {
        lemlib::Pose currentPose = Chassis::getPose();
        float targetHeading = currentPose.theta + degrees;
        
        Chassis::turnToHeading(targetHeading, timeout, 127);
        Chassis::waitUntilDone();
    }
    
    void turnLeft(float degrees, int timeout) {
        lemlib::Pose currentPose = Chassis::getPose();
        float targetHeading = currentPose.theta - degrees;
        
        Chassis::turnToHeading(targetHeading, timeout, 127);
        Chassis::waitUntilDone();
    }
    
    void turnToHeading(float heading, int timeout) {
        Chassis::turnToHeading(heading, timeout, 127);
        Chassis::waitUntilDone();
    }
    
    void resetPosition() {
        Chassis::setPose(0, 0, 0);
        startingPose = {0, 0, 0};
        // Reset motor encoders through Drive module
        // No external sensors to reset
    }
    
    void returnToStart() {
        // Move back to starting position
        Chassis::moveToPose(startingPose.x, startingPose.y, startingPose.theta, 4000, true, 127);
        Chassis::waitUntilDone();
    }
}
