void setup() {
    _io_subsystem_setup();
    _loop_control_setup();
    _heater_subsystem_setup();
    _do_subsystem_setup();
    _pump_subsystem_setup();
    _stirrel_subsystem_setup();
}

void loop() {
    _loop_action();
}