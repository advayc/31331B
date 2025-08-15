#pragma once

#include "pros/imu.hpp"

namespace Sensors {
    // Sensor instances
    extern pros::Imu imu;
    
    // Sensor functions
    void initialize();
    void calibrateAll();
    
    // IMU functions
    bool isImuCalibrated();
    double getHeading();
    double getRotation();
    void resetHeading();
    
    // Encoder functions (for future tracking wheels)
    double getHorizontalPosition();
    double getVerticalPosition();
    void resetEncoders();
}
