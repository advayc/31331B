#pragma once

#include <cstdint>
#include "pros/misc.hpp"

// Header contract:
// - Declares controller accessors; safe to include anywhere.
// - Implementation (.cpp) does not include this header.

namespace Controller {
    // Controller instance
    extern pros::Controller master;
    
    // Controller functions
    void initialize();
    
    // Input reading functions
    int getLeftY();
    int getRightX();
    int getLeftX();
    int getRightY();
    
    // Aliases for Python VEX style
    int getForward();  // Left Y (axis 3)
    int getTurn();     // Left X (axis 4)
    int getConveyor(); // Right Y (axis 2)
    
    // Button checking
    bool getDigital(pros::controller_digital_e_t button);
    bool getDigitalNewPress(pros::controller_digital_e_t button);
    
    // Rumble and screen functions
    void rumble(const char* pattern);
    void setText(std::uint8_t line, std::uint8_t col, const char* str);
}
