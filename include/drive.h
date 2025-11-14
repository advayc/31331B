#pragma once

#include "pros/motor_group.hpp"
#include "pros/motors.hpp"

// Header contract:
// - This header declares the Drive interface and extern motor groups.
// - It is intended to be included by users (e.g., other modules and main).
// - The implementation file does not include this header to avoid redundant self-include.

namespace Drive {
    // Motor groups for drive
    extern pros::MotorGroup leftMotors;
    extern pros::MotorGroup rightMotors;
    
    // Individual motors for conveyor
    extern pros::Motor conveyor_motor_1;
    extern pros::Motor conveyor_motor_2;
    
    // Drive functions
    void initialize();
    void setDriveSpeeds(int left_speed, int right_speed);
    void setConveyorSpeeds(int speed1, int speed2);
    
    // Motor control utilities
    void resetEncoders();
}
