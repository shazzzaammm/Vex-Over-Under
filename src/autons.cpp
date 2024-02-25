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
  // chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  // chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  // chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 100, 7, 100, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 50, 7, 100, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 50, 150, 100, 500);
}

double map_inches_to_pid(double inches) {
  return inches * 3.6;
}

void test_auton() {
  chassis.set_swing_pid(ez::LEFT_SWING, 90, SWING_SPEED);
  chassis.wait_drive();
}

void bowl_auton() {
  // Set offset
  int offset = 10;

  // Unstow
  set_intake_volts(-12000);

  // Drive to mid triball
  chassis.set_drive_pid(map_inches_to_pid(49), DRIVE_SPEED);
  chassis.wait_until(map_inches_to_pid(20));

  // Start intaking
  set_intake_volts(12000);
  chassis.wait_drive();

  // Wait a little so it intakes
  pros::delay(200);

  // Return with triball
  chassis.set_drive_pid(map_inches_to_pid(-48), DRIVE_SPEED);
  chassis.wait_drive();

  // Turn to be parallel with match load bar
  chassis.set_turn_pid(135 - offset, TURN_SPEED);
  chassis.wait_drive();

  // Outtake to drop triball
  set_intake_volts(-12000);

  // Move towards goal
  chassis.set_drive_pid(map_inches_to_pid(-30), DRIVE_SPEED);
  chassis.wait_drive();

  // Swing to score preload
  chassis.set_swing_pid(RIGHT_SWING, 180 - offset, SWING_SPEED);
  chassis.wait_drive();

  // Turn off intake (saves power idk)
  set_intake_volts(0);

  // Turn towards match load bar thing
  chassis.set_swing_pid(RIGHT_SWING, 135 - offset, SWING_SPEED);
  chassis.wait_drive();

  // Drive towards the awp triball
  chassis.set_drive_pid(map_inches_to_pid(25), DRIVE_SPEED);
  chassis.wait_until(map_inches_to_pid(15));

  // Wings
  wing_toggle(true);
  chassis.wait_drive();

  // Clear triball
  chassis.set_swing_pid(ez::RIGHT_SWING, 105 - offset, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::LEFT_SWING, 97 - offset, SWING_SPEED);
  chassis.wait_drive();

  // Turn off wings
  wing_toggle(false);

  // Back away (space for wings)
  chassis.set_drive_pid(map_inches_to_pid(-11), DRIVE_SPEED);
  chassis.wait_drive();

  // Turn off wings
  wing_toggle(false);

  chassis.set_swing_pid(ez::RIGHT_SWING, 98 - offset, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(94 - offset, TURN_SPEED);
  chassis.wait_drive();

  set_intake_volts(-12000);

  chassis.set_drive_pid(map_inches_to_pid(30), DRIVE_SPEED);
  chassis.wait_drive();
}

void six_ball() {
  chassis.set_exit_condition(chassis.turn_exit, 25, 3, 200, 7, 500, 500);

  int offset = -90;
  pto_toggle(true);

  set_intake_volts(-12000);

  chassis.set_drive_pid(map_inches_to_pid(12), 127);
  chassis.wait_until(map_inches_to_pid(6));
  set_intake_volts(12000);
  chassis.wait_drive();

  chassis.set_drive_pid(map_inches_to_pid(-36), 127);
  chassis.wait_drive();

  chassis.set_turn_pid(45 - 180 - offset, TURN_SPEED);
  chassis.wait_drive();

  wing_toggle(true);

  chassis.set_drive_pid(map_inches_to_pid(-18), DRIVE_SPEED);
  chassis.wait_drive();

  wing_toggle(false);

  chassis.set_swing_pid(ez::LEFT_SWING, 0 - offset, 127);
  chassis.wait_drive();

  // set_intake_volts(-12000);

  // chassis.set_drive_pid(map_inches_to_pid(10), 127);
  // chassis.wait_drive();

  // chassis.set_drive_pid(map_inches_to_pid(-5), 127);
  // chassis.wait_drive();

  // set_intake_volts(0);

  // chassis.set_drive_pid(map_inches_to_pid(5), 127);
  // chassis.wait_drive();

  // chassis.set_drive_pid(map_inches_to_pid(-10), 127);
  // chassis.wait_drive();

  // chassis.set_turn_pid(-70 - offset, 127);
  // chassis.wait_drive();

  // chassis.set_drive_pid(map_inches_to_pid(50), 127);
  // chassis.wait_until(25);
  // set_intake_volts(12000);
  // chassis.wait_drive();

  // chassis.set_turn_pid(58 - offset, 127);
  // chassis.wait_drive();

  // set_intake_volts(-12000);

  // chassis.set_drive_pid(map_inches_to_pid(5), 127);
  // chassis.wait_drive();

  // chassis.set_turn_pid(-39.69 - offset, 127);
  // chassis.wait_drive();

  // set_intake_volts(12000);

  // chassis.set_drive_pid(map_inches_to_pid(22), 127);
  // chassis.wait_drive();

  // chassis.set_turn_pid(90 - offset, TURN_SPEED);
  // chassis.wait_drive();

  // wing_toggle(true);
  // set_intake_volts(-12000);

  // chassis.set_drive_pid(map_inches_to_pid(25), DRIVE_SPEED);
  // chassis.wait_drive();

  // chassis.set_drive_pid(map_inches_to_pid(-30), DRIVE_SPEED);
  // chassis.wait_drive();
}

void skills() {
  pto_toggle(true);
  int offset = 135;

  chassis.set_drive_pid(map_inches_to_pid(-12), MAX_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, 180 - offset, MAX_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(map_inches_to_pid(-13), MAX_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(map_inches_to_pid(20), MAX_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::LEFT_SWING, 220 - offset, MAX_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, 245 - offset, MAX_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(map_inches_to_pid(5), MAX_SPEED);
  chassis.wait_drive();

  // //* Start auto shoot
  // // Initialize tracking variables
  // int total_shot = 0;
  // int timer = 0;
  // bool p_full = false;
  // const int magic_number = 69;
  // const int max_time = 10000;
  // const int shoot_goal = 2;
  // while (true) {
  //   // Debug info (so we can fix it when it breaks)
  //   print_to_screen("Shot: " + std::to_string(total_shot / magic_number), 0);
  //   print_to_screen("Timer: " + std::to_string(timer), 1);

  //   // Charge if not charged
  //   if (!is_slapper_charged()) {
  //     PTO_slapper.move_voltage(12000);

  //     // If we had a triball and now we arent charged, we shot
  //     if (!p_full) {
  //       total_shot++;
  //     }
  //   }

  //   // If have triball and are charged, shoot
  //   else if (is_slapper_full() && is_slapper_charged()) {
  //     PTO_slapper.move_voltage(12000);
  //     pros::delay(3 * ez::util::DELAY_TIME);
  //   }

  //   // If we are charged but without a triball, await a triball
  //   else {
  //     PTO_slapper.move_voltage(0);
  //   }

  //   // Delay (for timer)
  //   pros::delay(ez::util::DELAY_TIME);

  //   // Update variables
  //   timer += ez::util::DELAY_TIME;
  //   p_full = is_slapper_full();

  //   // Terminate auto shoot if we shot all triballs or have been shooting for 30 seconds
  //   if (total_shot / magic_number >= shoot_goal || timer > max_time) {
  //     break;
  //   }
  // }

  // // Stop slapper
  // PTO_slapper.move_voltage(0);
  //* End auto shoot

  // Switch to eight motor
  pto_toggle(false);

  //delay
  // pros::delay(30000);
  pros::delay(5000);

  // Drive towards the mid bar
  chassis.set_drive_pid(map_inches_to_pid(-50), MAX_SPEED);
  chassis.wait_drive();

  // Align to be parallel with mid bar
  chassis.set_turn_pid(185 - offset, MAX_SPEED);
  chassis.wait_drive();

  // Clear the triballs near/touching mid bar (pole riding)
  chassis.set_drive_pid(map_inches_to_pid(-71), MAX_SPEED);
  chassis.wait_drive();

  // Move forward (for turning clearance)
  chassis.set_drive_pid(map_inches_to_pid(5), MAX_SPEED);
  chassis.wait_drive();

  // Turn perpendicular to mid bar
  chassis.set_turn_pid(-90 - offset, MAX_SPEED);
  chassis.wait_drive();

  // Drive away from mid bar
  chassis.set_drive_pid(map_inches_to_pid(20), MAX_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0 - offset, MAX_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(map_inches_to_pid(18), MAX_SPEED);
  chassis.wait_drive();

  // Turn towards alley
  chassis.set_swing_pid(ez::LEFT_SWING, 90 - offset, MAX_SPEED);
  chassis.wait_drive();

  // Drive through alley
  chassis.set_drive_pid(map_inches_to_pid(64), MAX_SPEED);
  chassis.wait_drive();

  // Turn towards the side of the goal
  chassis.set_swing_pid(ez::LEFT_SWING, 135 - offset, MAX_SPEED);
  chassis.wait_drive();

  // Drive towards the side of the goal
  chassis.set_drive_pid(map_inches_to_pid(32), MAX_SPEED);
  chassis.wait_drive();

  // Turn to face the side of the goal
  chassis.set_swing_pid(ez::LEFT_SWING, 180 - offset, MAX_SPEED);
  chassis.wait_drive();

  // Score in the side of the goal
  chassis.set_drive_pid(map_inches_to_pid(7), MAX_SPEED);
  chassis.wait_drive();

  // Back away from the goal
  chassis.set_drive_pid(map_inches_to_pid(-24), MAX_SPEED);
  chassis.wait_drive();

  // Turn away from the goal
  chassis.set_turn_pid(65 - offset, MAX_SPEED);
  chassis.wait_drive();

  // Drive towards mid bar
  chassis.set_drive_pid(map_inches_to_pid(-50), MAX_SPEED);
  chassis.wait_drive();

  // Align with goal
  chassis.set_turn_pid(-70 - offset, MAX_SPEED);
  chassis.wait_drive();

  // Wings
  wing_toggle(true);

  // Score
  chassis.set_drive_pid(map_inches_to_pid(-38), MAX_SPEED);
  chassis.wait_drive();

  wing_toggle(false);

  chassis.set_turn_pid(-100 - offset, MAX_SPEED);
  chassis.wait_drive();

  // Drive towards mid bar
  chassis.set_drive_pid(map_inches_to_pid(28), MAX_SPEED);
  chassis.wait_drive();

  // Align with goal
  chassis.set_turn_pid(-60 - offset, MAX_SPEED);
  chassis.wait_drive();

  wing_toggle(true);

  // Score
  chassis.set_drive_pid(map_inches_to_pid(-47), MAX_SPEED);
  chassis.wait_drive();

  //
  wing_toggle(false);
  
  //
  chassis.set_drive_pid(map_inches_to_pid(32), MAX_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-70 - offset, TURN_SPEED);
  chassis.wait_drive();

  wing_toggle(true);

  chassis.set_drive_pid(map_inches_to_pid(-35), DRIVE_SPEED);
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
  chassis.set_drive_pid(map_inches_to_pid(24), MAX_SPEED);
  chassis.wait_until(map_inches_to_pid(20));

  // Intake the ball under endgame bar
  set_intake_volts(12000);
  chassis.wait_drive();

  // Back up towards goal
  chassis.set_drive_pid(map_inches_to_pid(-34), MAX_SPEED);
  chassis.wait_drive();

  // Turn to be parallel with match load zone
  chassis.set_turn_pid(45 - offset, TURN_SPEED);
  chassis.wait_drive();

  // Drive towards goal
  chassis.set_drive_pid(map_inches_to_pid(18), MAX_SPEED);
  chassis.wait_drive();

  // Swing to face goal
  chassis.set_swing_pid(ez::RIGHT_SWING, 0 - offset, MAX_SPEED);
  chassis.wait_drive();

  // Outtake
  set_intake_volts(-12000);

  // Score preload and previously scored ball
  chassis.set_drive_pid(map_inches_to_pid(10), MAX_SPEED);
  chassis.wait_drive();

  // Back up
  chassis.set_drive_pid(map_inches_to_pid(-5), MAX_SPEED);
  chassis.wait_drive();

  // Turn off the intake
  set_intake_volts(0);

  // Push balls in again
  chassis.set_drive_pid(map_inches_to_pid(5), MAX_SPEED);
  chassis.wait_drive();

  // Back away from goal
  chassis.set_drive_pid(map_inches_to_pid(-10), MAX_SPEED);
  chassis.wait_drive();

  // turn towards the safe ball
  chassis.set_turn_pid(-70 - offset, MAX_SPEED);
  chassis.wait_drive();

  // drive towards safe ball, turn on intake at 1/2 distance from ball
  chassis.set_drive_pid(map_inches_to_pid(50), MAX_SPEED);
  chassis.wait_until(map_inches_to_pid(25));
  set_intake_volts(12000);
  chassis.wait_drive();

  // turn towards to get ready to outtake the triball
  chassis.set_turn_pid(58 - offset, MAX_SPEED);
  chassis.wait_until(25);
  set_intake_volts(0);
  chassis.wait_drive();

  // outtake triball towards the goal
  set_intake_volts(-12000);

  // drive forwards (to ensure ball gets out)
  chassis.set_drive_pid(map_inches_to_pid(10), MAX_SPEED);
  chassis.wait_drive();

  // drive back towards the mid bar ball
  chassis.set_drive_pid(map_inches_to_pid(-5), MAX_SPEED);
  chassis.wait_drive();

  // turn to face the mid bar ball
  chassis.set_turn_pid(-39.69 - offset, MAX_SPEED);
  chassis.wait_drive();

  // turn on intake
  set_intake_volts(12000);

  // prevent program stalling during this turn
  //? WHYYYYYYYYYYYYYYYYY????????
  chassis.set_exit_condition(chassis.turn_exit, 5, 3, 10, 7, 50, 50);

  // drive to the mid bar ball
  chassis.set_drive_pid(map_inches_to_pid(17), MAX_SPEED);
  chassis.wait_drive();

  // turn towards the goal
  chassis.set_turn_pid(90 - offset, MAX_SPEED);
  pros::delay(600);

  // bring back the accuracy
  chassis.set_exit_condition(chassis.turn_exit, 25, 3, 200, 7, 500, 500);

  // start outtaking
  set_intake_volts(-12000);

  // ram balls into the goal
  chassis.set_drive_pid(map_inches_to_pid(25), MAX_SPEED);
  chassis.wait_drive();

  // back away
  chassis.set_drive_pid(map_inches_to_pid(-10), MAX_SPEED);
  chassis.wait_drive();

  // have back facing goal
  chassis.set_turn_pid(-90 - offset, MAX_SPEED);
  chassis.wait_drive();

  // turn off the intake
  set_intake_volts(0);

  // turn on the wings
  wing_toggle(true);

  // ram the balls into the goal with wings
  chassis.set_drive_pid(map_inches_to_pid(-20), MAX_SPEED);
  pros::delay(750);
}
