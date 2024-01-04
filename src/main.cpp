#include "main.h"

void initialize() {

  // Stop the user from doing anything while legacy ports configure.
  pros::delay(500);
  chassis.toggle_modify_curve_with_controller(false);
  chassis.set_active_brake(0.1);

  default_constants();
  exit_condition_defaults();

  // Define autons for the selector
  ez::as::auton_selector.add_autons({
      Auton("Test Auton", test_auton),
      Auton("Same Zone AWP", same_zone_awp),
      Auton("Opposite Zone AutonWinPoint", opposite_zone_awp),
      Auton("Opposite Zone Eliminations", opposite_zone_elim),
      Auton("Same Zone Eliminations", same_zone_elim),
  });

  // Initialize
  chassis.initialize();
  ez::as::initialize();

  // Set PTO to 8 motor drive configuration
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
  // Default to 8 motor drive
  pto_toggle(false);

  // Handle printing stats to the controller
  master.clear();
  pros::Task controller_task(controller_stats_task, NULL, "Controller Print Task");
  while (true) {
    // Handle chassis control
    chassis_control();

    // Handle pto control
    pto_control();

    // Handle intake control
    intake_control();

    // Handle wing control
    wing_control();

    // Handle flywheel control
    flywheel_control();

    // Handle lift control
    lift_control();

    // Handle debug information
    print_debug();

    // Keep the time between cycles constant
    pros::delay(ez::util::DELAY_TIME);
  }
}
