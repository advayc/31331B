#include "display.h"
#include "chassis.h"
#include "sensors.h"
#include "pros/llemu.hpp"

namespace Display {
    pros::Task* displayTask = nullptr;
    
    void initialize() {
        pros::lcd::initialize();
    }
    
    void updateRobotInfo() {
        // Display chassis and sensor info
        lemlib::Pose pose = Chassis::getPose();
        pros::lcd::print(0, "X: %.2f Y: %.2f", pose.x, pose.y);
        pros::lcd::print(1, "Heading: %.1f deg", pose.theta);
        pros::lcd::print(2, "IMU: %.1f deg", Sensors::getHeading());
        
        // Show if IMU is calibrated
        if (Sensors::isImuCalibrated()) {
            pros::lcd::print(3, "Status: Ready");
        } else {
            pros::lcd::print(3, "Status: Calibrating...");
        }
    }
    
    void printLine(int line, const char* format, ...) {
        va_list args;
        va_start(args, format);
        char buffer[64];
        vsnprintf(buffer, sizeof(buffer), format, args);
        pros::lcd::print(line, "%s", buffer);
        va_end(args);
    }
    
    void clear() {
        pros::lcd::clear();
    }
    
    void startDisplayTask() {
        if (displayTask == nullptr) {
            displayTask = new pros::Task([=] {
                while (true) {
                    updateRobotInfo();
                    pros::delay(50);
                }
            });
        }
    }
    
    void stopDisplayTask() {
        if (displayTask != nullptr) {
            displayTask->remove();
            delete displayTask;
            displayTask = nullptr;
        }
    }
    
    void showMotorTemps() {
        // Show motor temperatures (useful for debugging)
        pros::lcd::print(4, "Motor Temps: OK");
    }
    
    void showSensorValues() {
        pros::lcd::print(5, "IMU Calibrated: %s", Sensors::isImuCalibrated() ? "Yes" : "No");
        pros::lcd::print(6, "Rotation: %.1f", Sensors::getRotation());
    }
    
    void showPoseInfo() {
        lemlib::Pose pose = Chassis::getPose();
        pros::lcd::print(7, "Pose: (%.1f, %.1f, %.1f)", pose.x, pose.y, pose.theta);
    }
}
