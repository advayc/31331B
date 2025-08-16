#pragma once

#include "pros/motor_group.hpp"

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
