#include "sensors.h"

namespace Sensors {
    // No external sensors - using motor encoders only
    
    void initialize() {
        // No sensors to initialize
    }
    
    void calibrateAll() {
        // No sensors to calibrate
    }
    
    bool isImuCalibrated() {
        return true; // Always ready since no IMU
    }
    
    double getHeading() {
        // No IMU - heading will be calculated from motor encoders by LemLib
        return 0.0;
    }
    
    double getRotation() {
        // No IMU - rotation calculated from motor encoders
        return 0.0;
    }
    
    void resetHeading() {
        // No IMU to reset - motor encoders handle this
    }
    
    double getHorizontalPosition() {
        // No tracking wheels
        return 0.0;
    }
    
    double getVerticalPosition() {
        // No tracking wheels  
        return 0.0;
    }
    
    void resetEncoders() {
        // Motor encoders are reset in Drive module
    }
}
