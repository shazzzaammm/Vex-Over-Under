#pragma once

#include "main.h"

// Intake
const int INTAKE_SPEED = 127;
const int INTAKE_VOLTAGE = 12000;
bool intake_toggle_enabled = false;
bool outtake_toggle_enabled = false;

// PTO
bool pto_6_motor_enabled = false;

// Wings
bool wings_enabled = false;

// Chassis
bool chassis_is_reversed = false;

// Controls
const ControlScheme t_controls(DIGITAL_R1, DIGITAL_L1, DIGITAL_RIGHT, DIGITAL_LEFT, DIGITAL_B, DIGITAL_R2, DIGITAL_X,
                               DIGITAL_A, DIGITAL_L2, TANK);
const ControlScheme g_controls(DIGITAL_L1, DIGITAL_L2, DIGITAL_R1, DIGITAL_R2, DIGITAL_A, DIGITAL_B, DIGITAL_X,
                               DIGITAL_Y, DIGITAL_DOWN, TANK);
const ControlScheme k_controls(DIGITAL_L2, DIGITAL_L1, DIGITAL_R2, DIGITAL_R1, DIGITAL_B, DIGITAL_A, DIGITAL_Y,
                               DIGITAL_X, DIGITAL_DOWN, TANK);
ControlScheme selected_controls = g_controls;

// Util
const int MATCH_LENGTH = 105000; // = 105 seconds
int match_start_time = 0;