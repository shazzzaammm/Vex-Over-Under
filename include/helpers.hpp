void rumble_controller();
void controller_stats_task(void* parameter);
void print_stat_to_controller(int type);

void chassis_control();
bool isCataCharged();
bool isSlapperFull();

void set_intake_volts(int volts);
void spin_intake_for(float degrees);
void intake_control();

void pto_toggle(bool toggle);
void pto_control();

void wing_toggle(bool toggle);
void wing_control();

void catapult_control();