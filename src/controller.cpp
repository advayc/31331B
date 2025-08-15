#include "controller.h"

namespace Controller {
    // Controller instance
    pros::Controller master(pros::E_CONTROLLER_MASTER);
    
    void initialize() {
        // Controller initialization if needed
    }
    
    int getLeftY() {
        return master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    }
    
    int getRightX() {
        return master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    }
    
    int getLeftX() {
        return master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
    }
    
    int getRightY() {
        return master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    }
    
    bool getDigital(pros::controller_digital_e_t button) {
        return master.get_digital(button);
    }
    
    bool getDigitalNewPress(pros::controller_digital_e_t button) {
        return master.get_digital_new_press(button);
    }
    
    void rumble(const char* pattern) {
        master.rumble(pattern);
    }
    
    void setText(std::uint8_t line, std::uint8_t col, const char* str) {
        master.set_text(line, col, str);
    }
}
