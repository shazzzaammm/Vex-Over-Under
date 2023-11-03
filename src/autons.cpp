#include "helpers.hpp"
#include "main.h"

extern pros::Motor& PTO_left;
extern pros::Motor& PTO_right;

const int DRIVE_SPEED = 115;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void test_auton() {
  // Test the task functionality
  pros::Task cata_charge_task(catapult_auton_task, NULL, "Cata Charge Task");

  // Wait for a while
  pros::delay(4000);

  // Stop charging the cata
  cata_charge_task.remove();

  // Test the intake (mostly to show that the auton can keep running)
  spin_intake_for(420);
}

void same_zone_steal() {
  // Drive towards the center
  chassis.set_drive_pid(41, DRIVE_SPEED);
  chassis.wait_drive();

  // Enable wings
  wing_toggle(true);

  // Turn towards triballs
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  // Drive into the triballs (hitting with wings)
  chassis.set_drive_pid(10, DRIVE_SPEED);
  chassis.wait_drive();

  // Turn towards goal (pushing triballs towards our side and away from center)
  chassis.set_turn_pid(270, TURN_SPEED);
  chassis.wait_until(180);
  // Retract wings while turning
  wing_toggle(false);
  chassis.wait_drive();

  // Drive into the goal (this scores because our intake floats)
  chassis.set_drive_pid(19, DRIVE_SPEED);
  chassis.wait_drive();

  // Back away from the goal
  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();

  // Turn towards the elevation bar
  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();

  // Drive towards the bar
  chassis.set_drive_pid(40, DRIVE_SPEED);
  chassis.wait_drive();

  // Turn to face the bar with endgame
  chassis.set_turn_pid(270, TURN_SPEED);
  chassis.wait_drive();

  // Drive towards the bar
  chassis.set_drive_pid(-25, DRIVE_SPEED);
  chassis.wait_until(-15);

  // Change PTO to 4 motor drive while driving
  pto_toggle(true);
  chassis.wait_drive();

  // Toggle endgame once the robot reaches the bar
  toggle_endgame(true);
}

void same_zone_awp() {
  // Drive forward
  chassis.set_drive_pid(69, DRIVE_SPEED);
  chassis.wait_drive();

  // Drop preload
  spin_intake_for(360);
  pros::delay(500);
}

void opposite_zone_awp() {
  return;
}