#include "main.h"
#include "robot_config.hpp"
#include "variables.hpp"

#pragma region brain
void check_motors_and_get_temp() {
  std::vector<pros::Motor> motors = {
      chassis.left_motors[0],  chassis.left_motors[1],  chassis.left_motors[2],  chassis.left_motors[3],
      chassis.right_motors[0], chassis.right_motors[1], chassis.right_motors[2], chassis.right_motors[3],
  };

  double totalTemp = 0.0;
  int count = 0;

  for (auto& motor : motors) {
    double temp = motor.get_temperature();
    if (temp == PROS_ERR_F) {  // PROS_ERR_F is returned when the motor is unplugged
      print_to_screen("Motor " + std::to_string(motor.get_port()) + " unplugged.", 4);
      pros::delay(250);
      rumble_controller();
    }

    if (count < 6) {
      totalTemp += temp;
    }
    ++count;
  }

  if (count == 0)
    print_to_screen("No motors found", 4);

  double averageTempCelsius = totalTemp / count;
  double averageTempFahrenheit = averageTempCelsius * 9.0 / 5.0 + 32.0;
  print_to_screen("Avgerage Temp: " + std::to_string(averageTempFahrenheit), 4);
}

void print_debug() {
  // Prints a lot of debug information (this is so i dont go fully insane)
  std::string drive_mode = pto_6_motor_enabled ? "6 motor" : "8 motor";
  std::string endgame_state = to_string(endgame_enabled);
  std::string slapper_state = to_string(is_slapper_charged());
  std::string optic_state = to_string(is_slapper_full());
  std::string optic_brightness = to_string(slapper_optic_sensor.get_brightness());
  std::string slapper_rotation = to_string(slapper_rotation_sensor.get_angle());

  std::string right_stick = std::to_string(master.get_analog(ANALOG_RIGHT_Y));

  print_to_screen("drive mode: " + drive_mode, 0);
  print_to_screen("charged: " + slapper_state, 1);
  print_to_screen("full: " + optic_state, 2);
  print_to_screen("rot: " + slapper_rotation, 3);
  check_motors_and_get_temp();
  print_to_screen("endgame enabled: " + endgame_state, 5);
  print_to_screen("battery level: " + to_string(pros::battery::get_capacity()) + "%", 6);
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
  int left = master.get_analog(ANALOG_LEFT_Y);
  int right = master.get_analog(ANALOG_RIGHT_Y);

  if (left == 0 && right == 0) {
    chassis.tank();
  }

  if (!chassis_is_reversed) {
    chassis.set_tank(left, right);
  } else {
    chassis.set_tank(-right, -left);
  }
}

