#pragma once

namespace Sensors {
    // Header contract: stub sensor interface; implementation has no dependencies.
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
