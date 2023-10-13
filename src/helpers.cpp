#include "main.h"
#include "okapi/api.hpp"

// extern pros::ADIDigitalOut indexer;

// void toggle_indexer() {
//   indexer.set_value(1);
//   pros::delay(250);
//   indexer.set_value(0);
// }

void rumble_controller() {
  master.rumble("...."); //⁡⁢⁣⁢THIS USES MORSE CODE!!!!⁡
}

void move_claw(float dist){
  pros::delay(750); // ⁡⁢⁣⁢REMOVE THIS ONCE THINGS ARE EPIC⁡
  //set velocity
  //move dist 
}