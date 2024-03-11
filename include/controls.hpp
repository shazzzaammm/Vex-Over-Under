#include "main.h"

enum Drive_Type { TANK, ARCADE };

// Honestly this might actually be something people use :O
// Ur free to do that btw no need for credit :3
// Modify the names and amount of variables and stuff to fit your needs :D
class ControlScheme {
 public:
  pros::controller_digital_e_t hold_intake_button;
  pros::controller_digital_e_t hold_outtake_button;
  pros::controller_digital_e_t toggle_intake_button;
  pros::controller_digital_e_t toggle_outtake_button;
  std::vector<pros::controller_digital_e_t> toggle_wings_buttons;
  pros::controller_digital_e_t toggle_PTO_button;
  pros::controller_digital_e_t toggle_slapper_button;
  pros::controller_digital_e_t hold_slapper_button;
  pros::controller_digital_e_t reverse_chassis_button;
  pros::controller_digital_e_t endgame_button;
  Drive_Type drive_mode;

  ControlScheme(pros::controller_digital_e_t holdIntake, pros::controller_digital_e_t holdOuttake,
                pros::controller_digital_e_t toggleIntake, pros::controller_digital_e_t toggleOuttake,
                std::vector<pros::controller_digital_e_t> toggleWings, pros::controller_digital_e_t togglePTO,
                pros::controller_digital_e_t toggleSlapper, pros::controller_digital_e_t holdSlapper,
                pros::controller_digital_e_t reverseChassis, pros::controller_digital_e_t endgameButton,
                Drive_Type driveMode) {
    hold_intake_button = holdIntake;
    hold_outtake_button = holdOuttake;
    toggle_intake_button = toggleIntake;
    toggle_outtake_button = toggleOuttake;
    toggle_wings_buttons = toggleWings;
    toggle_PTO_button = togglePTO;
    toggle_slapper_button = toggleSlapper;
    hold_slapper_button = holdSlapper;
    reverse_chassis_button = reverseChassis;
    endgame_button = endgameButton;
    drive_mode = driveMode;
  }
};