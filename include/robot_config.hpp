#pragma once

#include "main.h"

// Define the chassis
// Left motors, Right motors, IMU, Wheel Diameter, RPM, Gear ratio
Drive chassis({15, -8, -13, 14}, {-18, 17, 20, -19}, 16, 4.125, 600, 0.6);

// Define Motors
pros::Motor& PTO_intake = chassis.left_motors[3];
pros::Motor& PTO_slapper = chassis.right_motors[3];

// Define Pneumatics
pros::ADIDigitalOut wing_piston('A');
pros::ADIDigitalOut PTO_piston('B');
pros::ADIDigitalOut hang_piston('C');

// Define Sensors
pros::Optical slapper_optic_sensor(5);
pros::Rotation slapper_rotation_sensor(12);