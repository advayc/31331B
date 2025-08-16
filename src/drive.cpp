#include "drive.h"
#include <cstdlib>  // for abs()

namespace Drive {
    // Motor groups - matching Python VEX configuration
    // Left side: port 1 (reversed), port 2 (normal), port 3 (normal)
    pros::MotorGroup leftMotors({-1, 2, 3}, pros::MotorGearset::blue);
    // Right side: port 4 (normal), port 5 (reversed), port 6 (reversed)  
    pros::MotorGroup rightMotors({4, -5, -6}, pros::MotorGearset::blue);
    
    void initialize() {
        // Set brake mode for better control
        setBrakeMode(pros::MotorBrake::coast);
        resetEncoders();
    }
    
    void leftStickControl(int forward, int turn) {
        // Left stick only control - full speed capability
        // Apply deadband to eliminate drift
        
        int left_speed = forward + turn;
        int right_speed = forward - turn;
        
        // Clamp to full motor range [-127, 127]
        if (left_speed > 127) left_speed = 127;
        if (left_speed < -127) left_speed = -127;
        if (right_speed > 127) right_speed = 127;
        if (right_speed < -127) right_speed = -127;
        
        // Apply reverse direction to match Python VEX behavior
        leftMotors.move(-left_speed);
        rightMotors.move(-right_speed);
    }
    
    void arcade(int forward, int turn) {
        leftStickControl(forward, turn);
    }
    
    void tank(int left, int right) {
        // Tank drive - direct left/right control
        leftMotors.move(-left);   // Reverse to match Python behavior
        rightMotors.move(-right); // Reverse to match Python behavior
    }
    
    void stop() {
        leftMotors.move(0);
        rightMotors.move(0);
    }
    
    void setBrakeMode(pros::MotorBrake mode) {
        leftMotors.set_brake_mode_all(mode);
        rightMotors.set_brake_mode_all(mode);
    }
    
    void resetEncoders() {
        leftMotors.tare_position();
        rightMotors.tare_position();
    }
    
    // Timed movement functions for autonomous
    void moveForward(int speed, int time_ms) {
        leftMotors.move(-speed);   // Reverse for forward movement
        rightMotors.move(-speed);  // Reverse for forward movement
        pros::delay(time_ms);
        stop();
    }
    
    void moveBackward(int speed, int time_ms) {
        leftMotors.move(speed);    // Normal for backward movement
        rightMotors.move(speed);   // Normal for backward movement
        pros::delay(time_ms);
        stop();
    }
    
    void turnRight(int speed, int time_ms) {
        leftMotors.move(-speed);   // Left motors forward
        rightMotors.move(speed);   // Right motors backward
        pros::delay(time_ms);
        stop();
    }
    
    void turnLeft(int speed, int time_ms) {
        leftMotors.move(speed);    // Left motors backward
        rightMotors.move(-speed);  // Right motors forward
        pros::delay(time_ms);
        stop();
    }
}
