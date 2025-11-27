#include "lemlib/api.hpp"
#include "pros/rtos.hpp"
#include "pros/motors.hpp"
#include "pros/motor_group.hpp"
#include "drive.h"
#include <new>

namespace Chassis {
    // Forward declarations for functions used before they are defined
    void calibrate();
    // PID and chassis setup for 36:60 drivetrain, 360 RPM, motor encoder odometry
    lemlib::Drivetrain drivetrain(&Drive::leftMotors,
                                  &Drive::rightMotors,
                                  15.0, // track width in inches (15" x 15" robot)
                                  lemlib::Omniwheel::NEW_325, // 3.25" wheels
                                  360, // drivetrain rpm (matches your specs)
                                  2 // horizontal drift (lower for better accuracy with encoders)
    );

    // Tuned PID controllers for precise motor encoder movement
    lemlib::ControllerSettings linearController(8,  // kP - proportional gain
                                               0,   // kI - integral gain
                                               25,  // kD - derivative gain
                                               3,   // anti windup
                                               1,   // small error range (inches)
                                               100, // small error timeout (ms)
                                               3,   // large error range (inches)
                                               500, // large error timeout (ms)
                                               20   // max acceleration (slew)
    );
    
    lemlib::ControllerSettings angularController(4,  // kP - proportional gain
                                                 0,   // kI - integral gain
                                                 30,  // kD - derivative gain
                                                 3,   // anti windup
                                                 2,   // small error range (degrees)
                                                 100, // small error timeout (ms)
                                                 5,   // large error range (degrees)
                                                 500, // large error timeout (ms)
                                                 0    // max acceleration (slew)
    );
    
    // Basic odometry using motor encoders only (no external sensors)
    lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1
                               nullptr, // vertical tracking wheel 2  
                               nullptr, // horizontal tracking wheel 1
                               nullptr, // horizontal tracking wheel 2
                               nullptr  // no inertial sensor - using motor encoders only
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
    
    void follow(asset& path, float lookahead, int timeout, bool forwards) {
        // Follow the path using LemLib's path following
        chassis.follow(path, lookahead, timeout, forwards);
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

    // --- Runtime PID tuning implementation ---
    void setLinearGains(float kP, float kI, float kD) {
        linearController.kP = kP;
        linearController.kI = kI;
        linearController.kD = kD;
    }

    void setAngularGains(float kP, float kI, float kD) {
        angularController.kP = kP;
        angularController.kI = kI;
        angularController.kD = kD;
    }

    void getLinearGains(float& kP, float& kI, float& kD) {
        kP = linearController.kP;
        kI = linearController.kI;
        kD = linearController.kD;
    }

    void getAngularGains(float& kP, float& kI, float& kD) {
        kP = angularController.kP;
        kI = angularController.kI;
        kD = angularController.kD;
    }

    void rebuild() {
        // Destroy and reconstruct chassis in-place with updated settings
        chassis.~Chassis();
        new (&chassis) lemlib::Chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);
    }
}
