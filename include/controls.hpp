#include "main.h"

enum Drive_Type {TANK, ARCADE};

class ControlScheme {
 public:
  pros::controller_digital_e_t hold_intake_button;
  pros::controller_digital_e_t hold_outtake_button;
  pros::controller_digital_e_t toggle_intake_button;
  pros::controller_digital_e_t toggle_outtake_button;
  pros::controller_digital_e_t toggle_wings_button;
  pros::controller_digital_e_t toggle_PTO_button;
  pros::controller_digital_e_t toggle_catapult_button;
  pros::controller_digital_e_t shoot_catapult_button;
  pros::controller_digital_e_t reverse_chassis_button;
  Drive_Type drive_mode;

  ControlScheme(pros::controller_digital_e_t holdIntake, pros::controller_digital_e_t holdOuttake,
                pros::controller_digital_e_t toggleIntake, pros::controller_digital_e_t toggleOuttake,
                pros::controller_digital_e_t toggleWings, pros::controller_digital_e_t togglePTO,
                pros::controller_digital_e_t toggleCatapult, pros::controller_digital_e_t shootCatapult,
                pros::controller_digital_e_t reverseChassis, Drive_Type driveMode) {
    hold_intake_button = holdIntake;
    hold_outtake_button = holdOuttake;
    toggle_intake_button = toggleIntake;
    toggle_outtake_button = toggleOuttake;
    toggle_wings_button = toggleWings;
    toggle_PTO_button = togglePTO;
    toggle_catapult_button = toggleCatapult;
    shoot_catapult_button = shootCatapult;
    reverse_chassis_button = reverseChassis;
    drive_mode = driveMode;
  }
};