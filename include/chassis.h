#pragma once

#include "lemlib/api.hpp"

namespace Chassis {
    // Drivetrain and chassis instances
    extern lemlib::Drivetrain drivetrain;
    extern lemlib::Chassis chassis;
    
    // PID Controllers
    extern lemlib::ControllerSettings linearController;
    extern lemlib::ControllerSettings angularController;
    
    // Drive curves
    extern lemlib::ExpoDriveCurve throttleCurve;
    extern lemlib::ExpoDriveCurve steerCurve;
    
    // Chassis functions
    void initialize();
    void calibrate();
    
    // Movement functions
    void moveToPose(float x, float y, float theta, int timeout, bool forwards = true, float maxSpeed = 127);
    void moveToPoint(float x, float y, int timeout, bool forwards = true, float maxSpeed = 127);
    void turnToHeading(float theta, int timeout, float maxSpeed = 127);
    void turnToPoint(float x, float y, int timeout, float maxSpeed = 127);
    
    // Path following
    void follow(const char* path, float lookahead, int timeout, bool forwards = true);
    
    // Utility functions
    void waitUntilDone();
    void waitUntil(float distance);
    void cancelMotion();
    
    // Pose functions
    lemlib::Pose getPose();
    void setPose(float x, float y, float theta);
}
