#pragma once

#include "main.h"

const int INTAKE_SPEED = 127;
const int INTAKE_VOLTAGE = 12000;

const int CATAPULT_CHARGING_VOLTAGE = 12000;
const int CATAPULT_SHOOTING_VOLTAGE = 12000;

const int TRIBALL_SHOOT_DISTANCE = 400;

int pto_cooldown = 0;
bool pto_6_motor_enabled = false;

bool intake_toggle_enabled = false;
bool outtake_toggle_enabled = false;

bool wing_toggle_enabled = false;

bool catapult_auto_shoot_enabled = false;

const ControlScheme a_controls(
  DIGITAL_R2,
  DIGITAL_L2,
  DIGITAL_R1,
  DIGITAL_L1,
  DIGITAL_B,
  DIGITAL_A,
  DIGITAL_Y,
  DIGITAL_X
);
const ControlScheme g_controls(
  DIGITAL_L1,
  DIGITAL_L2,
  DIGITAL_R1,
  DIGITAL_R2,
  DIGITAL_A,
  DIGITAL_B,
  DIGITAL_X,
  DIGITAL_Y
);

const ControlScheme k_controls(
  DIGITAL_L2,
  DIGITAL_L1,
  DIGITAL_R2,
  DIGITAL_R1,
  DIGITAL_B,
  DIGITAL_A,
  DIGITAL_Y,
  DIGITAL_X
);

ControlScheme selected_controls = k_controls;