#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"

namespace Drive {
    // Motor groups - matching Python VEX configuration
    // Left side: port 1 (reversed), port 2 (normal), port 3 (normal)
    pros::MotorGroup leftMotors({-1, 2, 3}, pros::MotorGearset::blue);
    // Right side: port 4 (normal), port 5 (reversed), port 6 (reversed)  
    pros::MotorGroup rightMotors({4, -5, -6}, pros::MotorGearset::blue);
    
    // Conveyor motors
    pros::Motor conveyor_motor_1(7, pros::v5::MotorGears::blue);
    pros::Motor conveyor_motor_2(8, pros::v5::MotorGears::green);
    
    void initialize() {
        // Set brake mode for better control
        leftMotors.set_brake_mode(pros::MotorBrake::coast);
        rightMotors.set_brake_mode(pros::MotorBrake::coast);
        leftMotors.tare_position();
        rightMotors.tare_position();
        
        // Set reversed for conveyor motor 2
        conveyor_motor_2.set_reversed(true);
    }
    
    void setDriveSpeeds(int left_speed, int right_speed) {
        // Apply reverse direction to match Python VEX behavior
        leftMotors.move(-left_speed);
        rightMotors.move(-right_speed);
    }
    
    void setConveyorSpeeds(int speed1, int speed2) {
        // Conveyor motors controlled separately
        conveyor_motor_1.move(speed1);  // Motor 7 (not reversed)
        conveyor_motor_2.move(speed2); // Motor 8 (reversed, so move(speed2) = REVERSE direction)
    }
    
    void resetEncoders() {
        leftMotors.tare_position();
        rightMotors.tare_position();
    }
}
