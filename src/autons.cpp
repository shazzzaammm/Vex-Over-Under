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
  // test the drive
  chassis.set_drive_pid(10, DRIVE_SPEED, false);
  chassis.wait_drive();
  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(10, DRIVE_SPEED, false);
  chassis.wait_drive();

  // test the intake
  spin_intake_for(500);

  // test the PTO
  pto_toggle(true);

  // test the endgame
  toggle_endgame(true);

  // test the wings????
  // TODO ask how wings are going to work
}

void same_zone_score() {
  // charge cata
  // drive forward
  // turn left
  // shoot cata
  // turn right
  // charge cata
  // drive forward
  // intake
  // shoot cata
  // charge cata
  // drive forward
  // intake
  // shoot cata
  // turn right
  // drive forward
  // intake
  // drive backwards
  // turn right
  // shoot cata
  // turn left
  // drive forward
  // shift PTO
  // grab pole
  // charge cata
}

void opposite_zone_awp() {
  // Drive forward
  chassis.set_drive_pid(69, DRIVE_SPEED, true);
  chassis.wait_drive();
  
  // Face enemy goal
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  
  // Shoot cata
  shoot_catapult();
  pros::delay(100);
  
  // Face first triball
  chassis.set_turn_pid(40, TURN_SPEED);
  chassis.wait_drive();
  
  // Move forward
  chassis.set_drive_pid(2.5, DRIVE_SPEED / 2);
  chassis.wait_drive();
  
  // Intake
  spin_intake_for(2024);
  pros::delay(500);
  
  // Face alliance goal
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  
  // Shoot cata
  shoot_catapult();
  pros::delay(150);
  
  // Drive forward
  chassis.set_drive_pid(25, DRIVE_SPEED);
  chassis.wait_drive();
  
  // Face second triball
  chassis.set_turn_pid(40, TURN_SPEED);
  chassis.wait_drive();
  
  // Drive forward
  chassis.set_drive_pid(5, DRIVE_SPEED);
  chassis.wait_drive();
  
  // Intake
  spin_intake_for(2024);
  pros::delay(500);
  
  // Drive backward
  chassis.set_drive_pid(-5, DRIVE_SPEED);
  chassis.wait_drive();
  
  // Face alliance goal
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  
  // Shoot cata
  shoot_catapult();
  pros::delay(150);
  
  // Drive backwards
  chassis.set_drive_pid(-30, DRIVE_SPEED);
  chassis.wait_drive();
  
  // Face forward
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  
  // Drive backwards towards endgame
  chassis.set_drive_pid(-69, DRIVE_SPEED);
  chassis.wait_drive();
  
  // Turn away from endgame
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  
  // Drive backwards to endgame
  chassis.set_drive_pid(-40, DRIVE_SPEED);
  chassis.wait_drive();
  
  // Swap pid to endgame
  pto_toggle(true);
  pros::delay(250);
  
  // Do the endgame thing
  toggle_endgame(true);
}