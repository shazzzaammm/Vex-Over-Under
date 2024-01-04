#pragma once

#include "main.h"

// Define the chassis (PTO motors are last in the curly braces)
Drive chassis({9, -10, 12, -11}, {5, -4, 3, -2}, 20, 4.125, 600, 0.5);

// Define Motors
pros::Motor& PTO_intake = chassis.left_motors[3];
pros::Motor& PTO_flywheel = chassis.right_motors[3];

// Define Pneumatics
pros::ADIDigitalOut PTO_piston('H');
pros::ADIDigitalOut wing_piston_left('A');
pros::ADIDigitalOut wing_piston_right('B');
pros::ADIDigitalOut lift_piston('Z');
