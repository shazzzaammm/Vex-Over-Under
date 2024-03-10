#pragma once

#include "EZ-Template/drive/drive.hpp"

extern Drive chassis;
extern pros::Motor& PTO_slapper;

void test_auton();

void bowl_auton();

void closer_awp();
void close_awp();

void five_ball_elim();
void five_ball_qual();

void skills();
void skills_macro();

void default_constants();
void exit_condition_defaults();