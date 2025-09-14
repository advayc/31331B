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
    bool tuningMode = false;
    bool adjustAngular = false; // false = linear, true = angular
    int whichGain = 0; // 0=kP,1=kI,2=kD
    float step = 0.5f;

    while (true) {
        // Left stick only control - full speed capability
        int forward = Controller::getLeftY();  // Left stick Y for forward/backward
        int turn = Controller::getLeftX();     // Left stick X for turning
        
        // Use left stick control for full speed driving
        Drive::leftStickControl(forward, turn);
        
        // Button controls
        if (Controller::getDigitalNewPress(pros::E_CONTROLLER_DIGITAL_L1)) {
            tuningMode = !tuningMode;
            Controller::rumble(tuningMode ? "." : "-");
        }

        if (tuningMode) {
            // Switch controller (linear vs angular)
            if (Controller::getDigitalNewPress(pros::E_CONTROLLER_DIGITAL_L2)) {
                adjustAngular = !adjustAngular;
            }

            // Select gain component with dpad left/right
            if (Controller::getDigitalNewPress(pros::E_CONTROLLER_DIGITAL_LEFT)) {
                whichGain = (whichGain + 2) % 3;
            }
            if (Controller::getDigitalNewPress(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
                whichGain = (whichGain + 1) % 3;
            }

            // Get current gains
            float kP, kI, kD;
            if (adjustAngular) Chassis::getAngularGains(kP, kI, kD);
            else Chassis::getLinearGains(kP, kI, kD);

            // Adjust with up/down
            if (Controller::getDigitalNewPress(pros::E_CONTROLLER_DIGITAL_UP)) {
                if (whichGain == 0) kP += step;
                else if (whichGain == 1) kI += step;
                else kD += step;
            }
            if (Controller::getDigitalNewPress(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                if (whichGain == 0) kP = std::max(0.0f, kP - step);
                else if (whichGain == 1) kI = std::max(0.0f, kI - step);
                else kD = std::max(0.0f, kD - step);
            }

            // Apply only if gains actually changed
            static float lastLin[3] = {-1,-1,-1};
            static float lastAng[3] = {-1,-1,-1};
            float* last = adjustAngular ? lastAng : lastLin;
            bool changed = (whichGain==0 && last[0]!=kP) || (whichGain==1 && last[1]!=kI) || (whichGain==2 && last[2]!=kD);
            if (changed) {
                if (adjustAngular) {
                    Chassis::setAngularGains(kP, kI, kD);
                    lastAng[0]=kP; lastAng[1]=kI; lastAng[2]=kD;
                } else {
                    Chassis::setLinearGains(kP, kI, kD);
                    lastLin[0]=kP; lastLin[1]=kI; lastLin[2]=kD;
                }
                Chassis::rebuild();
            }

            // Show current values on controller screen
            char buf[32];
            snprintf(buf, sizeof(buf), "%s PID", adjustAngular ? "Ang" : "Lin");
            Controller::setText(0, 0, buf);
            snprintf(buf, sizeof(buf), "P:%.1f I:%.1f", kP, kI);
            Controller::setText(1, 0, buf);
            snprintf(buf, sizeof(buf), "D:%.1f [%-1s]", kD, whichGain==0?"P":whichGain==1?"I":"D");
            Controller::setText(2, 0, buf);
        }

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
        
        if (!tuningMode && Controller::getDigitalNewPress(pros::E_CONTROLLER_DIGITAL_X)) {
            // Test autonomous routine when X is pressed
            Autonomous::testRoutine();
        }
        
        pros::delay(10);
    }
}