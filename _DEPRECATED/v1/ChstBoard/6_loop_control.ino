void _loop_control_setup() {

    // Setup globals
    loop_enable_flag = true;
}

void _loop_action() {

    // READ INPUT
    _io_read_action();

    // LOOP GLOBALS
    _loop_init_time = millis();
    _loop_counter++;

    // MAIN ACTIONS
    if (loop_enable_flag) { 
        _do_subsystem_action();
        _heater_subsystem_action();
        _pump_subsystem_action();
        _stirrel_subsystem_action();
    }

    // PRINT
    _io_print_action();

}