#include "main.h"

// Get motors
extern pros::Motor& PTO_left;
extern pros::Motor& PTO_right;

extern pros::ADIDigitalOut PTO_piston;
extern pros::ADIDigitalOut wing_piston_left;
extern pros::ADIDigitalOut wing_piston_right;
extern pros::Rotation catapult_rotation_sensor;

extern pros::Motor intake;
extern pros::Motor catapult;

// Define constants
const int INTAKE_SPEED = 127;
const int INTAKE_VOLTAGE = 8000;

const int CATAPULT_CHARGED_DEGREES_MIN = 2000;
const int CATAPULT_CHARGED_DEGREES_MAX = 2100;

const int CATAPULT_CHARGING_VOLTAGE = 7750;
const int CATAPULT_SHOOTING_VOLTAGE = 12000;

// Define useful variables
bool pto_endgame_enabled = false;
float pto_cooldown = 0;

bool intake_toggle_enabled = false;
bool outtake_toggle_enabled = false;

bool wing_enabled = false;

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

bool is_catapult_charged() {
  return catapult_rotation_sensor.get_angle() >= CATAPULT_CHARGED_DEGREES_MIN &&
         catapult_rotation_sensor.get_angle() <= CATAPULT_CHARGED_DEGREES_MAX;
}

void catapult_auton_task(void* paramater) {
  // Used to keep the catapult charged during the auton
  while (true) {
    if (is_catapult_charged()) {
      catapult.brake();
    } else {
      catapult.move_voltage(CATAPULT_CHARGING_VOLTAGE);
    }
    pros::delay(20);
  }
}

void catapult_control() {
  if (master.get_digital(DIGITAL_X)) {
    catapult.move_voltage(CATAPULT_SHOOTING_VOLTAGE);
    return;
  }

  // Charge if not ready and not shooting
  if (is_catapult_charged()) {
    catapult.move_voltage(CATAPULT_CHARGING_VOLTAGE);
  }

  // Turn off motor once charged
  else {
    catapult.brake();
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
    outtake_toggle_enabled = false;
  }
  // Toggle the intake (outward direction)
  if (master.get_digital_new_press(DIGITAL_L1)) {
    outtake_toggle_enabled = !outtake_toggle_enabled;
    intake_toggle_enabled = false;
  }

  // If toggled, intake stays on
  if (intake_toggle_enabled) {
    set_intake_volts(-INTAKE_VOLTAGE);
    return;
  }

  if (outtake_toggle_enabled) {
    set_intake_volts(INTAKE_VOLTAGE);
    return;
  }

  // Hold buttons to control the intake (while not toggled)
  if (master.get_digital(DIGITAL_L2)) {
    intake_toggle_enabled = false;
    outtake_toggle_enabled = false;
    set_intake_volts(INTAKE_VOLTAGE);
  } else if (master.get_digital(DIGITAL_R2)) {
    intake_toggle_enabled = false;
    outtake_toggle_enabled = false;
    set_intake_volts(-INTAKE_VOLTAGE);
  } else {
    set_intake_volts(0);
  }
}

void wing_toggle(bool toggle) {
  wing_piston_right.set_value(toggle);
  wing_piston_left.set_value(toggle);
  wing_enabled = toggle;
}

void wing_control() {
  // Handle enabling/disabling the wings in user control
  if (master.get_digital(DIGITAL_B))
    wing_toggle(!wing_enabled);
}

void rumble_controller() {
  master.rumble("....");
}

void print_stats_controller() {
  // Clear the controller screen
  master.clear();

  // Print PTO mode
  master.print(0, 0, "PTO mode: %d", get_pto_mode());

  // Print the heading (0-360) of the robot
  master.print(1, 0, "Heading: %d", chassis.imu.get_heading());
}
