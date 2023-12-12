#include "main.h"
#include "robot_config.hpp"
#include "variables.hpp"

#pragma region brain
void print_debug() {
  std::string drive_mode = pto_6_motor_enabled ? "6 motor" : "8 motor";
  std::string triball_status = isSlapperFull() ? "triball loaded" : "no triball loaded";
  std::string auto_shoot_status = catapult_auto_shoot_enabled ? "enabled" : "disabled";
  std::string cata_charged_status = isCataCharged() ? "charged" : "not charged";
  print_to_screen("drive mode: " + drive_mode, 0);
  print_to_screen("optic brightness: " + std::to_string(cata_optic_sensor.get_brightness()), 1);
  print_to_screen("triball status: " + triball_status, 2);
  print_to_screen("cata auto shoot: " + auto_shoot_status, 3);
  print_to_screen("cata charged status: " + cata_charged_status, 4);
  print_to_screen("cata temp: " + std::to_string(PTO_catapult.get_temperature()) + "C", 5);
  print_to_screen("battery level: " + std::to_string(pros::battery::get_capacity()) + "%", 6);
}
#pragma endregion brain

#pragma region chassis
void arcade_drive() {
  // Arcade Split drive based off the joysticks and the orientation of the robot
  int forward_stick = master.get_analog(ANALOG_LEFT_Y);
  int turn_stick = master.get_analog(ANALOG_RIGHT_X);

  if (!chassis_is_reversed) {
    chassis.set_tank(forward_stick + turn_stick, forward_stick - turn_stick);
  } else {
    chassis.set_tank(-forward_stick - turn_stick, -forward_stick + turn_stick);
  }
}

void tank_drive() {
  // Tank drive based off the joysticks and the orientation of the robot
  if (!chassis_is_reversed) {
    chassis.set_tank(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_Y));
  } else {
    chassis.set_tank(-master.get_analog(ANALOG_RIGHT_Y), -master.get_analog(ANALOG_LEFT_Y));
  }
}

void drive_control(){
  // Use the drive mode the user wants
  switch (selected_controls.drive_mode)
  {
  case TANK:
    tank_drive();
    break;
  
  case ARCADE:
  arcade_drive();
    break;
  }
}

void reverse_chassis() {
  chassis_is_reversed = !chassis_is_reversed;
}

void chassis_control() {
  drive_control();
  if (master.get_digital_new_press(selected_controls.reverse_chassis_button)) {
    reverse_chassis();
  }
}
#pragma endregion chassis

#pragma region controller
void rumble_controller() {
  master.rumble(".");
}

std::string getButtonDown() {
  // Used for debugging
  if (master.get_digital(selected_controls.hold_intake_button)) {
    return "Intake Hold    ";
  }
  if (master.get_digital(selected_controls.hold_outtake_button)) {
    return "Outtake Hold   ";
  }
  if (master.get_digital(selected_controls.shoot_catapult_button)) {
    return "Catapult Hold  ";
  }
  if (master.get_digital(selected_controls.toggle_catapult_button)) {
    return "Catapult Toggle";
  }
  if (master.get_digital(selected_controls.toggle_intake_button)) {
    return "Intake Toggle  ";
  }
  if (master.get_digital(selected_controls.toggle_outtake_button)) {
    return "Outtake Toggle ";
  }
  if (master.get_digital(selected_controls.toggle_PTO_button)) {
    return "PTO Toggle     ";
  }
  if (master.get_digital(selected_controls.toggle_wings_button)) {
    return "Wings Toggle   ";
  }
  if (master.get_digital(selected_controls.reverse_chassis_button)) {
    return "Reverse Chassis";
  }
  return "No Button Down ";
}

void controller_stats_task(void* parameter) {
  int printIndex = 0;
  int loopIndex = 0;
  match_start_time = pros::millis();
  while (true) {
    // Only print every 50ms
    if (loopIndex % 5 == 0) {
      // Change which thing is printed each interval
      print_stat_to_controller(printIndex);
      printIndex++;
      printIndex %= 3;
    }
    loopIndex++;
    pros::delay(ez::util::DELAY_TIME);
  }
}

