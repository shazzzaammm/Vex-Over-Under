#pragma once

#include "main.h"

// Intake
const int INTAKE_SPEED = 127;
const int INTAKE_VOLTAGE = 12000;
bool intake_toggle_enabled = false;
bool outtake_toggle_enabled = false;

// Catapult
const int CATAPULT_CHARGING_VOLTAGE = 12000;
const int CATAPULT_SHOOTING_VOLTAGE = 12000;
const float TRIBALL_LOADED_BRIGHTNESS = .00005;
const int CATAPULT_CHARGED_DEGREES = 3000;
bool catapult_auto_shoot_enabled = false;

// PTO
bool pto_6_motor_enabled = false;

// Wings
bool wings_enabled = false;

// Chassis
bool chassisIsReversed = false;

const ControlScheme t_controls(
  DIGITAL_R2,
  DIGITAL_L2,
  DIGITAL_R1,
  DIGITAL_L1,
  DIGITAL_B,
  DIGITAL_A,
  DIGITAL_Y,
  DIGITAL_X,
  DIGITAL_DOWN
);
const ControlScheme g_controls(
  DIGITAL_L1,
  DIGITAL_L2,
  DIGITAL_R1,
  DIGITAL_R2,
  DIGITAL_A,
  DIGITAL_B,
  DIGITAL_X,
  DIGITAL_Y,
  DIGITAL_DOWN
);

const ControlScheme k_controls(
  DIGITAL_L2,
  DIGITAL_L1,
  DIGITAL_R2,
  DIGITAL_R1,
  DIGITAL_B,
  DIGITAL_A,
  DIGITAL_Y,
  DIGITAL_X,
  DIGITAL_DOWN
);

ControlScheme selected_controls = k_controls;