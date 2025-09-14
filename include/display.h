#pragma once

#include "pros/screen.hpp"

// Header contract: declares display helpers; implementation includes pros lcd and may include chassis.

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
