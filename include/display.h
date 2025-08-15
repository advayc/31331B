#pragma once

#include "pros/screen.hpp"

namespace Display {
    // Display functions
    void initialize();
    void updateRobotInfo();
    void printLine(int line, const char* format, ...);
    void clear();
    
    // Brain screen task
    void startDisplayTask();
    void stopDisplayTask();
    
    // Debug info
    void showMotorTemps();
    void showSensorValues();
    void showPoseInfo();
}
