#pragma once

#include "EZ-Template/drive/drive.hpp"

extern Drive chassis;
extern pros::Motor& PTO_slapper;

void test_auton();

void four_ball();
void five_ball();

void skills();

void same_zone_awp();
void same_zone_elim();

void opposite_zone_awp();
void opposite_zone_elim();

void default_constants();
void exit_condition_defaults();