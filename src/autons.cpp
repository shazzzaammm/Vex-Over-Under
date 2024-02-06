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

/*void skills() {
  //6 motor mode
  pto_toggle(true);

  //unstow
  set_intake_volts(-12000);

  //drive to bar
  chassis.set_drive_pid(map_inches_to_pid(-10), 127);
  chassis.wait_drive();
  chassis.set_turn_pid(75, TURN_SPEED);
  chassis.wait_drive();

  //matchload
  pros::Task shooting_task(slapper_auton_task, NULL, "Slapper Task");

  //drive under side bar & push into goal side
  chassis.set_turn_pid(100, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(map_inches_to_pid(15), DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(map_inches_to_pid(70), 127);
  chassis.wait_drive();
  chassis.set_turn_pid(50, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(map_inches_to_pid(10), 127);
  chassis.wait_drive();

  //zigzag

  //push into other goal side?

}*/

void skills() {
  /*chassis.set_turn_pid(-251, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(map_inches_to_pid(19), DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-72, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(map_inches_to_pid(28), DRIVE_SPEED);
  chassis.wait_drive();*/

  int total_shot = 0;
  int timer = 0;
  bool p_full = false;
  while (true) {
    print_to_screen("Shot: " + std::to_string(total_shot / 69), 0);
    print_to_screen("Timer: " + std::to_string(timer), 1);
    if (!is_slapper_charged()) {
      PTO_slapper.move_voltage(-12000);
      if (!p_full) {
        total_shot++;
      }
    } else if (is_slapper_full() && is_slapper_charged()) {
      PTO_slapper.move_voltage(-12000);
      pros::delay(3 * ez::util::DELAY_TIME);
    } else {
      PTO_slapper.move_voltage(0);
    }
    pros::delay(ez::util::DELAY_TIME);
    timer += ez::util::DELAY_TIME;
    p_full = is_slapper_full();
    if (total_shot / 69 >= 46 || timer >= 30000) {
      break;
    }
  }
  PTO_slapper.move_voltage(0);

  /*chassis.set_turn_pid(-91, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(map_inches_to_pid(81), DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-135, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(map_inches_to_pid(21), DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-182, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(map_inches_to_pid(18), DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-3, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(map_inches_to_pid(9), DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(map_inches_to_pid(54), DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-179, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(map_inches_to_pid(14), DRIVE_SPEED);
  chassis.wait_drive();

  //wings on

  chassis.set_turn_pid(-106, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(map_inches_to_pid(37), DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-270, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(map_inches_to_pid(37), DRIVE_SPEED);
  chassis.wait_drive();

  //wings off

  chassis.set_turn_pid(-179, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(map_inches_to_pid(17), DRIVE_SPEED);
  chassis.wait_drive();

  //wings on

  chassis.set_turn_pid(-91, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(map_inches_to_pid(35), DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-251, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(map_inches_to_pid(37), DRIVE_SPEED);
  chassis.wait_drive();

  //wings off

  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(map_inches_to_pid(18), DRIVE_SPEED);
  chassis.wait_drive();

  //wings on

  chassis.set_turn_pid(-105, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(map_inches_to_pid(25), DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-168, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(map_inches_to_pid(22), DRIVE_SPEED);
  chassis.wait_drive();

  //wings off

  chassis.set_turn_pid(-50, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(map_inches_to_pid(29), DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(map_inches_to_pid(21), DRIVE_SPEED);
  chassis.wait_drive();*/
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
  chassis.wait_until(map_inches_to_pid(20));

  // Intake the ball under endgame bar
  set_intake_volts(12000);
  chassis.wait_drive();

  // Back up towards goal
  chassis.set_drive_pid(map_inches_to_pid(-34), 127);
  chassis.wait_drive();

  // Turn to be parallel with match load zone
  chassis.set_turn_pid(45 - offset, TURN_SPEED);
  chassis.wait_drive();

  // Drive towards goal
  chassis.set_drive_pid(map_inches_to_pid(18), 127);
  chassis.wait_drive();

  // Swing to face goal
  chassis.set_swing_pid(ez::RIGHT_SWING, 0 - offset, 127);
  chassis.wait_drive();

  // Outtake
  set_intake_volts(-12000);

  // Score preload and previously scored ball
  chassis.set_drive_pid(map_inches_to_pid(10), 127);
  chassis.wait_drive();

  // Back up
  chassis.set_drive_pid(map_inches_to_pid(-5), 127);
  chassis.wait_drive();

  // Turn off the intake
  set_intake_volts(0);

  // Push balls in again
  chassis.set_drive_pid(map_inches_to_pid(5), 127);
  chassis.wait_drive();

  // Back away from goal
  chassis.set_drive_pid(map_inches_to_pid(-10), 127);
  chassis.wait_drive();

  // turn towards the safe ball
  chassis.set_turn_pid(-70 - offset, 127);
  chassis.wait_drive();

  // drive towards safe ball, turn on intake at 1/2 distance from ball
  chassis.set_drive_pid(map_inches_to_pid(50), 127);
  chassis.wait_until(map_inches_to_pid(25));
  set_intake_volts(12000);
  chassis.wait_drive();

  // turn towards to get ready to outtake the triball
  chassis.set_turn_pid(58 - offset, 127);
  chassis.wait_until(25);
  set_intake_volts(0);
  chassis.wait_drive();

  // outtake triball towards the goal
  set_intake_volts(-12000);

  // drive forwards (to ensure ball gets out)
  chassis.set_drive_pid(map_inches_to_pid(10), 127);
  chassis.wait_drive();

  // drive back towards the mid bar ball
  chassis.set_drive_pid(map_inches_to_pid(-5), 127);
  chassis.wait_drive();

  // turn to face the mid bar ball
  chassis.set_turn_pid(-39.69 - offset, 127);
  chassis.wait_drive();

  // turn on intake
  set_intake_volts(12000);

  // prevent program stalling during this turn
  //? WHYYYYYYYYYYYYYYYYY????????
  chassis.set_exit_condition(chassis.turn_exit, 5, 3, 10, 7, 50, 50);

  // drive to the mid bar ball
  chassis.set_drive_pid(map_inches_to_pid(17), 127);
  chassis.wait_drive();

  // turn towards the goal
  chassis.set_turn_pid(90 - offset, 127);
  pros::delay(600);

  // bring back the accuracy
  chassis.set_exit_condition(chassis.turn_exit, 25, 3, 200, 7, 500, 500);

  // start outtaking
  set_intake_volts(-12000);

  // ram balls into the goal
  chassis.set_drive_pid(map_inches_to_pid(25), 127);
  chassis.wait_drive();

  // back away
  chassis.set_drive_pid(map_inches_to_pid(-10), 127);
  chassis.wait_drive();

  // have back facing goal
  chassis.set_turn_pid(-90 - offset, 127);
  chassis.wait_drive();

  // turn off the intake
  set_intake_volts(0);

  // turn on the wings
  wing_toggle(true);

  // ram the balls into the goal with wings
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