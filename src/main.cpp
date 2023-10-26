#include "main.h"
#include "helpers.hpp"

// Define the chassis (PTO motors are in the middle of the curly braces)
Drive chassis({-1, 2, -3}, {8, -7, 10}, 17, 4.125, 200, 0.5);

// Define Motors
pros::Motor& PTO_left = chassis.left_motors[1];
pros::Motor& PTO_right = chassis.right_motors[1];
pros::Motor intake(-5, false);
pros::Motor catapult(100, false);

// Define pneumatics
pros::ADIDigitalOut PTO_piston('A');
pros::ADIDigitalOut wing_piston('B');

// Retrieve necessary constants
extern float pto_cooldown;
extern float controller_stats_cooldown;

void initialize() {

  // Stop the user from doing anything while legacy ports configure.
  pros::delay(500);

  chassis.set_active_brake(0.1);
  chassis.set_curve_default(0, 0);

  default_constants();
  exit_condition_defaults();

  // Define autons for the selector
  ez::as::auton_selector.add_autons({
      Auton("Opposite Zone AutonWinPoint\n\nstart on the left side, score 3 triballs, end touching the elevation bar", opposite_zone_awp),
      Auton("Same Zone Score\n\nstart on the right side, score 4 triballs ", same_zone_score),
      Auton("Test Auton\n\nchat is this real", test_auton),
  });

  // Set the motor brake modes
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD);

  // Initialize
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
  // TODO Automatically deactivate the endgame and switch PTO to 6 motor
  while (true) {
    chassis.set_drive_brake(MOTOR_BRAKE_BRAKE);
    // Handle chassis control
    chassis.tank();

    // Handle pto control
    pto_control();

    // Handle intake control
    intake_control();

    // Handle wing control
    wing_control();

    // Test the catapult movement
    // !Remove once the catapult is working
    test_cata_user_control();

    // Print to the controller screen
    print_stats_controller();

    // Decrease the timers
    pto_cooldown -= ez::util::DELAY_TIME;
    controller_stats_cooldown -= ez::util::DELAY_TIME;

    // Keep the time between cycles constant
    pros::delay(ez::util::DELAY_TIME);
  }
}
