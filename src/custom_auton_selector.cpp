#include "main.h"

void CustomAutonSelector::add_autons(std::vector<Auton> autons) {
  auton_count += autons.size();
  current_auton_page = 0;
  Autons.assign(autons.begin(), autons.end());
}

void CustomAutonSelector::call_selected_auton() {
  if (auton_count == 0) return;
  Autons[current_auton_page].auton_call();
}

void CustomAutonSelector::print_selected_auton() {
  if (auton_count == 0) return;
  for (int i = 0; i < 8; i++)
    pros::lcd::clear_line(i);
  ez::print_to_screen("Page " + std::to_string(current_auton_page + 1) + "\n" + Autons[current_auton_page].Name, 6);
}

CustomAutonSelector::CustomAutonSelector(std::vector<Auton> autons) {
  auton_count = autons.size();
  current_auton_page = 0;
  Autons = {};
  Autons.assign(autons.begin(), autons.end());
}

CustomAutonSelector::CustomAutonSelector() {
  auton_count = 0;
  current_auton_page = 0;
  Autons = {};
}