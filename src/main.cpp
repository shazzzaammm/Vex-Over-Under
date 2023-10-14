#include "main.h"
#include "helpers.hpp"
#include "okapi/api.hpp"

// Define the okapi controller
okapi::Controller controller;

// ⁡⁣⁢⁣(left_motor_ports, right_motor_ports, imu_port, wheel_diameter, ticks, ratio);
// Define the chassis (PTO motors are in the middle of the curly braces)⁡
Drive chassis({-15, 9, -17}, {8, -10, 2}, 20, 4.125, 200, 0.5);

// Define Motors
pros::Motor& PTO_left = chassis.left_motors[1];
pros::Motor& PTO_right = chassis.right_motors[1];
pros::ADIDigitalOut PTO_piston('A');
bool pto_intake_enabled = false;
float pto_cooldown = 0;

void pto_intake(bool toggle) {
  //This prevents extreme air loss using a cooldown
  if (pto_cooldown > 0) {
    return;
  }
  pto_cooldown = ez::util::DELAY_TIME * 10;
  pto_intake_enabled = toggle;
  chassis.pto_toggle({PTO_left, PTO_right}, toggle);

  //⁡⁢⁢⁣TODO ⁡make sure this line isnt the issue in the chassis
  PTO_piston.set_value(!toggle);
  if (toggle) {
    PTO_left.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    PTO_right.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  }
}

void set_intake(int volts) {
  if (!pto_intake_enabled)
    return;
  // Sets intake voltage to the input value
  PTO_left = volts;
  PTO_right = volts;
}

void intake_control() {
  // Handle PTO activation /deactivation
  if (master.get_digital(DIGITAL_A))
    pto_intake(!pto_intake_enabled);
  else if (master.get_digital(DIGITAL_DOWN))
    pto_intake(0);
  else if (master.get_digital(DIGITAL_UP))
    pto_intake(1);
  //move with buttons if PTO set to intake :3
  if (master.get_digital(DIGITAL_L1))
    set_intake(127);
  else if (master.get_digital(DIGITAL_L2))
    set_intake(-127);
  else
    set_intake(0);
}

void initialize() {

  // Stop the user from doing anything while legacy ports configure.
  pros::delay(500);

  chassis.set_active_brake(0.1);
  chassis.set_curve_default(0, 0);

  default_constants();
  exit_condition_defaults();
  // All of these autons are deprecated at the moment
  ez::as::auton_selector.add_autons({
      Auton("Test Auton\n\nchat is this real", test_auton),
      Auton("Opposite Zone AWP\n\nstart on the right side, get half awp", opposite_zone_awp),
      Auton("Same Zone AutonWinPoint\n\nstart on the left side, get half awp", same_zone_awp),
      Auton("Opposite Zone Score\n\nstart on the right side, get 3<=x<=3 triballs", opposite_zone_score),
  });

  // Set the motor brake modes
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD);
  chassis.initialize();
  ez::as::initialize();

  // Set PTO to 6 motor drive configuration
  pto_intake(false);
}

void autonomous() {
  chassis.reset_pid_targets();
  chassis.reset_gyro();
  chassis.reset_drive_sensor();
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD);

  ez::as::auton_selector.call_selected_auton();
}

void opcontrol() {
  while (true) {
    chassis.set_drive_brake(MOTOR_BRAKE_BRAKE);
    // Handle the drive movement
    chassis.tank();

    // Handle intake control
    intake_control();

    pto_cooldown -= ez::util::DELAY_TIME;
    pros::delay(ez::util::DELAY_TIME);
  }
}
