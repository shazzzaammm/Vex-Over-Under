#include "main.h"
#pragma region definitions
// Get motors
extern pros::Motor& PTO_intake;
extern pros::Motor& PTO_catapult;

extern pros::ADIDigitalOut PTO_piston;
extern pros::ADIDigitalOut wing_piston_left;
extern pros::ADIDigitalOut wing_piston_right;

// Define constants
const int INTAKE_SPEED = 127;
const int INTAKE_VOLTAGE = 12000;

const int CATAPULT_CHARGING_VOLTAGE = 12000;
const int CATAPULT_SHOOTING_VOLTAGE = 12000;

// Define useful variables
int pto_cooldown = 0;
bool pto_6_motor_enabled = false;

bool intake_toggle_enabled = false;
bool outtake_toggle_enabled = false;

bool wing_toggle_enabled = false;

bool catapult_auto_shoot_enabled = false;

// Define the control scheme
const ControlScheme a_controls(
  DIGITAL_R2,
  DIGITAL_L2,
  DIGITAL_R1,
  DIGITAL_L1,
  DIGITAL_B,
  DIGITAL_A,
  DIGITAL_Y,
  DIGITAL_X
);
const ControlScheme g_controls(
  DIGITAL_R1,
  DIGITAL_R2,
  DIGITAL_L1,
  DIGITAL_L2,
  DIGITAL_A,
  DIGITAL_B,
  DIGITAL_X,
  DIGITAL_Y
);

ControlScheme selected_controls = a_controls;

#pragma endregion definitions

#pragma region controller
void rumble_controller() {
  master.rumble(".");
}

void print_stats_controller() {
  // Clear the controller screen
  master.clear();

  // Print PTO mode
  master.print(0, 0, "PTO mode: %d", pto_6_motor_enabled ? 4 : 6);

  // Print the heading (0-360) of the robot
  master.print(1, 0, "Heading: %d", chassis.imu.get_heading());
}
#pragma endregion controller

#pragma region catapult
void toggle_auto_shoot_catapult(){
  catapult_auto_shoot_enabled = !catapult_auto_shoot_enabled;
}

void catapult_control() {
  if(!pto_6_motor_enabled) return;
  
  if(master.get_digital_new_press(selected_controls.toggleCatapultButton)){
    toggle_auto_shoot_catapult();
  }

  if (master.get_digital(selected_controls.shootCatapultButton) || catapult_auto_shoot_enabled) {
    PTO_catapult.move_voltage(CATAPULT_SHOOTING_VOLTAGE);
    pto_cooldown = 0;
    return;
  }

  // Turn off motor once charged
  else {
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

  // 

  // Reset the timer
  pto_cooldown = 0;
}

void pto_control() {
  // Handle PTO activation/deactivation in user control
  if (master.get_digital_new_press(selected_controls.togglePTOButton)){
    pto_toggle(!pto_6_motor_enabled);
  }
}

void pto_timer(){
  if (pto_6_motor_enabled){
    pto_cooldown += ez::util::DELAY_TIME;
  }

  // Change to 8 motor if driver forgot
  if(pto_cooldown > 2000 && pto_6_motor_enabled){
    pto_toggle(false);
  }
}

#pragma endregion pto

#pragma region intake
void spin_intake_for(float degrees) {
  if(!pto_6_motor_enabled) return;
  PTO_intake.move_relative(degrees, INTAKE_SPEED);
}

void set_intake_volts(int volts) {
  if(!pto_6_motor_enabled) return;
  PTO_intake.move_voltage(volts);
  pto_cooldown = 0;
}

void intake_control() {
  if(!pto_6_motor_enabled) return;
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
  if (master.get_digital(selected_controls.holdOuttakeButton)) {
    set_intake_volts(INTAKE_VOLTAGE);
  } else if (master.get_digital(selected_controls.holdIntakeButton)) {
    set_intake_volts(-INTAKE_VOLTAGE);
  } else {
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