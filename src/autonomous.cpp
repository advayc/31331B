#include "autonomous.h"
#include "chassis.h"
#include "drive.h"
#include <cmath>

namespace Autonomous {
    // Starting position tracking
    lemlib::Pose startingPose = {0, 0, 0};
    
    void initialize() {
        // Automatically reset position and heading
        resetPosition();
    }
    
    void basicRoutine() {
        // Automatically reset position at start
        resetPosition();
        
        // Simple timed autonomous routine
        // Move forward at 50% speed for 3 seconds
        Drive::moveForward(64, 3000);  // 50% of 127 = ~64
        
        // Small pause
        pros::delay(500);
        
        // Turn right 90 degrees (adjust time as needed for your robot)
        Drive::turnRight(50, 800);  // Adjust time for 90 degree turn
        
        // Small pause
        pros::delay(500);
        
        // Move forward a bit (1 second at 50% speed)
        Drive::moveForward(64, 1000);
        
        // Small pause
        pros::delay(500);
        
        // Move back to roughly starting area
        Drive::moveBackward(64, 1000);
        
        // Turn back left to original heading
        Drive::turnLeft(50, 800);
        
        // Move back to start
        Drive::moveBackward(64, 3000);
    }
    
    void skillsRoutine() {
        // Extended routine for skills challenge
        resetPosition();
        
        // Simple square pattern with timed movements
        for (int i = 0; i < 4; i++) {
            Drive::moveForward(80, 2000);  // 2 seconds forward
            pros::delay(200);
            Drive::turnRight(60, 600);     // Turn right
            pros::delay(200);
        }
    }
    
    void testRoutine() {
        // Simple test routine
        resetPosition();
        
        Drive::moveForward(50, 1000);   // 1 second forward
        pros::delay(500);
        Drive::moveBackward(50, 1000);  // 1 second back
        pros::delay(500);
        Drive::turnRight(50, 400);      // Quick right turn
        pros::delay(500);
        Drive::turnLeft(50, 400);       // Quick left turn back
    }
    
    // Helper functions for easy autonomous programming (simplified)
    void driveForward(float distance, int timeout) {
        // Simple forward movement based on time estimation
        // Roughly 1 second = ~12 inches at medium speed
        int time_estimate = (int)(distance * 83);  // Rough time calculation
        Drive::moveForward(80, time_estimate);
    }
    
    void driveBackward(float distance, int timeout) {
        int time_estimate = (int)(distance * 83);
        Drive::moveBackward(80, time_estimate);
    }
    
    void turnRight(float degrees, int timeout) {
        // Rough time estimation for degrees (adjust for your robot)
        int time_estimate = (int)(degrees * 9);  // ~9ms per degree
        Drive::turnRight(60, time_estimate);
    }
    
    void turnLeft(float degrees, int timeout) {
        int time_estimate = (int)(degrees * 9);
        Drive::turnLeft(60, time_estimate);
    }
    
    void turnToHeading(float heading, int timeout) {
        // Simple turn to heading (not precise without IMU)
        Drive::turnRight(50, 1000);  // Basic turn
    }
    
    void resetPosition() {
        // Reset chassis position and motor encoders
        Chassis::setPose(0, 0, 0);
        Drive::resetEncoders();
        startingPose = {0, 0, 0};
    }
    
    void returnToStart() {
        // Simple return to start (not precise without odometry)
        // This is a basic implementation
        pros::delay(500);
    }
}
