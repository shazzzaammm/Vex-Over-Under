#include "main.h"

// Define the chassis (PTO motors are last in the curly braces)
Drive chassis({-6, 9, -7, 200}, {1, -8, 2, 300}, 10, 4.125, 200, 0.5);

// Define Motors
pros::Motor& PTO_intake = chassis.left_motors[3];
pros::Motor& PTO_catapult = chassis.right_motors[3];
pros::Motor intake(-20, false);
pros::Motor catapult(-5, pros::E_MOTOR_GEAR_100, true);

// Define pneumatics
pros::ADIDigitalOut PTO_piston('A');
pros::ADIDigitalOut wing_piston_left('C');
pros::ADIDigitalOut wing_piston_right('D');

// Define sensors (excluding IMU)
pros::ADIAnalogIn catapult_rotation_sensor('B');

void initialize() {

  // Stop the user from doing anything while legacy ports configure.
  pros::delay(500);

  chassis.set_active_brake(0.1);
  chassis.set_curve_default(0, 0);

  default_constants();
  exit_condition_defaults();

  // Define autons for the selector
  ez::as::auton_selector.add_autons({
      Auton("Same Zone AWP\n\nstart on the right side, score 4 triballs, end touching the elevation bar",
            same_zone_awp),
      Auton("Test Auton\n\nchat is this real", test_auton),
      Auton("Opposite Zone AutonWinPoint\n\nstart on the left side, score 4 triballs?, end touching the elevation bar",
            opposite_zone_awp),
      Auton("Opposite Zone Eliminations\n\nstart on the left side, the rest is TBD",
            opposite_zone_elim),
      Auton("Same Zone Steal\n\nstart on the right side, steal the middle triballs, score preload ", same_zone_steal),
  });

  // Set the motor brake modes
  catapult.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

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
  // TODO Automatically deactivate the endgame
  pto_toggle(false);
  while (true) {
    // Handle chassis control
    chassis.tank();

    // Handle pto control
    pto_control();

    // Handle intake control
    intake_control();

    // Handle wing control
    wing_control();

    // Handle catapult control
    catapult_control();

    // Print to the controller screen
    // ? Why doesnt this work
    print_stats_controller();

    // Keep the time between cycles constant
    pros::delay(ez::util::DELAY_TIME);
  }
}
