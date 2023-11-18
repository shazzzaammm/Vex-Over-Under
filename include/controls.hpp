#include "main.h"
class ControlScheme {
 public:
  pros::controller_digital_e_t holdIntakeButton;
  pros::controller_digital_e_t holdOuttakeButton;
  pros::controller_digital_e_t toggleIntakeButton;
  pros::controller_digital_e_t toggleOuttakeButton;
  pros::controller_digital_e_t toggleWingsButton;
  pros::controller_digital_e_t togglePTOButton;
  pros::controller_digital_e_t toggleCatapultButton;
  pros::controller_digital_e_t shootCatapultButton;

  ControlScheme(pros::controller_digital_e_t holdIntake, pros::controller_digital_e_t holdOuttake,
                pros::controller_digital_e_t toggleIntake, pros::controller_digital_e_t toggleOuttake,
                pros::controller_digital_e_t toggleWings, pros::controller_digital_e_t togglePTO,
                pros::controller_digital_e_t toggleCatapult, pros::controller_digital_e_t shootCatapult) {
    holdIntakeButton = holdIntake;
    holdOuttakeButton = holdOuttake;
    toggleIntakeButton = toggleIntake;
    toggleOuttakeButton = toggleOuttake;
    toggleWingsButton = toggleWings;
    togglePTOButton = togglePTO;
    toggleCatapultButton = toggleCatapult;
    shootCatapultButton = shootCatapult;
  }
};