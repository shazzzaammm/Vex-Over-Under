#include "main.h"

// Define the chassis (PTO motors are last in the curly braces)
Drive chassis({1, -2, -4, 10}, {3, 5, -6, -9}, 21, 4.125, 600, 0.5);

// Define Motors
pros::Motor& PTO_intake = chassis.right_motors[3];
pros::Motor& PTO_catapult = chassis.left_motors[3];

// Define pneumatics
pros::ADIDigitalOut PTO_piston('H');
pros::ADIDigitalOut wing_piston_left('A');
pros::ADIDigitalOut wing_piston_right('B');

// Define sensors
pros::Optical cata_optic_sensor(80);

extern ControlScheme selected_controls;
extern int pto_cooldown;
extern bool pto_6_motor_enabled;
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
      Auton("Opposite Zone Eliminations\n\nstart on the left side, the rest is TBD", opposite_zone_elim),
      Auton("Same Zone Steal\n\nstart on the right side, steal the middle triballs, score preload ", same_zone_steal),
  });

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

    // Handle the PTO timer
    if (pto_6_motor_enabled) {
      pto_cooldown += ez::util::DELAY_TIME;
    }

    // Change to 8 motor if driver forgot
    if (pto_cooldown > 2000 && pto_6_motor_enabled) {
      pto_toggle(false);
    }

    // ? why doesnt this work in a different file????
    if (master.get_digital_new_press(selected_controls.togglePTOButton))
      PTO_catapult.set_reversed(!PTO_catapult.is_reversed());
    // Keep the time between cycles constant
    pros::delay(ez::util::DELAY_TIME);
  }
}
