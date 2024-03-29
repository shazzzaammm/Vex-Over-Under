#include "main.h"

void initialize() {

  // Stop the user from doing anything while legacy ports configure.
  pros::delay(500);
  chassis.toggle_modify_curve_with_controller(false);
  chassis.set_active_brake(0.1);

  // Set the constants
  default_constants();
  exit_condition_defaults();

  // Define autons for the selector
  ez::as::auton_selector.add_autons({
      Auton("Skills", skills),
      Auton("Five Ball Elim", five_ball_elim),
      Auton("Bowl Auton", bowl_auton),
      Auton("Closer awp", closer_awp),
      Auton("Close awp", close_awp),
      Auton("Five Ball Qual", five_ball_qual),
      Auton("Test Auton", test_auton),
  });

  // Initialize
  chassis.initialize();
  ez::as::initialize();

  // Switch to 6 motor
  pto_toggle(true);
}

void autonomous() {
  chassis.reset_pid_targets();
  chassis.reset_gyro();
  chassis.reset_drive_sensor();
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD);

  ez::as::auton_selector.call_selected_auton();
}

void opcontrol() {
  // Handle printing stats to the controller
  master.clear();

  // Uncommented this only when we were running skills
  // skills_macro();
  pros::Task controller_task(controller_stats_task, NULL, "Controller Print Task");
  while (true) {
    // Handle chassis control
    chassis_control();

    // Handle pto control
    pto_control();

    // Handle intake control
    intake_control();

    // Handle slapper control
    slapper_control();

    // Handle wing control
    wing_control();

    // Handle endgame control
    endgame_control();

    // Handle debug information
    print_debug();

    // Keep the time between cycles constant
    pros::delay(ez::util::DELAY_TIME);
  }
}
