#include "main.h"
#include "helpers.hpp"
#include "okapi/api.hpp"

// Define the okapi controller
okapi::Controller controller;
// ⁡⁣⁢⁣(left_motor_ports, right_motor_ports, imu_port, wheel_diameter, ticks, ratio);⁡
Drive chassis({-15, 9, -17},{8, -10, 2}, 20, 4.125, 200, 0.5);

// Define the reused motor variables
okapi::AbstractMotor::gearset default_ratio = okapi::AbstractMotor::gearset::green;
okapi::AbstractMotor::gearset speed_ratio = okapi::AbstractMotor::gearset::blue;
okapi::AbstractMotor::encoderUnits default_encoder_units = okapi::AbstractMotor::encoderUnits::degrees;
pros::Motor& PTO_left = chassis.left_motors[1];
pros::Motor& PTO_right = chassis.right_motors[1];
pros::ADIDigitalOut PTO_piston('A');
bool pto_intake_enabled = false;

void pto_intake(bool toggle) {
  pto_intake_enabled = toggle;
  chassis.pto_toggle({PTO_left, PTO_right}, toggle);
  PTO_piston.set_value(!toggle); 
  if (toggle) {
    PTO_left.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    PTO_right.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  }
}

void set_intake(int volts){
  if(!pto_intake_enabled) return;
  PTO_left = volts;
  PTO_right = volts;
}

void intake_control(){
  //handle turning on pto
  if(master.get_digital(DIGITAL_A)) pto_intake(!pto_intake_enabled);
  else if(master.get_digital(DIGITAL_LEFT)) pto_intake(0);
  else if(master.get_digital(DIGITAL_RIGHT)) pto_intake(1);
  //move with buttons if pto :3
  if (master.get_digital(DIGITAL_L1)) set_intake(127);
  else if (master.get_digital(DIGITAL_L2)) set_intake(-127);
  else set_intake(0);
}

void initialize() {

  // Stop the user from doing anything while legacy ports configure.
  pros::delay(500);

  chassis.toggle_modify_curve_with_controller(false);

  chassis.set_active_brake(0.1);
  chassis.set_curve_default(0, 0);

  default_constants(); 
  exit_condition_defaults();
  ez::as::auton_selector.add_autons({
      // Auton("Test Auton\n\nchat is this real", test_auton),
      Auton("Opposite Zone AWP\n\nstart on the right side, get half awp", opposite_zone_awp),
      Auton("Same Zone AutonWinPoint\n\nstart on the left side, get half awp", same_zone_awp),
      Auton("Opposite Zone Score\n\nstart on the right side, get 3<=x<=3 triballs", opposite_zone_score),
  });

  // Set the motor brake modes
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD);
  chassis.initialize();
  ez::as::initialize();

  pto_intake(false);
}

void autonomous() {
  chassis.reset_pid_targets();
  chassis.reset_gyro();
  chassis.reset_drive_sensor();
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD);

  ez::as::auton_selector.call_selected_auton();
}

void opcontrol() {
  while (true) {
  chassis.set_drive_brake(MOTOR_BRAKE_BRAKE);
    // Handle the drive movement
    chassis.tank();
    intake_control();
    
    // Define the controller buttons
    okapi::ControllerButton buttonL1 = controller[okapi::ControllerDigital::L1];
    okapi::ControllerButton buttonL2 = controller[okapi::ControllerDigital::L2];
    okapi::ControllerButton buttonR1 = controller[okapi::ControllerDigital::R1];
    okapi::ControllerButton buttonR2 = controller[okapi::ControllerDigital::R2];
    okapi::ControllerButton buttonB = controller[okapi::ControllerDigital::B];
    okapi::ControllerButton buttonA = controller[okapi::ControllerDigital::A];
    okapi::ControllerButton buttonUp = controller[okapi::ControllerDigital::up];
    okapi::ControllerButton buttonDown = controller[okapi::ControllerDigital::down];
    okapi::ControllerButton buttonLeft = controller[okapi::ControllerDigital::left];
    okapi::ControllerButton buttonRight = controller[okapi::ControllerDigital::right];

    pros::delay(ez::util::DELAY_TIME);
  }
}
