#pragma once

#include "EZ-Template/drive/drive.hpp"

extern Drive chassis;
extern pros::Motor& PTO_slapper;

void test_auton();

void bowl_auton();
void four_ball();
void five_ball();

void skills();

void default_constants();
void exit_condition_defaults();