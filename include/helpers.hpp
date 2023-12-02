void rumble_controller();
void print_stats_controller();
std::string getButtonDown();
void set_intake_volts(int volts);
void spin_intake_for(float degrees);
void intake_control();

void pto_toggle(bool toggle);
void pto_control();
void pto_timer();

void wing_toggle(bool toggle);
void wing_control();

void toggle_endgame(bool toggle);

void catapult_control();
void catapult_auton_task(void* parameter);
bool is_catapult_charging();