// Brain
void print_debug();

// Controller
void rumble_controller();
void controller_stats_task(void* parameter);
void print_stat_to_controller(int type);

// Chassis
void chassis_control();

// Intake
void set_intake_volts(int volts);
void spin_intake_for(float degrees);
void intake_control();

// Flywheel
void flywheel_control();

// Lift
void lift_control();
void lift_toggle(bool toggle);

// PTO
void pto_toggle(bool toggle);
void pto_control();

// Wings
void wing_toggle(bool toggle);
void wing_control();

// Endgame
void endgame_toggle(bool toggle);
void endgame_control();