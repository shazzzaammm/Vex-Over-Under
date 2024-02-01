#pragma once

#include "main.h"

// Define the chassis
// Left motors, Right motors, IMU, Wheel Diameter, RPM, Gear ratio
Drive chassis({9, -10, -21, 8}, {6, -4, 3, -5}, 2, 4.125, 600, 0.6);

// Define Motors
pros::Motor& PTO_intake = chassis.left_motors[3];
pros::Motor& PTO_slapper = chassis.right_motors[3];

// Define Pneumatics
pros::ADIDigitalOut PTO_piston('B');
pros::ADIDigitalOut wing_piston('C');
