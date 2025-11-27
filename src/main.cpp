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
    // Autonomous::skillsRoutine(); // PID square routine
    // Autonomous::testRoutine(); // PID test routine
    Autonomous::skills15p(); // 15 point skills routine
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
        
        // Right joystick for conveyor
        int conveyor = Controller::getRightY(); // Right stick Y for conveyor control
        
        int left_speed = forward + turn;
        int right_speed = forward - turn;
        
        Drive::setDriveSpeeds(left_speed, right_speed);
        Drive::setConveyorSpeed(conveyor);
        
        pros::delay(10);
    }
}