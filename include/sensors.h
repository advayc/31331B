#pragma once

namespace Sensors {
    // Sensor functions (no external sensors - using motor encoders only)
    void initialize();
    void calibrateAll();
    
    // Placeholder functions for compatibility
    bool isImuCalibrated();
    double getHeading();
    double getRotation();
    void resetHeading();
    
    // Encoder functions (for future tracking wheels)
    double getHorizontalPosition();
    double getVerticalPosition();
    void resetEncoders();
}