void print_stat_to_controller(int type) {
  // TODO maybe use a switch case instead
  if (pros::competition::is_disabled()) {
    if (type == 0) {
      master.set_text(0, 0, "Good Luck!!!!");
    } else if (type == 1) {
      master.clear_line(1);
    } else if (type == 2) {
      std::string auton_name = ez::as::auton_selector.Autons[ez::as::auton_selector.current_auton_page].Name;
      std::string auton_display_name = auton_name.substr(0, auton_name.find("\n", 0));
      master.set_text(1, 0, auton_display_name);
    } else {
      master.clear();
    }
    return;
  }

  if (type == 0) {
    master.set_text(0, 0, (pto_6_motor_enabled ? "Mode: 6 motor!!!!" : "Mode: 8 motor!!!!"));
  } else if (type == 1) {
    master.set_text(1, 0, getButtonDown());
  } else if (type == 2) {
    master.set_text(
        2, 0, "Time Remaining: " + std::to_string((MATCH_LENGTH + match_start_time - pros::millis()) / 1000) + "  ");
  } else {
    master.clear();
  }
}
#pragma endregion controller

#pragma region catapult
void toggle_auto_shoot_catapult() {
  catapult_auto_shoot_enabled = !catapult_auto_shoot_enabled;
}

bool isSlapperFull() {
  return cata_optic_sensor.get_brightness() < TRIBALL_LOADED_BRIGHTNESS;
}

bool isCataCharged() {
  return cata_rotation_sensor.get_angle() < CATAPULT_CHARGED_DEGREES;
}

void catapult_control() {
  // Make sure the catapult is moving the correct direction
  PTO_catapult.set_reversed(pto_6_motor_enabled);

  // Only move cata if we are in 6 motor
  if (!pto_6_motor_enabled) {
    return;
  }

  // Toggle automatic shooting (for match loading)
  if (master.get_digital_new_press(selected_controls.toggle_catapult_button)) {
    toggle_auto_shoot_catapult();
  }

  // Shoot the catapult automatically, shoot the catapult manually, or charge the catapult automatically
  if (master.get_digital(selected_controls.shoot_catapult_button) || (isSlapperFull() && toggle_auto_shoot_catapult) ||
      !isCataCharged()) {
    PTO_catapult.move_voltage(CATAPULT_SHOOTING_VOLTAGE);
  }

  // Stop the catapult unless we are in 8 motor drive
  else if (pto_6_motor_enabled) {
    PTO_catapult.brake();
  }
}
#pragma endregion catapult

#pragma region pto
void pto_toggle(bool toggle) {
  // Toggle PTO motors
  pto_6_motor_enabled = toggle;
  chassis.pto_toggle({PTO_intake, PTO_catapult}, toggle);

  // Actuate the piston
  PTO_piston.set_value(!toggle);
}

void pto_control() {
  // Handle PTO activation/deactivation in user control
  if (master.get_digital_new_press(selected_controls.toggle_PTO_button)) {
    pto_toggle(!pto_6_motor_enabled);
  }
}
#pragma endregion pto

#pragma region intake
void spin_intake_for(float degrees) {
  PTO_intake.move_relative(degrees, INTAKE_SPEED);
}

void set_intake_volts(int volts) {
  PTO_intake.move_voltage(volts);
}

void intake_control() {
  // Toggle the intake (inward direction)
  if (master.get_digital_new_press(selected_controls.toggle_intake_button)) {
    intake_toggle_enabled = !intake_toggle_enabled;
    outtake_toggle_enabled = false;
  }
  // Toggle the intake (outward direction)
  if (master.get_digital_new_press(selected_controls.toggle_outtake_button)) {
    outtake_toggle_enabled = !outtake_toggle_enabled;
    intake_toggle_enabled = false;
  }

  // Move the intake while toggled and 6 motor
  if (pto_6_motor_enabled) {
    if (intake_toggle_enabled) {
      set_intake_volts(-INTAKE_VOLTAGE);
    } else if (outtake_toggle_enabled) {
      set_intake_volts(INTAKE_VOLTAGE);
    }
  }

  // Hold buttons to control the intake
  if (master.get_digital(selected_controls.hold_outtake_button)) {
    set_intake_volts(INTAKE_VOLTAGE);
    pto_toggle(true);
  } else if (master.get_digital(selected_controls.hold_intake_button)) {
    set_intake_volts(-INTAKE_VOLTAGE);
    pto_toggle(true);
  } else if (pto_6_motor_enabled) {
    set_intake_volts(0);
  }
}
#pragma endregion intake

#pragma region wings
void wing_toggle(bool toggle) {
  wing_piston_right.set_value(toggle);
  wing_piston_left.set_value(toggle);
  wings_enabled = toggle;
}

void wing_control() {
  // Handle enabling/disabling the wings in user control
  if (master.get_digital_new_press(selected_controls.toggle_wings_button))
    wing_toggle(!wings_enabled);
}
#pragma endregion wings

#pragma region endgame
// how is endgame gonna work im so lost
#pragma endregion endgame