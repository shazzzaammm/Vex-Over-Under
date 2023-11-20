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
  return;
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

void opposite_zone_elim(){
  return;
}