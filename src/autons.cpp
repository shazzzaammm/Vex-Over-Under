#include "helpers.hpp"
#include "main.h"

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
  return;
}

void same_zone_awp() {
  wing_toggle(true);
  chassis.set_drive_pid(12, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -20, SWING_SPEED);
  chassis.wait_drive();

  wing_toggle(false);

  chassis.set_drive_pid(25, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-46, TURN_SPEED);
  chassis.wait_drive();

  set_intake_volts(8000);

  chassis.set_drive_pid(11.5, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-15, DRIVE_SPEED);
  chassis.wait_drive();

  set_intake_volts(0);

  chassis.set_drive_pid(20, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-17, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-123, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(36, DRIVE_SPEED);
  chassis.wait_drive();

  set_intake_volts(12000);

  chassis.set_drive_pid(40, DRIVE_SPEED);
  chassis.wait_drive();

  // wing_toggle(true);
}

void opposite_zone_awp() {
  return;
}
void opposite_zone_elim() {
  return;
}