#pragma once

#include "lemlib/api.hpp"

namespace Autonomous {
    // Starting position management
    extern lemlib::Pose startingPose;
    
    // Autonomous routine functions
    void initialize();
    
    // Competition autonomous routines
    void basicRoutine();
    void skillsRoutine();
    void testRoutine();
    
    // PID-based movement functions with precise positioning
    void driveToPoint(float x, float y, int timeout = 4000, bool forwards = true);
    void driveToPose(float x, float y, float heading, int timeout = 4000, bool forwards = true);
    void turnToHeading(float heading, int timeout = 3000);
    void driveDistance(float distance, int timeout = 4000, bool forwards = true);
    
    // Relative movement functions (from current position)
    void driveForward(float inches);
    void driveBackward(float inches);
    void turnRight(float degrees);
    void turnLeft(float degrees);
    void strafeRight(float inches);  // For future mecanum wheels
    void strafeLeft(float inches);   // For future mecanum wheels
    
    // Position and pose management
    void setStartingPose(float x, float y, float heading);
    void resetToStartingPose();
    void resetPosition();
    lemlib::Pose getCurrentPose();
    
    // Utility functions
    void waitUntilDone();
    void waitUntilDistance(float distance);
    void waitMS(int milliseconds);
    
    // PID tuning functions
    void tuneLinearPID();
    void tuneAngularPID();
}
