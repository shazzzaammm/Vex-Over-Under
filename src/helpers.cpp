#include "main.h"

#pragma region // Variables 
// Get motors
extern pros::Motor& PTO_left;
extern pros::Motor& PTO_right;
extern pros::ADIDigitalOut PTO_piston;
extern pros::ADIDigitalOut wing_piston_left;
extern pros::ADIDigitalOut wing_piston_right;
extern pros::ADIDigitalIn catapult_limit_switch;
extern pros::Motor intake;
extern pros::Motor catapult;

// Define constants
const int INTAKE_SPEED = 127;
const int CATAPULT_SPEED = 12000;

// Define useful variables
bool pto_endgame_enabled = false;
float pto_cooldown = 0;
bool intake_toggle_enabled = false;
bool outtake_toggle_enabled = false;
bool wing_enabled = false;
float controller_stats_cooldown = 0;
#pragma endregion

void toggle_endgame(bool toggle) {
  // Only use endgame if PTO is in 4 motor mode
  if (!pto_endgame_enabled)
    return;

  // Set the endgame motors to the correct position
  if (toggle) {
    // TODO turn on the endgame
  } else {
    // TODO turn off the endgame
  }
}

void charge_catapult() {
  // Only move if the catapult is not charged
  if (catapult_limit_switch.get_value() == false) {
    catapult.move_voltage(CATAPULT_SPEED);
  }
  else{
    catapult.move_voltage(6000);
  }
}

void shoot_catapult() {
  // Dont try and shoot unless cata is ready
  if (!catapult_limit_switch.get_value()){
    return;
  }
  // Move the catapult enough to slip the gear
  catapult.move_relative(90, -127);
}

void test_cata_user_control() {
  charge_catapult();
  if(master.get_digital(DIGITAL_Y)){
    shoot_catapult();
  } 
}

void pto_toggle(bool toggle) {
  // This prevents extreme air loss using a cooldown
  if (pto_cooldown > 0) {
    return;
  }
  // Set the PTO cooldown
  pto_cooldown = ez::util::DELAY_TIME * 50;

  // Toggle PTO motors + bool
  pto_endgame_enabled = toggle;
  chassis.pto_toggle({PTO_left, PTO_right}, toggle);

  // Actuate the piston
  PTO_piston.set_value(!toggle);
}

void set_pto_volts(int volts) {
  // Only activates if engame is enabled
  if (!pto_endgame_enabled)
    return;

  // Sets endgame voltage to the input value
  PTO_left = volts;
  PTO_right = volts;
}

void pto_control() {
  // Handle PTO activation/deactivation in user control
  if (master.get_digital(DIGITAL_A))
    pto_toggle(!pto_endgame_enabled);
  else if (master.get_digital(DIGITAL_DOWN))
    pto_toggle(0);
  else if (master.get_digital(DIGITAL_UP))
    pto_toggle(1);
}

int get_pto_mode() {
  if (pto_endgame_enabled)
    return 4;
  return 6;
}

void spin_intake_for(float degrees) {
  intake.move_relative(degrees, INTAKE_SPEED);
}

void set_intake_volts(int volts) {
  intake.move_voltage(volts);
}

void intake_control() {
  // Toggle the intake (inward direction)
  if (master.get_digital_new_press(DIGITAL_R1)) {
    intake_toggle_enabled = !intake_toggle_enabled;
  }
  // Toggle the intake (outward direction)
  if (master.get_digital_new_press(DIGITAL_L1)) {
    outtake_toggle_enabled = !outtake_toggle_enabled;
    intake_toggle_enabled = false;
  }

  // If toggled, intake stays on
  if (intake_toggle_enabled) {
    set_intake_volts(-8000);
    return;
  }

  if (outtake_toggle_enabled) {
    set_intake_volts(8000);
    return;
  }

  // Hold buttons to control the intake (while not toggled)
  if (master.get_digital(DIGITAL_L2)) {
    set_intake_volts(8000);
  } else if (master.get_digital(DIGITAL_R2)) {
    set_intake_volts(-8000);
  } else {
    set_intake_volts(0);
  }
}

void wing_toggle(bool toggle) {
  wing_piston_left.set_value(toggle);
  wing_piston_right.set_value(toggle);
  wing_enabled = toggle;
}

void wing_control() {
  // Handle enabling/disabling the wings in user control
  if (master.get_digital(DIGITAL_RIGHT))
    wing_toggle(!wing_enabled);
  // else if (master.get_digital(DIGITAL_LEFT))
  //   wing_toggle(0);
  // else if (master.get_digital(DIGITAL_RIGHT))
  //   wing_toggle(1);
}

void rumble_controller() {
  master.rumble("....");
}

void print_stats_controller() {
  // Test if the cooldown is over
  if (controller_stats_cooldown > 0) {
    return;
  }

  // Reset the cooldown
  controller_stats_cooldown = ez::util::DELAY_TIME * 50;

  // Clear the controller screen
  master.clear();

  // Print PTO mode
  master.print(0, 0, "PTO mode: %d", get_pto_mode());

  // Print the heading (0-360) of the robot
  master.print(1, 0, "Heading: %d", chassis.imu.get_heading());
}
