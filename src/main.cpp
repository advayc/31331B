#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    // Initialize all subsystems
    Drive::initialize();
    Controller::initialize();
    Sensors::initialize();
    Chassis::initialize();
    Display::initialize();
    Autonomous::initialize();
    
    // Start display task for brain screen
    Display::startDisplayTask();
}

/**
 * Runs while the robot is disabled
 */
void disabled() {}

/**
 * runs after initialize if the robot is connected to field control
 */
void competition_initialize() {}


/**
 * Runs during autonomous period
 */
void autonomous() {
    // Run the main autonomous routine
    //Autonomous::basicRoutine(); // pathjerry path

    // Autonomous::testRoutine(); // PID test routine

    //Autonomous::skills15p(); // 15 point skills routine

    Autonomous::AWP(); // move forward one inch

    // Autonomous::rightMatch(); // jerry right routine
    // Autonomous::leftMatch(); // jerry left routine

}

/**
 * Runs in driver control
 */
void opcontrol() {
    Drive::initialize();
    
    while (true) {
        // Left joystick for arcade drive
        int forward = Controller::getLeftY();  // Left stick Y for forward/backward
        int turn = Controller::getLeftX();     // Left stick X for turning
        
        // Right joystick controls intake (motor on port 11)
        int intake = Controller::getRightY(); // Right stick Y for intake control

        // D-pad up/down control the second conveyor (motor on port 12)
        int conveyor2_speed = 0;
        if (Controller::getDigital(pros::E_CONTROLLER_DIGITAL_UP)) {
            conveyor2_speed = 127;
        } else if (Controller::getDigital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            conveyor2_speed = -127;
        }

        int left_speed = forward - turn;
        int right_speed = forward + turn;

        Drive::setDriveSpeeds(left_speed, right_speed);
        // Motor on port 11 -> intake joystick
        Drive::conveyor_motor_1.move(intake);
        // Motor on port 12 -> up/down arrows
        Drive::conveyor_motor_2.move(conveyor2_speed);
        
        // Matchload piston controls (down on R1/R2, up on L1/L2)
        if (Controller::getDigital(pros::E_CONTROLLER_DIGITAL_R1) || Controller::getDigital(pros::E_CONTROLLER_DIGITAL_R2)) {
            Drive::setMatchloadPiston(false);  // Down
        } else if (Controller::getDigital(pros::E_CONTROLLER_DIGITAL_L1) || Controller::getDigital(pros::E_CONTROLLER_DIGITAL_L2)) {
            Drive::setMatchloadPiston(true); // Up
        }
        
        pros::delay(10);
    }
}