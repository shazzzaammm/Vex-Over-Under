#include "main.h"

extern bool pto_endgame_enabled;
extern float pto_cooldown;
extern pros::Motor& PTO_left;
extern pros::Motor& PTO_right;
extern pros::ADIDigitalOut PTO_piston;
extern pros::Motor intake_left;
extern pros::Motor intake_right;
extern pros::Motor catapult_left;
extern pros::Motor catapult_right;

const int INTAKE_SPEED = 127;
const int CATAPULT_SPEED = 127;
const int RELATIVE_CHARGE_DIST = 720;
const int RELATIVE_SHOOT_DIST = 50;
void rumble_controller() {
  master.rumble("....");  //⁡⁢⁣⁢THIS USES MORSE CODE!!!!⁡
}

void print_stats_controller(bool pto) {
  master.set_text(0, 0, pto ? "6 motor" : "4 motor");
}

void move_catapult(int degrees) {
  catapult_left.move_relative(degrees, CATAPULT_SPEED);
  catapult_right.move_relative(degrees, CATAPULT_SPEED);
}

void charge_catapult() {
  // Charge the catapult (not likely to be used often)
  move_catapult(RELATIVE_CHARGE_DIST);
}

void shoot_catapult() {
  // Shoot the catapult and recharge it
  move_catapult(RELATIVE_SHOOT_DIST + RELATIVE_CHARGE_DIST);
  return;
}

void spin_intake_for(float dist) {
  intake_left.move_relative(dist, INTAKE_SPEED);
  intake_right.move_relative(dist, INTAKE_SPEED);
}

void set_intake_volts(int volts) {
  intake_left.move_voltage(volts);
  intake_right.move_voltage(volts);
}

void pto_toggle(bool toggle) {
  //This prevents extreme air loss using a cooldown
  if (pto_cooldown > 0) {
    return;
  }
  pto_cooldown = ez::util::DELAY_TIME * 50;
  pto_endgame_enabled = toggle;
  chassis.pto_toggle({PTO_left, PTO_right}, toggle);

  //⁡⁢⁢⁣TODO ⁡make sure this line isnt the issue in the chassis
  PTO_piston.set_value(!toggle);
  if (toggle) {
    PTO_left.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    PTO_right.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  }
}

void set_pto_volts(int volts) {
  if (!pto_endgame_enabled)
    return;
  // Sets intake voltage to the input value
  PTO_left = volts;
  PTO_right = volts;
}

void intake_control(){
  if(master.get_digital(DIGITAL_L1)){
    set_intake_volts(12000);
  }
  else if(master.get_digital(DIGITAL_L2)){
    set_intake_volts(-12000);
  }
  else{
    set_intake_volts(0);
  }
}

void pto_control() {
  // Handle PTO activation /deactivation
  if (master.get_digital(DIGITAL_A))
    pto_toggle(!pto_endgame_enabled);
  else if (master.get_digital(DIGITAL_DOWN))
    pto_toggle(0);
  else if (master.get_digital(DIGITAL_UP))
    pto_toggle(1);
  // Move with buttons if PTO set to endgame :3
  // Likely to be replaced with a different control scheme
  if (master.get_digital(DIGITAL_L1))
    set_pto_volts(127);
  else if (master.get_digital(DIGITAL_L2))
    set_pto_volts(-127);
  else
    set_pto_volts(0);
}