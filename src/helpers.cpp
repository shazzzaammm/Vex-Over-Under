#include "main.h"
#include "variables.hpp"

#pragma region definitions
// Get motors
extern pros::Motor& PTO_intake;
extern pros::Motor& PTO_catapult;

extern pros::ADIDigitalOut PTO_piston;
extern pros::ADIDigitalOut wing_piston_left;
extern pros::ADIDigitalOut wing_piston_right;

// Get sensors
extern pros::Distance cata_distance_sensor;

// Get constants
extern const int INTAKE_SPEED;
extern const int INTAKE_VOLTAGE;

extern const int CATAPULT_CHARGING_VOLTAGE;
extern const int CATAPULT_SHOOTING_VOLTAGE;

extern const int TRIBALL_SHOOT_DISTANCE;

// Get useful variables
extern int pto_cooldown;
extern bool pto_6_motor_enabled;

extern bool intake_toggle_enabled;
extern bool outtake_toggle_enabled;

extern bool wing_toggle_enabled;

extern bool catapult_auto_shoot_enabled;

// Get the control scheme
extern ControlScheme selected_controls;

#pragma endregion definitions

#pragma region controller
void rumble_controller() {
  master.rumble(".");
}
std::string getButtonDown(){
  if (master.get_digital(selected_controls.holdIntakeButton)){
    return "Intake Hold";
  }
  if (master.get_digital(selected_controls.holdOuttakeButton)){
    return "Outtake Hold";
  }
  if (master.get_digital(selected_controls.shootCatapultButton)){
    return "Catapult Hold";
  }
  if (master.get_digital(selected_controls.toggleCatapultButton)){
    return "Catapult Toggle";
  }
  if (master.get_digital(selected_controls.toggleIntakeButton)){
    return "Intake Toggle";
  }
  if (master.get_digital(selected_controls.toggleOuttakeButton)){
    return "Outtake Toggle";
  }
  if (master.get_digital(selected_controls.togglePTOButton)){
    return "PTO Toggle";
  }
  if (master.get_digital(selected_controls.toggleWingsButton)){
    return "Wings Toggle";
  }
  return "None";
}

void print_stats_controller() {
  // Clear the controller screen
  // master.clear();
  
  master.set_text(2, 0, pto_6_motor_enabled ? "6 motor!!!!" : "8 motor!!!!");
}
#pragma endregion controller

#pragma region catapult
void toggle_auto_shoot_catapult() {
  catapult_auto_shoot_enabled = !catapult_auto_shoot_enabled;
}

bool catapult_filled() {
  // Returns if the cata has triball in it and is in auto shoot mode
  return cata_distance_sensor.get() <= TRIBALL_SHOOT_DISTANCE && toggle_auto_shoot_catapult;
}

void catapult_control() {
  if(!pto_6_motor_enabled){
    return;
  }
  if (master.get_digital_new_press(selected_controls.toggleCatapultButton)) {
    toggle_auto_shoot_catapult();
  }

  if (master.get_digital(selected_controls.shootCatapultButton) || toggle_auto_shoot_catapult) {
    PTO_catapult.move_voltage(CATAPULT_SHOOTING_VOLTAGE);
  }

  else if (pto_6_motor_enabled) {
    PTO_catapult.brake();
  }
}
#pragma endregion catapult

#pragma region pto
void pto_toggle(bool toggle) {
  // Toggle PTO motors + bool
  pto_6_motor_enabled = toggle;
  chassis.pto_toggle({PTO_intake, PTO_catapult}, toggle);

  // Actuate the piston
  PTO_piston.set_value(!toggle);

  // Reset the timer
  pto_cooldown = 0;
}

void pto_control() {
  // Handle PTO activation/deactivation in user control
  if (master.get_digital_new_press(selected_controls.togglePTOButton)) {
    pto_toggle(!pto_6_motor_enabled);
  }
}

void pto_timer() {}

#pragma endregion pto

#pragma region intake
void spin_intake_for(float degrees) {
  if (!pto_6_motor_enabled)
    return;
  PTO_intake.move_relative(degrees, INTAKE_SPEED);
}

void set_intake_volts(int volts) {
  PTO_intake.move_voltage(volts);
}

void intake_control() {
  // Toggle the intake (inward direction)
  if (master.get_digital_new_press(selected_controls.toggleIntakeButton)) {
    intake_toggle_enabled = !intake_toggle_enabled;
    outtake_toggle_enabled = false;
  }
  // Toggle the intake (outward direction)
  if (master.get_digital_new_press(selected_controls.toggleOuttakeButton)) {
    outtake_toggle_enabled = !outtake_toggle_enabled;
    intake_toggle_enabled = false;
  }

  // Hold buttons to control the intake (while not toggled)
  if (master.get_digital(selected_controls.holdOuttakeButton) || outtake_toggle_enabled) {
    set_intake_volts(INTAKE_VOLTAGE);
    pto_toggle(true);
  } else if (master.get_digital(selected_controls.holdIntakeButton) || intake_toggle_enabled) {
    set_intake_volts(-INTAKE_VOLTAGE);
    pto_toggle(true);
  } else if (pto_6_motor_enabled) {
    set_intake_volts(0);
  }
}
#pragma endregion intake

#pragma region wings
void wing_toggle(bool toggle) {
  wing_piston_right.set_value(toggle);
  wing_piston_left.set_value(toggle);
  wing_toggle_enabled = toggle;
}

void wing_control() {
  // Handle enabling/disabling the wings in user control
  if (master.get_digital_new_press(selected_controls.toggleWingsButton))
    wing_toggle(!wing_toggle_enabled);
}
#pragma endregion wings

#pragma region endgame
// how is endgame gonna work im so lost
#pragma endregion endgame