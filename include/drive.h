#pragma once

#include "pros/motor_group.hpp"

// Header contract:
// - This header declares the Drive interface and extern motor groups.
// - It is intended to be included by users (e.g., other modules and main).
// - The implementation file does not include this header to avoid redundant self-include.

namespace Drive {
    // Motor groups
    extern pros::MotorGroup leftMotors;
    extern pros::MotorGroup rightMotors;
    
    // Drive functions
    void initialize();
    void leftStickControl(int forward, int turn);  // Left stick only control
    void arcade(int forward, int turn);
    void tank(int left, int right);
    void stop();
    
    // Timed movement functions for autonomous
    void moveForward(int speed, int time_ms);
    void moveBackward(int speed, int time_ms);
    void turnRight(int speed, int time_ms);
    void turnLeft(int speed, int time_ms);
    
    // Motor control utilities
    void setBrakeMode(pros::MotorBrake mode);
    void resetEncoders();
}
