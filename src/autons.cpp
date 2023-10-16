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
  chassis.set_drive_pid(10, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(10, DRIVE_SPEED, true);
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
  charge_catapult();
  // drive forward 
  chassis.set_drive_pid(52.8, DRIVE_SPEED, true);
  chassis.wait_drive();
  // turn right
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  // shoot cata
  shoot_catapult();
  pros::delay(350);
  // turn left
  chassis.set_turn_pid(-150, TURN_SPEED);
  chassis.wait_drive();
  // move forward
  chassis.set_drive_pid(4.5, DRIVE_SPEED);
  chassis.wait_drive();
  // intake 
  spin_intake_for(2024);
  pros::delay(600);
  // turn right
  chassis.set_turn_pid(150, TURN_SPEED);
  chassis.wait_drive();
  // shoot cata
  shoot_catapult();
  pros::delay(350);
  // turn left
  chassis.set_turn_pid(-167, TURN_SPEED);  
  chassis.wait_drive();
  // drive forward
  chassis.set_drive_pid(14, DRIVE_SPEED);
  chassis.wait_drive();
  // intake
  spin_intake_for(2024);
  pros::delay(600);
  // turn right
  chassis.set_turn_pid(167, TURN_SPEED);  
  chassis.wait_drive();
  // shoot cata
  shoot_catapult();
  pros::delay(350);
  // turn right
  chassis.set_turn_pid(32, TURN_SPEED);
  chassis.wait_drive();
  // drive forward
  chassis.set_drive_pid(9.5, DRIVE_SPEED);
  chassis.wait_drive();
  // turn left
  chassis.set_turn_pid(105, TURN_SPEED);
  chassis.wait_drive();
  // drive forward
  chassis.set_drive_pid(9.25, DRIVE_SPEED);
  chassis.wait_drive();
  // intake
  spin_intake_for(2024);
  pros::delay(600);
  // turn right
  chassis.set_turn_pid(-153, TURN_SPEED);
  chassis.wait_drive();
  // shoot cata
  shoot_catapult();
  pros::delay(350);
  // turn right
  chassis.set_turn_pid(52, TURN_SPEED);
  chassis.wait_drive();
  // drive forward
  chassis.set_drive_pid(20, DRIVE_SPEED);
  chassis.wait_drive();
}