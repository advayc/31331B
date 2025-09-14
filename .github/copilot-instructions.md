# Copilot Instructions for 31331B VEX Robot Codebase

## Architecture Overview
This is a PROS-based VEX V5 robot project using modular C++ namespaces for subsystems. Key components:
- **Drive**: Motor control and basic movements (`src/drive.cpp`, `include/drive.h`).
- **Controller**: Input handling (`src/controller.cpp`, `include/controller.h`).
- **Chassis**: LemLib-based PID control and odometry (`src/chassis.cpp`, `include/chassis.h`).
- **Autonomous**: Movement routines using Chassis (`src/autonomous.cpp`, `include/autonomous.h`).
- **Display**: Brain screen output (`src/display.cpp`, `include/display.h`).
- **Sensors**: Placeholder for external sensors (`src/sensors.cpp`, `include/sensors.h`).

Data flows from Controller inputs to Drive/Chassis for teleop, or Autonomous calls Chassis for PID-based movements. Modular design enables independent tuning (e.g., PID gains in Chassis, motor ports in Drive).

## Key Patterns and Conventions
- **Namespaces**: Each module uses its own namespace (e.g., `namespace Drive { ... }`).
- **Headers**: Declare externs and function prototypes; avoid self-includes in `.cpp` files (e.g., `drive.cpp` does not `#include "drive.h"`).
- **PID Tuning**: Runtime adjustment via `Chassis::setLinearGains()`/`setAngularGains()` and `rebuild()`; tuned in `opcontrol()` with controller buttons (L1 toggle mode, L2 switch Linear/Angular, D-pad adjust P/I/D).
- **LemLib Integration**: Use `lemlib::Chassis` for advanced control; settings in `ControllerSettings` structs.
- **PROS API**: Hardware access via `pros::` namespace (e.g., `pros::MotorGroup`, `pros::Controller`).

## Developer Workflows
- **Build**: Run `make -j4` from project root; outputs `bin/hot.package.bin` for VEX brain.
- **Testing/Debugging**: No unit tests; use `Autonomous::testRoutine()` or tuning mode in `opcontrol()` for on-robot validation. Debug via brain screen (`Display::printLine()`) or controller rumble (`Controller::rumble()`).
- **Tuning**: Enter tuning mode (L1) in driver control; adjust gains with D-pad, test movements immediately.
- **Dependencies**: LemLib linked statically; PROS toolchain required (install via `pros-cli`).

## Integration Points
- **External Libs**: LemLib for chassis/odometry (`firmware/LemLib.a`); PROS for hardware (`firmware/libpros.a`).
- **Communication**: Modules communicate via function calls (e.g., `Autonomous` calls `Chassis::moveToPoint()`); no inter-process or network comms.
- **Hardware**: VEX V5 brain/motors; motor ports configured in `Drive` (e.g., ports -1,2,3 for left).

Reference: `src/main.cpp` for competition hooks; `include/main.h` for includes.