void drive_control() {
  // Use the drive mode the user wants
  switch (selected_controls.drive_mode) {
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
  // Drive using the user's prefered method
  drive_control();
  // Reverse chassis when requested
  if (master.get_digital_new_press(selected_controls.reverse_chassis_button)) {
    reverse_chassis();
  }
}
#pragma endregion chassis

#pragma region controller
bool multi_pressing(std::vector<pros::controller_digital_e_t> buttons) {
  for (auto button = buttons.begin(); button != buttons.end(); ++button) {
    if (*button == *buttons.end() && !master.get_digital_new_press(*button)) {
      return false;
    } else if (!master.get_digital(*button)) {
      return false;
    }
  }
  return true;
}

bool any_button_down(std::vector<pros::controller_digital_e_t> buttons) {
  for (auto button = buttons.begin(); button != buttons.end(); ++button) {
    if (master.get_digital_new_press(*button)) {
      return true;
    }
  }
  return false;
}

void rumble_controller() {
  master.rumble(".");
}

std::string get_button_down() {
  // Used for debugging
  if (master.get_digital(selected_controls.hold_intake_button)) {
    return "Intake Hold    ";
  }
  if (master.get_digital(selected_controls.hold_outtake_button)) {
    return "Outtake Hold   ";
  }
  if (master.get_digital(selected_controls.hold_slapper_button)) {
    return "Slapper Hold   ";
  }
  if (master.get_digital(selected_controls.toggle_slapper_button)) {
    return "Slapper Toggle ";
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
  if (any_button_down(selected_controls.toggle_wings_buttons)) {
    return "Wings Toggle   ";
  }
  if (master.get_digital(selected_controls.endgame_button)) {
    return "End Game       ";
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
  // Behave differently if disabled
  if (pros::competition::is_disabled()) {
    if (type == 0) {
      // :D
      master.set_text(0, 0, "Good Luck!!!!");
    } else if (type == 1) {
      // Clear line to update more consistently
      master.clear_line(1);
    } else if (type == 2) {
      // Print the auton name to the controller
      std::string auton_name = ez::as::auton_selector.Autons[ez::as::auton_selector.current_auton_page].Name;
      std::string auton_display_name = auton_name.substr(0, auton_name.find("\n", 0));
      master.set_text(1, 0, auton_display_name);
    }
    return;
  } else {
    if (type == 0) {
      // Prints the current drive mode
      master.set_text(0, 0, (pto_6_motor_enabled ? "Mode: 6 motor!!!!" : "Mode: 8 motor!!!!"));
    } else if (type == 1) {
      // Prints the button being pressed (so we dont use the wrong controls)
      master.set_text(1, 0, get_button_down());
    } else if (type == 2) {
      // Prints remaining time in the match
      double time_remaining = (MATCH_LENGTH + match_start_time - pros::millis()) / 1000;
      master.set_text(2, 0, "Time Remaining: " + std::to_string(time_remaining) + "  ");
    }
  }
}
#pragma endregion controller

#pragma region pto
void pto_toggle(bool toggle) {
  // Toggle PTO motors
  pto_6_motor_enabled = toggle;
  chassis.pto_toggle({PTO_intake, PTO_slapper}, toggle);

  // Actuate the piston
  PTO_piston.set_value(toggle);
}

void pto_control() {
  // Handle PTO activation/deactivation in user control
  if (master.get_digital_new_press(selected_controls.toggle_PTO_button)) {
    pto_toggle(!pto_6_motor_enabled);
  }
}
#pragma endregion pto

#pragma region slapper
void slapper_auto_shoot_toggle() {
  slapper_auto_shoot_enabled = !slapper_auto_shoot_enabled;
}

bool is_slapper_full() {
  return slapper_optic_sensor.get_brightness() <= TRIBALL_BRIGHTNESS;
}

bool is_slapper_charged() {
  return (slapper_rotation_sensor.get_angle() >= SLAPPER_CHARGED_ROTATION - SLAPPER_CHARGED_LEEWAY &&
          slapper_rotation_sensor.get_angle() <= SLAPPER_CHARGED_ROTATION + SLAPPER_CHARGED_LEEWAY);
}

void slapper_auton_task(void* parameter) {
  int total_shot = 0;
  while (true) {
    if (!is_slapper_charged()) {
      PTO_slapper.move_voltage(SLAPPER_VOLTAGE);
    } else if (is_slapper_full()) {
      PTO_slapper.move_voltage(SLAPPER_VOLTAGE);
      total_shot++;
      pros::delay(3 * ez::util::DELAY_TIME);
    }
    pros::delay(ez::util::DELAY_TIME);
    if (total_shot > 45) {
      break;
    }
  }
}

void slapper_control() {
  // Only move slapper if we are in 6 motor
  if (!pto_6_motor_enabled) {
    return;
  }

  // Toggle automatic shooting (for match loading)
  if (master.get_digital_new_press(selected_controls.toggle_slapper_button)) {
    slapper_auto_shoot_toggle();
  }

  // Shoot the slapper automatically, shoot the slapper manually, or charge the slapper automatically
  if (master.get_digital(selected_controls.hold_slapper_button) || (is_slapper_full() && slapper_auto_shoot_enabled) ||
      (!is_slapper_charged())) {
    PTO_slapper.move_voltage(SLAPPER_VOLTAGE);
  }

  // Stop the slapper
  else {
    PTO_slapper.brake();
  }
}
#pragma endregion slapper

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

  // Move the intake if toggled or holding the buttons
  if (master.get_digital(selected_controls.hold_outtake_button) || outtake_toggle_enabled) {
    set_intake_volts(INTAKE_VOLTAGE);
    pto_toggle(true);
  } else if (master.get_digital(selected_controls.hold_intake_button) || intake_toggle_enabled) {
    set_intake_volts(-INTAKE_VOLTAGE);
    pto_toggle(true);
  } else if (pto_6_motor_enabled) {
    set_intake_volts(0);
  }
}
#pragma endregion intake

#pragma region wings
void wing_toggle(bool toggle) {
  wing_piston.set_value(toggle);
  wings_enabled = toggle;
}

void wing_control() {
  // Handle enabling/disabling the wings in user control
  if (any_button_down(selected_controls.toggle_wings_buttons))
    wing_toggle(!wings_enabled);
}
#pragma endregion wings

#pragma region endgame
void endgame_toggle(bool enable) {
  // Toggle variable
  endgame_enabled = enable;

  // Toggle endgame
  hang_piston.set_value(endgame_enabled);
}

void endgame_control() {
  // Handle toggling the endgame in user control
  if (master.get_digital_new_press(selected_controls.endgame_button)) {
    endgame_toggle(!endgame_enabled);
  }
}
#pragma endregion endgame