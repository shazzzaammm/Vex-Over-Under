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
void spline_exit_condition() {
  // chassis.set_exit_condition(chassis.drive_exit, 8, 8, 30, 150, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
  chassis.set_exit_condition(chassis.turn_exit, 10, 3, 1, 25, 500, 500);
}

void test_auton() {
  chassis.set_drive_pid(50, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-50, DRIVE_SPEED);
  chassis.wait_drive();
}

void same_zone_steal() {}

void same_zone_elim() {
  int OFFSET = 45;
  
  wing_toggle(true);
  
  chassis.set_drive_pid(60, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(RIGHT_SWING, 0 - OFFSET, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(85, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-65, DRIVE_SPEED);
  chassis.wait_drive();

  wing_toggle(false);

  chassis.set_turn_pid(-45 - OFFSET, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(195, DRIVE_SPEED);
  chassis.wait_drive();

  wing_toggle(true);

  chassis.set_turn_pid(180 -OFFSET, TURN_SPEED);
  chassis.wait_drive();
}

void opposite_zone_awp() {
  int OFFSET = 135;
  chassis.set_drive_pid(-20, DRIVE_SPEED);
  chassis.wait_drive();

  wing_toggle(true);

  chassis.set_drive_pid(-55, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(230 - OFFSET, 75);
  chassis.wait_drive();

  wing_toggle(false);

  chassis.set_drive_pid(-235, DRIVE_SPEED);
  chassis.wait_drive();

  wing_toggle(true);

  chassis.set_turn_pid(360 - OFFSET, TURN_SPEED);
  chassis.wait_drive();

  wing_toggle(false);

  chassis.set_drive_pid(-80, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(180 - OFFSET, TURN_SPEED);
  chassis.wait_drive();

  wing_toggle(true);

  chassis.set_drive_pid(500, 127);
  chassis.wait_drive();
}

void opposite_zone_elim() {
  pto_toggle(false);

  chassis.set_drive_pid(200, DRIVE_SPEED, false);
  chassis.wait_until(180);
  wing_toggle(true);
  chassis.wait_drive();

  chassis.set_turn_pid(-90, TURN_SPEED);
  wing_toggle(false);
  chassis.wait_drive();

  chassis.set_drive_pid(40, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-50, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  wing_toggle(true);

  chassis.set_drive_pid(115, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-25, DRIVE_SPEED);
  chassis.wait_drive();

  wing_toggle(false);

  chassis.set_turn_pid(220, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(175, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(RIGHT_SWING, -40, 127);
  chassis.wait_drive();
}