#include "sensors.h"

namespace Sensors {
    // Sensor instances - enabled for PID/odometry
    pros::Imu imu(10);  // IMU on port 10
    
    // No tracking wheels yet, but IMU can provide heading for basic odometry
    
    void initialize() {
        calibrateAll();
    }
    
    void calibrateAll() {
        imu.reset();
        while (imu.is_calibrating()) {
            pros::delay(10);
        }
    }
    
    bool isImuCalibrated() {
        return !imu.is_calibrating();
    }
    
    double getHeading() {
        return imu.get_heading();
    }
    
    double getRotation() {
        return imu.get_rotation();
    }
    
    void resetHeading() {
        imu.set_heading(0);
    }
    
    double getHorizontalPosition() {
        // No tracking wheels yet
        return 0.0;
    }
    
    double getVerticalPosition() {
        // No tracking wheels yet
        return 0.0;
    }
    
    void resetEncoders() {
        // No tracking wheels to reset yet
    }
}
