#include "main.h"
const int DRIVE_SPEED = 115;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;
const int MAX_SPEED = 127;

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 4.69, 0, 35, 15);
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

double map_inches_to_pid(double inches) {
  return inches * 3.6;
}

void unstow(bool stay_6_motor) {
  pto_toggle(true);
  spin_intake_for(-250);
}

void test_auton() {
  chassis.set_swing_pid(ez::LEFT_SWING, 90, SWING_SPEED);
  chassis.wait_drive();
}

void five_ball() {
  // Trade turning accuracy for speed
  chassis.set_exit_condition(chassis.turn_exit, 25, 3, 200, 7, 500, 500);

  // Set the offset 
  int offset = -90;
  
  // 6 motor mode
  pto_toggle(true);

  // Unstow
  set_intake_volts(-12000);

  // Drive toward the ball under endgame bar
  chassis.set_drive_pid(map_inches_to_pid(24), 127);
  chassis.wait_until(map_inches_to_pid(14));
  
  // Intake the ball under endgame bar
  set_intake_volts(12000);
  chassis.wait_drive();

  // Back up towards goal
  chassis.set_drive_pid(map_inches_to_pid(-34), 127);
  chassis.wait_until(map_inches_to_pid(-6));
  // Stop intaking (saving power and stuff)
  set_intake_volts(0);
  chassis.wait_drive();

  // 
  chassis.set_turn_pid(45 - offset, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(map_inches_to_pid(18), 127);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, 0 - offset, 127);
  chassis.wait_drive();

  set_intake_volts(-12000);

  chassis.set_drive_pid(map_inches_to_pid(10), 127);
  chassis.wait_drive();

  chassis.set_drive_pid(map_inches_to_pid(-5), 127);
  chassis.wait_drive();

  set_intake_volts(0);

  chassis.set_drive_pid(map_inches_to_pid(5), 127);
  chassis.wait_drive();

  chassis.set_drive_pid(map_inches_to_pid(-10), 127);
  chassis.wait_drive();

  chassis.set_turn_pid(-70 - offset, 127);
  chassis.wait_drive();

  chassis.set_drive_pid(map_inches_to_pid(50), 127);
  chassis.wait_until(map_inches_to_pid(25));
  set_intake_volts(12000);
  chassis.wait_drive();

  chassis.set_turn_pid(58 - offset, 127);
  chassis.wait_until(25);
  set_intake_volts(0);
  chassis.wait_drive();

  set_intake_volts(-12000);

  chassis.set_drive_pid(map_inches_to_pid(10), 127);
  chassis.wait_drive();

  chassis.set_drive_pid(map_inches_to_pid(-5), 127);
  chassis.wait_drive();

  chassis.set_turn_pid(-39.69 - offset, 127);
  chassis.wait_drive();

  set_intake_volts(12000);
  chassis.set_exit_condition(chassis.turn_exit, 5, 3, 10, 7, 50, 50);

  chassis.set_drive_pid(map_inches_to_pid(17), 127);
  chassis.wait_drive();

  chassis.set_turn_pid(90 - offset, 127);
  pros::delay(600);

  chassis.set_exit_condition(chassis.turn_exit, 25, 3, 200, 7, 500, 500);

  set_intake_volts(-12000);

  chassis.set_drive_pid(map_inches_to_pid(25), 127);
  chassis.wait_drive();

  chassis.set_drive_pid(map_inches_to_pid(-10), 127);
  chassis.wait_drive();

  chassis.set_turn_pid(-90 - offset, 127); 
  chassis.wait_drive();

  set_intake_volts(0);
  wing_toggle(true);

  chassis.set_drive_pid(map_inches_to_pid(-20), 127);
  pros::delay(750);
}

void four_ball() {
  int offset = -90;
  pto_toggle(true);

  set_intake_volts(-12000);

  chassis.set_drive_pid(map_inches_to_pid(24), DRIVE_SPEED);
  chassis.wait_until(map_inches_to_pid(14));
  set_intake_volts(12000);
  chassis.wait_drive();

  chassis.set_drive_pid(map_inches_to_pid(-34), DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45 - offset, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(map_inches_to_pid(18), DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, 0 - offset, SWING_SPEED);
  chassis.wait_drive();

  set_intake_volts(-12000);

  chassis.set_drive_pid(map_inches_to_pid(11), DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(map_inches_to_pid(-5), DRIVE_SPEED);
  chassis.wait_drive();

  set_intake_volts(0);

  chassis.set_drive_pid(map_inches_to_pid(5), DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(map_inches_to_pid(-10), DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-70 - offset, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(map_inches_to_pid(50), DRIVE_SPEED);
  chassis.wait_until(25);
  set_intake_volts(12000);
  chassis.wait_drive();

  wing_toggle(true);

  chassis.set_turn_pid(0 - offset, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(map_inches_to_pid(14.5), DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::LEFT_SWING, 90 - offset, SWING_SPEED);
  chassis.wait_drive();

  set_intake_volts(-12000);
  chassis.set_drive_pid(map_inches_to_pid(23), DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(map_inches_to_pid(-10), DRIVE_SPEED);
  chassis.wait_drive();
}

void same_zone_elim() {}

void same_zone_awp() {}

void opposite_zone_awp() {}

void opposite_zone_elim() {}