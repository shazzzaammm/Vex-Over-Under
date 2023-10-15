#include "main.h"
#include "helpers.hpp"

// Define the chassis (PTO motors are in the middle of the curly braces)
Drive chassis({-15, 9, -17}, {8, -10, 2}, 20, 4.125, 200, 0.5);

// Define Motors
pros::Motor& PTO_left = chassis.left_motors[1];
pros::Motor& PTO_right = chassis.right_motors[1];
pros::Motor intake_left (19, false);
pros::Motor intake_right (-18, false);
pros::Motor catapult_left (16, false);
pros::Motor catapult_right (-14, false);
// Define pneumatics
pros::ADIDigitalOut PTO_piston('A');

bool pto_intake_enabled = false;
float pto_cooldown = 0;

void initialize() {

  // Stop the user from doing anything while legacy ports configure.
  pros::delay(500);

  chassis.set_active_brake(0.1);
  chassis.set_curve_default(0, 0);

  default_constants();
  exit_condition_defaults();

  // Define autons for the selector
  ez::as::auton_selector.add_autons({
      Auton("Test Auton\n\nchat is this real", test_auton),
      Auton("Same Zone Score\n\nstart on the right side, score 4 triballs ", same_zone_score),
      Auton("Opposite Zone AutonWinPoint\n\nstart on the left side, score 4 triballs, end touching the elevation bar", opposite_zone_awp),
  });

  // Set the motor brake modes
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD);
  chassis.initialize();
  ez::as::initialize();

  // Set PTO to 6 motor drive configuration
  pto_toggle(false);
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
    pto_control();

    pto_cooldown -= ez::util::DELAY_TIME;
    pros::delay(ez::util::DELAY_TIME);
  }
}
