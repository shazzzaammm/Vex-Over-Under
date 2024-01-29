#include "main.h"

enum Drive_Type { TANK, ARCADE };

class ControlScheme {
 public:
  pros::controller_digital_e_t hold_intake_button;
  pros::controller_digital_e_t hold_outtake_button;
  pros::controller_digital_e_t toggle_intake_button;
  pros::controller_digital_e_t toggle_outtake_button;
  std::vector<pros::controller_digital_e_t> toggle_wings_buttons;
  pros::controller_digital_e_t toggle_PTO_button;
  pros::controller_digital_e_t toggle_flywheel_button;
  pros::controller_digital_e_t hold_flywheel_button;
  pros::controller_digital_e_t toggle_lift_button;
  pros::controller_digital_e_t reverse_chassis_button;
  std::vector<pros::controller_digital_e_t> expansion_buttons;
  Drive_Type drive_mode;

  ControlScheme(pros::controller_digital_e_t holdIntake, pros::controller_digital_e_t holdOuttake,
                pros::controller_digital_e_t toggleIntake, pros::controller_digital_e_t toggleOuttake,
                std::vector<pros::controller_digital_e_t> toggleWings, pros::controller_digital_e_t togglePTO,
                pros::controller_digital_e_t toggleFlywheel, pros::controller_digital_e_t holdFlywheel,
                pros::controller_digital_e_t reverseChassis, pros::controller_digital_e_t toggleLift,
                std::vector<pros::controller_digital_e_t> expansionButtons, Drive_Type driveMode) {
    hold_intake_button = holdIntake;
    hold_outtake_button = holdOuttake;
    toggle_intake_button = toggleIntake;
    toggle_outtake_button = toggleOuttake;
    toggle_wings_buttons = toggleWings;
    toggle_PTO_button = togglePTO;
    toggle_flywheel_button = toggleFlywheel;
    hold_flywheel_button = holdFlywheel;
    reverse_chassis_button = reverseChassis;
    toggle_lift_button = toggleLift;
    expansion_buttons = expansionButtons;
    drive_mode = driveMode;
  }
};