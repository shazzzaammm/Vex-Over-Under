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
extern pros::Optical cata_optic_sensor;

// Get constants
extern const int INTAKE_SPEED;
extern const int INTAKE_VOLTAGE;

extern const int CATAPULT_CHARGING_VOLTAGE;
extern const int CATAPULT_SHOOTING_VOLTAGE;

extern const float TRIBALL_LOADED_BRIGHTNESS;

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

#pragma region chassis
void tank_drive(){
    if (!chassisIsReversed) {
      chassis.set_tank(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_Y));
    } else {
      chassis.set_tank(-master.get_analog(ANALOG_RIGHT_Y), -master.get_analog(ANALOG_LEFT_Y));
    }
}

void reverse_chassis(){
      chassisIsReversed = !chassisIsReversed;
}

void chassis_control(){
  tank_drive();
  if(master.get_digital_new_press(selected_controls.reverseChassisButton)){
    reverse_chassis();
  }
}
#pragma endregion chassis

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
  master.set_text(0, 0, pto_6_motor_enabled ? "6 motor!!!!" : "8 motor!!!!");
}
#pragma endregion controller

#pragma region catapult
void toggle_auto_shoot_catapult() {
  catapult_auto_shoot_enabled = !catapult_auto_shoot_enabled;
}

bool isSlapperFull() {
  return cata_optic_sensor.get_brightness() < TRIBALL_LOADED_BRIGHTNESS;
}

void catapult_control() {
  if (master.get_digital_new_press(selected_controls.toggleCatapultButton)) {
    toggle_auto_shoot_catapult();
  }

  if (master.get_digital(selected_controls.shootCatapultButton) || catapult_auto_shoot_enabled) {
    PTO_catapult.move_voltage(CATAPULT_SHOOTING_VOLTAGE);
    pto_toggle(true);
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

#pragma endregion pto

#pragma region intake
void spin_intake_for(float degrees) {
  if (!pto_6_motor_enabled)
    return;
  PTO_intake.move_relative(degrees, INTAKE_SPEED);
}

void set_intake_volts(int volts) {
  if (!pto_6_motor_enabled)
    return;
  PTO_intake.move_voltage(volts);
}

void intake_control() {
  if (!pto_6_motor_enabled)
    return;
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