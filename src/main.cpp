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
    while (true) {
        // Left stick only control - full speed capability
        int forward = Controller::getLeftY();  // Left stick Y for forward/backward
        int turn = Controller::getLeftX();     // Left stick X for turning
        
        // Use left stick control for full speed driving
        Drive::leftStickControl(forward, turn);
        
        // Button controls
        if (Controller::getDigitalNewPress(pros::E_CONTROLLER_DIGITAL_A)) {
            // Reset motor encoders and position when A is pressed
            Drive::resetEncoders();
            Chassis::setPose(0, 0, 0);
        }
        
        if (Controller::getDigitalNewPress(pros::E_CONTROLLER_DIGITAL_B)) {
            // Change brake mode when B is pressed
            static bool coastMode = true;
            coastMode = !coastMode;
            Drive::setBrakeMode(coastMode ? pros::MotorBrake::coast : pros::MotorBrake::brake);
        }
        
        pros::delay(10);
    }
}