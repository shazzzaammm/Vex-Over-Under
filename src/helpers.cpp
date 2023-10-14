#include "main.h"


extern bool pto_intake_enabled;
extern float pto_cooldown;
extern pros::Motor& PTO_left;
extern pros::Motor& PTO_right;
extern pros::ADIDigitalOut PTO_piston;

void rumble_controller() {
  master.rumble("...."); //⁡⁢⁣⁢THIS USES MORSE CODE!!!!⁡
}

void charge_catapult(){
  return;
}

void shoot_catapult(){
  return;
}

void pto_intake(bool toggle) {
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

void set_intake(int volts) {
  if (!pto_intake_enabled)
    return;
  // Sets intake voltage to the input value
  PTO_left = volts;
  PTO_right = volts;
}

void intake_control() {
  // Handle PTO activation /deactivation
  if (master.get_digital(DIGITAL_A))
    pto_intake(!pto_intake_enabled);
  else if (master.get_digital(DIGITAL_DOWN))
    pto_intake(0);
  else if (master.get_digital(DIGITAL_UP))
    pto_intake(1);
  //move with buttons if PTO set to intake :3
  if (master.get_digital(DIGITAL_L1))
    set_intake(127);
  else if (master.get_digital(DIGITAL_L2))
    set_intake(-127);
  else
    set_intake(0);
}