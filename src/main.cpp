#include "main.h"

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Motor groups matching Python VEX code configuration
// Left side: port 1 (reversed), port 2 (normal), port 3 (normal)
pros::MotorGroup leftMotors({-1, 2, 3}, pros::MotorGearset::blue);
// Right side: port 4 (normal), port 5 (reversed), port 6 (reversed)  
pros::MotorGroup rightMotors({4, -5, -6}, pros::MotorGearset::blue);

// All sensor & LemLib related (PID/odometry) code commented out per request
/*
// Inertial Sensor on port 10
pros::Imu imu(10);

// tracking wheels
pros::Rotation horizontalEnc(20);    // horizontal tracking wheel encoder (not reversed)
pros::Rotation verticalEnc(-11);      // vertical tracking wheel encoder (reversed)

lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_275, -5.75); // 2.75" diameter, 5.75" offset
lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_275, -2.5);      // 2.75" diameter, 2.5" offset
*/

/* PID & chassis setup (commented out)
lemlib::Drivetrain drivetrain(&leftMotors,
                              &rightMotors,
                              10,
                              lemlib::Omniwheel::NEW_325,
                              360,
                              2);

lemlib::ControllerSettings linearController(10,0,3,3,1,100,3,500,20);
lemlib::ControllerSettings angularController(2,0,10,3,1,100,3,500,0);
lemlib::OdomSensors sensors(&vertical,nullptr,&horizontal,nullptr,&imu);
lemlib::ExpoDriveCurve throttleCurve(3,10,1.019);
lemlib::ExpoDriveCurve steerCurve(3,10,1.019);
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);
*/

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    // chassis.calibrate(); // (disabled) calibrate sensors

    // the default rate is 50. however, if you need to change the rate, you
    // can do the following.
    // lemlib::bufferedStdout().setRate(...);
    // If you use bluetooth or a wired connection, you will want to have a rate of 10ms

    // for more information on how the formatting for the loggers
    // works, refer to the fmtlib docs

    // thread to for brain screen and position logging
    // Position logging task disabled because PID/odometry commented out
    // pros::Task screenTask([&]() { ... });
}

/**
 * Runs while the robot is disabled
 */
void disabled() {}

/**
 * runs after initialize if the robot is connected to field control
 */
void competition_initialize() {}

// get a path used for pure pursuit
// this needs to be put outside a function
//ASSET(example_txt); // '.' replaced with "_" to make c++ happy

/**
 * Runs during auto
 *
 * This is an example autonomous routine which demonstrates a lot of the features LemLib has to offer
 */
void autonomous() {
    // Autonomous disabled (PID & chassis code commented out).
    // Add manual timed or open-loop routines here if desired.
}

/**
 * Runs in driver control
 */
void opcontrol() {
    // Driver control loop - matches Python drive_task() function
    while (true) {
        // Python: forward = controller.axis3.position()  # Forward/backward control
        // Python: turn = controller.axis4.position()     # Left/right turn control
        // PROS axis3 = left Y, axis4 = right X (same as Python VEX)
        int forward = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);   // axis3
        int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);     // axis4

        // Python: left_speed = forward + turn
        // Python: right_speed = forward - turn
        int left_speed = forward + turn;
        int right_speed = forward - turn;

        // Python spins all motors in REVERSE direction, so we negate the speeds
        // Using motor groups instead of individual motors
        leftMotors.move(-left_speed);    // REVERSE = negate speed for all left motors
        rightMotors.move(-right_speed);  // REVERSE = negate speed for all right motors

        // Python: sleep(10) 
        pros::delay(10);
    }
}