void rumble_controller();
void print_stats_controller();

void charge_catapult();
void shoot_catapult();
void move_catapult(int degrees);

void set_intake_volts(int volts);
void spin_intake_for(float dist);
void intake_control();

void pto_toggle(bool toggle);
void set_pto_volts(int volts);
void pto_control();

void wing_toggle(bool toggle);
void wing_control();

void toggle_endgame(bool toggle);