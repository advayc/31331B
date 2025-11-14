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
    Autonomous::basicRoutine();
}

/**
 * Runs in driver control
 */
void opcontrol() {
    Drive::initialize();
    
    while (true) {
        // D-pad for arcade drive
        int forward = 0;
        int turn = 0;
        if (Controller::getDigital(pros::E_CONTROLLER_DIGITAL_UP)) forward = 127;
        if (Controller::getDigital(pros::E_CONTROLLER_DIGITAL_DOWN)) forward = -127;
        if (Controller::getDigital(pros::E_CONTROLLER_DIGITAL_LEFT)) turn = -127;
        if (Controller::getDigital(pros::E_CONTROLLER_DIGITAL_RIGHT)) turn = 127;
        
        // Left joystick Y for conveyor motor 7, right joystick Y for conveyor motor 8
        int conveyor_7 = Controller::getLeftY();
        int conveyor_8 = Controller::getRightY();
        
        int left_speed = forward + turn;
        int right_speed = forward - turn;
        
        Drive::setDriveSpeeds(left_speed, right_speed);
        Drive::setConveyorSpeeds(conveyor_7, conveyor_8);
        
        pros::delay(10);
    }
}