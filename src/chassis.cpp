#include "chassis.h"
#include "drive.h"
#include "sensors.h"

namespace Chassis {
    // PID and chassis setup for 36:60 drivetrain, 360 RPM
    lemlib::Drivetrain drivetrain(&Drive::leftMotors,
                                  &Drive::rightMotors,
                                  10.5, // track width in inches (adjust based on your robot)
                                  lemlib::Omniwheel::NEW_4, // 4" wheels
                                  360, // drivetrain rpm (matches your specs)
                                  8 // horizontal drift with traction wheels
    );

    // Tuned PID controllers for your drivetrain
    lemlib::ControllerSettings linearController(10, // kP
                                               0,  // kI  
                                               3,  // kD
                                               3,  // anti windup
                                               1,  // small error range (inches)
                                               100, // small error timeout (ms)
                                               3,   // large error range (inches)
                                               500, // large error timeout (ms)
                                               20   // max acceleration (slew)
    );
    
    lemlib::ControllerSettings angularController(2,  // kP
                                                 0,  // kI
                                                 10, // kD
                                                 3,  // anti windup
                                                 1,  // small error range (degrees)
                                                 100, // small error timeout (ms)
                                                 3,   // large error range (degrees)
                                                 500, // large error timeout (ms)
                                                 0    // max acceleration (slew)
    );
    
    // Basic odometry using IMU only (no tracking wheels yet)
    lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1
                               nullptr, // vertical tracking wheel 2  
                               nullptr, // horizontal tracking wheel 1
                               nullptr, // horizontal tracking wheel 2
                               &Sensors::imu // inertial sensor
    );
    
    // Drive curves for smooth control
    lemlib::ExpoDriveCurve throttleCurve(3, 10, 1.019);
    lemlib::ExpoDriveCurve steerCurve(3, 10, 1.019);
    
    // Create chassis instance
    lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);
    
    void initialize() {
        calibrate();
    }
    
    void calibrate() {
        chassis.calibrate();
    }
    
    void moveToPose(float x, float y, float theta, int timeout, bool forwards, float maxSpeed) {
        chassis.moveToPose(x, y, theta, timeout, {.forwards = forwards, .maxSpeed = maxSpeed});
    }
    
    void moveToPoint(float x, float y, int timeout, bool forwards, float maxSpeed) {
        chassis.moveToPoint(x, y, timeout, {.forwards = forwards, .maxSpeed = maxSpeed});
    }
    
    void turnToHeading(float theta, int timeout, float maxSpeed) {
        chassis.turnToHeading(theta, timeout, {.maxSpeed = (int)maxSpeed});
    }
    
    void turnToPoint(float x, float y, int timeout, float maxSpeed) {
        chassis.turnToPoint(x, y, timeout, {.maxSpeed = (int)maxSpeed});
    }
    
    void follow(const char* path, float lookahead, int timeout, bool forwards) {
        // Path following will be implemented when assets are set up
        // chassis.follow(path, lookahead, timeout, forwards);
    }
    
    void waitUntilDone() {
        chassis.waitUntilDone();
    }
    
    void waitUntil(float distance) {
        chassis.waitUntil(distance);
    }
    
    void cancelMotion() {
        chassis.cancelMotion();
    }
    
    lemlib::Pose getPose() {
        return chassis.getPose();
    }
    
    void setPose(float x, float y, float theta) {
        chassis.setPose(x, y, theta);
    }
}
