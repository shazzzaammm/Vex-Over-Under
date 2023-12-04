#include "main.h"

// Define the chassis (PTO motors are last in the curly braces)
Drive chassis({1, -2, -4, 10}, {3, 5, -6, -9}, 20, 4.125, 600, 0.5);

// Define Motors
pros::Motor& PTO_intake = chassis.right_motors[3];
pros::Motor& PTO_catapult = chassis.left_motors[3];

// Define Pneumatics
pros::ADIDigitalOut PTO_piston('H');
pros::ADIDigitalOut wing_piston_left('A');
pros::ADIDigitalOut wing_piston_right('B');

// Define Sensors
pros::Optical cata_optic_sensor(19);
pros::Rotation cata_rotation_sensor(11);

// Get Debug Variables
extern bool pto_6_motor_enabled;
extern bool catapult_auto_shoot_enabled;

void initialize() {

  // Stop the user from doing anything while legacy ports configure.
  pros::delay(500);
  chassis.toggle_modify_curve_with_controller(false);
  chassis.set_active_brake(0.1);

  default_constants();
  exit_condition_defaults();

  // Define autons for the selector
  ez::as::auton_selector.add_autons({
      Auton("Test Auton\n\nchat is this real", test_auton),
      Auton("Same Zone AWP\n\nstart on the right side, score 4 triballs, end touching the elevation bar",
            same_zone_awp),
      Auton("Opposite Zone AutonWinPoint\n\nstart on the left side, score 4 triballs?, end touching the elevation bar",
            opposite_zone_awp),
      Auton("Opposite Zone Eliminations\n\nstart on the left side, the rest is TBD", opposite_zone_elim),
      Auton("Same Zone Steal\n\nstart on the right side, steal the middle triballs, score preload ", same_zone_steal),
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

    // Handle catapult control
    catapult_control();

    // Debug
    std::string drive_mode = pto_6_motor_enabled ? "6 motor" : "8 motor";
    std::string triball_status = isSlapperFull() ? "triball loaded" : "no triball loaded";
    std::string auto_shoot_status = catapult_auto_shoot_enabled ? "enabled" : "disabled";
    std::string cata_charged_status = isCataCharged() ? "charged" : "not charged";
    print_to_screen("drive mode: " + drive_mode, 0);
    print_to_screen("optic brightness: " + std::to_string(cata_optic_sensor.get_brightness()), 1);
    print_to_screen("triball status: " + triball_status, 2);
    print_to_screen("cata auto shoot: " + auto_shoot_status, 3);
    print_to_screen("cata charged status: " + cata_charged_status, 4);
    print_to_screen("cata temp: " + std::to_string(PTO_catapult.get_temperature()) + "C", 5);
    print_to_screen("battery level: " + std::to_string(pros::battery::get_capacity()) + "%", 6);
    
    // Keep the time between cycles constant
    pros::delay(ez::util::DELAY_TIME);
  }
}
