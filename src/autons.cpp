#include "helpers.hpp"
#include "main.h"
#include "okapi/api.hpp"

// extern okapi::MotorGroup flywheel;
// extern okapi::MotorGroup intake;
// extern pros::ADIDigitalOut indexer;
// extern pros::ADIDigitalOut expansion;

const int DRIVE_SPEED = 115;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;
const int CLAW_TRIBALL_DIST = 80;

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

void test_auton(){
  chassis.set_drive_pid(10, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(10, DRIVE_SPEED, true);
}

void same_zone_awp(){
  chassis.set_drive_pid(4, DRIVE_SPEED, false);
  chassis.wait_drive();

  move_claw(CLAW_TRIBALL_DIST);

  chassis.set_drive_pid(-10, DRIVE_SPEED, false);
  chassis.wait_drive();
  
  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();
  
  chassis.set_drive_pid(8, DRIVE_SPEED, false);
  chassis.wait_drive();

  move_claw(-CLAW_TRIBALL_DIST);

  chassis.set_turn_pid(-120, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(15, DRIVE_SPEED, true);
  chassis.wait_drive();

  // GRAB_POLE();

}

void opposite_zone_awp(){
  chassis.set_drive_pid(4, DRIVE_SPEED, false);
  chassis.wait_drive();

  move_claw(CLAW_TRIBALL_DIST);
  chassis.set_drive_pid(-10, DRIVE_SPEED, false);
  chassis.wait_drive();
  
  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();
  
  chassis.set_drive_pid(8, DRIVE_SPEED, false);
  chassis.wait_drive();

  move_claw(-CLAW_TRIBALL_DIST);

  chassis.set_turn_pid(120, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(15, DRIVE_SPEED, true);
  chassis.wait_drive();

  // GRAB_POLE();

}

void opposite_zone_score(){
  chassis.set_drive_pid(4, DRIVE_SPEED, false);
  chassis.wait_drive();

  move_claw(CLAW_TRIBALL_DIST);

  chassis.set_drive_pid(-10, DRIVE_SPEED, false);
  chassis.wait_drive();
  
  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();
  
  chassis.set_drive_pid(8, DRIVE_SPEED, false);
  chassis.wait_drive();

  move_claw(-CLAW_TRIBALL_DIST);

  chassis.set_turn_pid(110, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(16, DRIVE_SPEED, true);
  chassis.wait_drive();

  move_claw(CLAW_TRIBALL_DIST);

  chassis.set_drive_pid(-15, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();

  move_claw(-CLAW_TRIBALL_DIST);

  chassis.set_drive_pid(-1, DRIVE_SPEED, false);
  chassis.wait_drive();

  chassis.set_turn_pid(125, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(45, DRIVE_SPEED, true);
  chassis.wait_drive();

  move_claw(CLAW_TRIBALL_DIST);

  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(45, DRIVE_SPEED, true);
  chassis.wait_drive();

  move_claw(-CLAW_TRIBALL_DIST);

  chassis.set_drive_pid(-5, DRIVE_SPEED, false);
  chassis.wait_drive();
}
// void match_non_roller() {
//   pros::Task start_fw_1{[=] {
//     run_auton_flywheel(495);
//   }};
//   chassis.set_drive_pid(13, DRIVE_SPEED, true);
//   chassis.wait_drive();
//   chassis.set_turn_pid(20, TURN_SPEED);
//   chassis.wait_drive();
//   pros::delay(2200);
//   toggle_indexer();
//   pros::delay(1250);
//   toggle_indexer();
//   chassis.set_turn_pid(-160, TURN_SPEED);
//   start_fw_1.remove();
//   stop_auton_flywheel();
//   chassis.wait_drive();
//   intake.moveVoltage(12000);
//   chassis.set_drive_pid(-11, DRIVE_SPEED, true);
//   chassis.wait_drive();
//   chassis.set_turn_pid(-45, TURN_SPEED);
//   chassis.wait_drive();
//   pros::Task start_fw_2{[=] {
//     run_auton_flywheel(485);
//   }};
//   chassis.set_drive_pid(-27, DRIVE_SPEED, true);
//   chassis.wait_drive();
//   intake.moveVoltage(0);
//   chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
//   chassis.wait_drive();
//   intake.moveRelative(-110, 200);
//   pros::delay(500);
//   chassis.set_drive_pid(3, DRIVE_SPEED, true);
//   chassis.wait_drive();
//   chassis.set_turn_pid(4, TURN_SPEED);
//   chassis.wait_drive();
//   toggle_indexer();
//   start_fw_2.remove();
//   stop_auton_flywheel();
// }

