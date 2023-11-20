#pragma once
#include <tuple>

#include "EZ-Template/auton.hpp"
#include "vector"
class CustomAutonSelector {
 public:
  std::vector<Auton> Autons;
  int current_auton_page;
  int auton_count;
  CustomAutonSelector();
  CustomAutonSelector(std::vector<Auton> autons);
  void call_selected_auton();
  void print_selected_auton();
  void add_autons(std::vector<Auton> autons);
};