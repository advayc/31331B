#pragma once

#include "pros/motor_group.hpp"

namespace Drive {
    // Motor groups
    extern pros::MotorGroup leftMotors;
    extern pros::MotorGroup rightMotors;
    
    // Drive functions
    void initialize();
    void leftStickControl(int forward, int turn);  // New left stick only control
    void arcade(int forward, int turn);
    void tank(int left, int right);
    void stop();
    
    // Motor control utilities
    void setBrakeMode(pros::MotorBrake mode);
    void resetEncoders();
}
