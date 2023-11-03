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
  return;
}

void same_zone_steal() {
  return;
}

void same_zone_awp() {
  return;
}

void opposite_zone_awp() {
  pros::Task cata_charge_task(catapult_auton_task, NULL, "Cata Charge Task");
  // Drive forward
  chassis.set_drive_pid(69, DRIVE_SPEED, true);
  chassis.wait_drive();

  // Face enemy goal
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();

  // Ram into goal
  chassis.set_drive_pid(12, DRIVE_SPEED);
  chassis.wait_drive();

  // Outtake
  spin_intake_for(360);
  pros::delay(500);

  // Back up
  chassis.set_drive_pid(-10.5, DRIVE_SPEED);
  chassis.wait_drive();

  // Ram into goal again
  chassis.set_drive_pid(11.5, DRIVE_SPEED);
  chassis.wait_drive();

  // Outtake again
  spin_intake_for(360);
  pros::delay(500);

  // Stop charging the catapult (prevent overheating)
  cata_charge_task.remove();

  // Back away from goal
  chassis.set_drive_pid(-10.5, DRIVE_SPEED);
  chassis.wait_drive();

  // Turn towards triballs
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  // Activate wings
  wing_toggle(true);
  spin_intake_for(-3000);

  // Drive forward
  chassis.set_drive_pid(20, DRIVE_SPEED);
  chassis.wait_drive();

  // Swing to steal the triballs
  chassis.set_swing_pid(ez::LEFT_SWING, 180, SWING_SPEED);
  chassis.wait_drive();

  // Drive forward
  chassis.set_drive_pid(20, DRIVE_SPEED);
  chassis.wait_drive();

  // Turn left
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();

  // Route towards the endgame
  chassis.set_drive_pid(40, DRIVE_SPEED);
  chassis.wait_until(20);

  // Turn off pto when convienient
  pto_toggle(true);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // Turn on endgame
  toggle_endgame(true);
}