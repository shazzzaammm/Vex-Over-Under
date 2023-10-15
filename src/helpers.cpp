#include "main.h"


extern bool pto_intake_enabled;
extern float pto_cooldown;
extern pros::Motor& PTO_left;
extern pros::Motor& PTO_right;
extern pros::ADIDigitalOut PTO_piston;
extern pros::Motor intake_left;
extern pros::Motor intake_right;
extern pros::Motor catapult_left;
extern pros::Motor catapult_right;

const int intake_max_speed = 127;

void rumble_controller() {
  master.rumble("...."); //⁡⁢⁣⁢THIS USES MORSE CODE!!!!⁡
}

void charge_catapult(){
  return;
}

void shoot_catapult(){
  return;
}

void spin_intake_for(float dist){
  intake_left.move_relative(dist, intake_max_speed);
  intake_right.move_relative(dist, intake_max_speed);
}

void set_intake_volts(int volts){
  intake_left.move(volts);
  intake_right.move(volts);
}

void pto_toggle(bool toggle) {
  //This prevents extreme air loss using a cooldown
  if (pto_cooldown > 0) {
    return;
  }
  pto_cooldown = ez::util::DELAY_TIME * 10;
  pto_intake_enabled = toggle;
  chassis.pto_toggle({PTO_left, PTO_right}, toggle);

  //⁡⁢⁢⁣TODO ⁡make sure this line isnt the issue in the chassis
  PTO_piston.set_value(!toggle);
  if (toggle) {
    PTO_left.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    PTO_right.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  }
}

void set_pto_volts(int volts) {
  if (!pto_intake_enabled)
    return;
  // Sets intake voltage to the input value
  PTO_left = volts;
  PTO_right = volts;
}

void pto_control() {
  // Handle PTO activation /deactivation
  if (master.get_digital(DIGITAL_A))
    pto_toggle(!pto_intake_enabled);
  else if (master.get_digital(DIGITAL_DOWN))
    pto_toggle(0);
  else if (master.get_digital(DIGITAL_UP))
    pto_toggle(1);
  //move with buttons if PTO set to intake :3
  if (master.get_digital(DIGITAL_L1))
    set_pto_volts(127);
  else if (master.get_digital(DIGITAL_L2))
    set_pto_volts(-127);
  else
    set_pto_volts(0);
}