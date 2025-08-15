#pragma once

namespace Autonomous {
    // Autonomous routine functions
    void initialize();
    
    // Competition autonomous routines
    void basicRoutine();
    void skillsRoutine();
    void testRoutine();
    
    // Helper functions for easy autonomous programming
    void driveForward(float distance, int timeout = 3000);
    void driveBackward(float distance, int timeout = 3000);
    void turnRight(float degrees, int timeout = 2000);
    void turnLeft(float degrees, int timeout = 2000);
    void turnToHeading(float heading, int timeout = 2000);
    
    // Position management
    void resetPosition();
    void returnToStart();
}
