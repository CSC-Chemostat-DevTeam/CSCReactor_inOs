// ---------------------------------------------------------
// API
void _io_subsystem_setup() {

    // INIT GLOBAL (DEFAULTS)
    io_print_include_flag = IO_PRINT_INCLUDE_FLAG_DFLT_VAL;
    io_print_action_period = IO_PRINT_ACTION_PERIOD_DFLT_VAL; // (ms)
    io_print_dry_run_flag = IO_PRINT_DRY_RUN_FLAG_DFLT_VAL;
    
    // INIT INTERNALS
    _io_print_timer.set_period(io_print_action_period);

    // INIT SERIAL
    Serial.begin(IO_BAUDRATE);
    delay(3);

}

void _io_read_action() {

    do {

        _io_read_input_keypair();
        _io_up_global();

    } while (_io_input_isvalid);

}

void _io_print_action() {

    // ENABLE
    if (!io_print_include_flag) { return; }

    // ACTION
    _io_print_timer.set_period(io_print_action_period);
    if (_io_print_timer.istime() || _io_print_force_flag || _io_ctask.is_running()) {
        // PRINT
        if (io_print_dry_run_flag) { 
            delay(100);
        } else {
            _io_print_bash();
        }
        _io_print_free();
    }
}

// ---------------------------------------------------------
// READ

void _io_read_input_keypair() {
  
    _io_input_isvalid = false;

    byte key_ndx = 0;
    byte val_ndx = 0;
    char curr_char;
    bool init_found = false;
    bool sep_found = false;
    long t0 = millis();

    while (Serial.available() > 0) {

        delay(3); // Stability
        curr_char = Serial.read();

        // TIME OUT
        if (millis() - t0 > IO_INPUT_TIMEOUT) { return; }

        // INIT CHAR
        if (curr_char == IO_INPUT_INIT_CHAR) { 
            if (init_found) { return; } // invalid
            init_found = true; 
            continue; 
        }
        if (!init_found) { continue; }

        // SEP CHAR
        if (curr_char == IO_INPUT_SEP_CHAR) { 
            if (sep_found) { return; } // invalid
            sep_found = true; 
            continue; 
        }

        // END CHAR
        if (curr_char == IO_INPUT_END_CHAR) { 
            _io_input_key_buff[key_ndx] = '\0'; // end of string
            _io_input_val_buff[val_ndx] = '\0'; // end of string
            _io_input_isvalid = true; // validate input
            return;
        }

        if (sep_found) {
            // VAL CHAR
            _io_input_val_buff[val_ndx] = curr_char;
            val_ndx++;
        } else {
            // KEY CHAR
            _io_input_key_buff[key_ndx] = curr_char;
            key_ndx++;
        }

        // FULL BUFFER
        if (key_ndx >= _IO_INPUT_KEY_BUFF_LENGTH || val_ndx >= _IO_INPUT_VALUE_BUFF_LENGTH) { 
            return; 
        }

    } // while
  
}

void _io_up_global() {
    if (!_io_input_isvalid) { return; };

    int key = atoi(_io_input_key_buff);

    if (key == DO_INCLUDE_FLAG_INPUT_KEY) { // DO SUBSYSTEM
        do_include_flag = atoi(_io_input_val_buff);
    } else if (key == DO_LASER_PWD_VAL_INPUT_KEY) {
        do_laser_pwd_val = atol(_io_input_val_buff);
    } else if (key == DO_ACTION_PERIOD_INPUT_KEY) {
        do_action_period = atol(_io_input_val_buff);
    } else if (key == DO_LEDS_SAMPLING_TIME_INPUT_KEY) {
        do_leds_sampling_time = atol(_io_input_val_buff);
    } else if (key == LEDS_MAX_PER_PULSE_TIMEOUT_INPUT_KEY) {
        do_leds_per_pulse_timeout = atol(_io_input_val_buff);
    } else if (key == LEDS_BUFFER_TIME_INPUT_KEY) {
        do_buffer_time = atol(_io_input_val_buff);
    } else if (key == DO_DRY_RUN_FLAG_INPUT_KEY) {
        do_dry_run_flag = atol(_io_input_val_buff);
    } else if (key == PUMP_INCLUDE_FLAG_INPUT_KEY) { // PUMP SUBSYSTEM
        pump_include_flag = atoi(_io_input_val_buff);
    } else if (key == PUMP_DILUTION_RATE_INPUT_KEY) {
        pump_dilution_rate = atof(_io_input_val_buff);
    } else if (key == PUMP_WORKING_VOLUME_INPUT_KEY) {
        pump_working_volume = atof(_io_input_val_buff);
    } else if (key == PUMP_VOL_PER_PULSE_INPUT_KEY) {
        pump_vol_per_pulse = atof(_io_input_val_buff);
    } else if (key == PUMP_PULSE_DURATION_INPUT_KEY) {
        pump_pulse_duration = atol(_io_input_val_buff);
    } else if (key == PUMP_BUFFER_TIME_INPUT_KEY) {
        pump_buffer_time = atol(_io_input_val_buff);
    } else if (key == PUMP_TOT_PULSES_INPUT_KEY) {
        pump_tot_pulses = atol(_io_input_val_buff);
    } else if (key == PUMP_DRY_RUN_FLAG_INPUT_KEY) {
        pump_dry_run_flag = atoi(_io_input_val_buff);
    } else if (key == STIRREL_INCLUDE_FLAG_INPUT_KEY) { // STIRREL SUBSYSTEM
        stirrel_include_flag = atoi(_io_input_val_buff);
    } else if (key == STIRREL_DRY_RUN_FLAG_INPUT_KEY) {
        stirrel_dry_run_flag = atoi(_io_input_val_buff);
    } else if (key == STIRREL_PULSE_DURATION_INPUT_KEY) {
        stirrel_pulse_duration = atol(_io_input_val_buff);
    } else if (key == STIRREL_ACTION_PERIOD_INPUT_KEY) {
        stirrel_action_period = atol(_io_input_val_buff);
    } else if (key == HEATER_INCLUDE_FLAG_INPUT_KEY) { // HEATER SUBSYSTEM
        heater_include_flag = atoi(_io_input_val_buff);
    } else if (key == HEATER_TARGET_TEMP_INPUT_KEY) {
        heater_target_temp = atof(_io_input_val_buff);
    } else if (key == HEATER_ACTION_PERIOD_INPUT_KEY) {
        heater_action_period = atol(_io_input_val_buff);
    } else if (key == HEATER_PULSE_DURATION_INPUT_KEY) {
        heater_pulse_duration = atol(_io_input_val_buff);
    } else if (key == HEATER_DRY_RUN_FLAG_INPUT_KEY) {
        heater_dry_run_flag = atoi(_io_input_val_buff);
    } else if (key == IO_PRINT_INCLUDE_FLAG_INPUT_KEY) { // IO SUBSYSTEM
        io_print_include_flag = atoi(_io_input_val_buff);
    } else if (key == IO_PRINT_ACTION_PERIOD_INPUT_KEY) { 
        io_print_action_period = atol(_io_input_val_buff);
    } else if (key == IO_PRINT_DRY_RUN_FLAG_INPUT_KEY) {
        io_print_dry_run_flag = atoi(_io_input_val_buff);
    } else if (key == LOOP_ENABLE_FLAG_INPUT_KEY) { // LOOP
        loop_enable_flag = atoi(_io_input_val_buff);
    }
}

// ---------------------------------------------------------
// PRINT

// Concurrent
void _io_print_bash() {

    // update
    _io_ctask.at_init();
    
    // ---------------------------------------------------------
    // START SIGNAL
    if (_io_ctask.is_todo()) { Serial.println(); return; }
    if (_io_ctask.is_todo()) { Serial.println(IO_PRINT_START_MARKER); return; }

    // ---------------------------------------------------------
    if (_io_ctask.is_todo()) { Serial.println("[LOOP]"); return; }

    // CONTROLS
    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(LOOP_ENABLE_FLAG_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") loop_enable_flag = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(loop_enable_flag); return; }
        
    // INTERNALS
    if (_io_ctask.is_todo()) { Serial.print("loop_init_time = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(_loop_init_time); return; }

    if (_io_ctask.is_todo()) { Serial.print("loop_counter = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(_loop_counter); return; }

    // ---------------------------------------------------------
    if (_io_ctask.is_todo()) { Serial.println("[PUMP]"); return; }

    // CONTROLS
    if (_io_ctask.is_todo()) {  Serial.print("("); return; }
    if (_io_ctask.is_todo()) {  Serial.print(PUMP_INCLUDE_FLAG_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) {  Serial.print(") pump_include_flag = "); return; }
    if (_io_ctask.is_todo()) {  Serial.println(pump_include_flag); return; }

    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(PUMP_DRY_RUN_FLAG_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") pump_dry_run_flag = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(pump_dry_run_flag); return; }

    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(PUMP_DILUTION_RATE_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") pump_dilution_rate = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(pump_dilution_rate); return; }

    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(PUMP_WORKING_VOLUME_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") pump_working_volume = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(pump_working_volume); return; }

    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(PUMP_VOL_PER_PULSE_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") pump_vol_per_pulse = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(pump_vol_per_pulse); return; }

    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(PUMP_PULSE_DURATION_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") pump_pulse_duration = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(pump_pulse_duration); return; }

    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(PUMP_BUFFER_TIME_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") pump_buffer_time = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(pump_buffer_time); return; }
        
    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(PUMP_TOT_PULSES_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") pump_tot_pulses = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(pump_tot_pulses); return; }

        // INTERNALS
    if (_io_ctask.is_todo()) { Serial.print("period = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(_pump_timer.get_period()); return; }
        
    if (_io_ctask.is_todo()) { Serial.print("time_till_next = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(_pump_timer.time_to_event()); return; }

    if (_io_ctask.is_todo()) { Serial.print("pulse_counter = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(_pump_pulse_counter); return; }

    // ---------------------------------------------------------
    // STIRREL
    if (_io_ctask.is_todo()) { Serial.println("[STIRREL]"); return; }

    // CONTROL
    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(STIRREL_INCLUDE_FLAG_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") stirrel_include_flag = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(stirrel_include_flag); return; }

    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(STIRREL_DRY_RUN_FLAG_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") stirrel_dry_run_flag = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(stirrel_dry_run_flag); return; }

    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(STIRREL_PULSE_DURATION_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") stirrel_pulse_duration = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(stirrel_pulse_duration); return; }

    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(STIRREL_ACTION_PERIOD_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") stirrel_action_period = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(stirrel_action_period); return; }

    // INTERNALS
    if (_io_ctask.is_todo()) { Serial.print("stirrel_period = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(_stirrel_timer.get_period()); return; }

    if (_io_ctask.is_todo()) { Serial.print("time_till_next = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(_stirrel_timer.time_to_event()); return; }

    if (_io_ctask.is_todo()) { Serial.print("pulse_counter = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(_stirrel_timer.get_event_count()); return; }
        
    // ---------------------------------------------------------
    // HEATER
    if (_io_ctask.is_todo()) { Serial.println("[HEATER]"); return; }
    
    // CONTROL
    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(HEATER_INCLUDE_FLAG_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") heater_include_flag = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(heater_include_flag); return; }

    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(HEATER_DRY_RUN_FLAG_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") heater_dry_run_flag = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(heater_dry_run_flag); return; }

    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(HEATER_TARGET_TEMP_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") heater_target_temp = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(heater_target_temp); return; }

    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(HEATER_ACTION_PERIOD_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") heater_action_period = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(heater_action_period); return; }

    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(HEATER_PULSE_DURATION_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") heater_pulse_duration = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(heater_pulse_duration); return; }

    // INTERNALS
    if (_io_ctask.is_todo()) { Serial.print("temp = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(_heater_temp_val); return; }

    if (_io_ctask.is_todo()) { Serial.print("till_target = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(heater_target_temp - _heater_temp_val); return; }

    // ---------------------------------------------------------
    if (_io_ctask.is_todo()) { Serial.println("[DO]"); return; }

    // CONTROL
    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(DO_INCLUDE_FLAG_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") do_include_flag = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(do_include_flag); return; }

    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(DO_DRY_RUN_FLAG_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") do_dry_run_flag = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(do_dry_run_flag); return; }

    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(DO_LASER_PWD_VAL_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") do_laser_pwd_val = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(do_laser_pwd_val); return; }

    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(DO_ACTION_PERIOD_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") do_action_period = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(do_action_period); return; }
    
    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(DO_LEDS_SAMPLING_TIME_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") do_leds_sampling_time = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(do_leds_sampling_time); return; }
    
    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(LEDS_MAX_PER_PULSE_TIMEOUT_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") do_leds_per_pulse_timeout = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(do_leds_per_pulse_timeout); return; }
    
    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(LEDS_BUFFER_TIME_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") do_buffer_time = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(do_buffer_time); return; }

    // INTERNALS
    if (_io_ctask.is_todo()) { Serial.print("led1_acc = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(_led1_acc); return; }

    if (_io_ctask.is_todo()) { Serial.print("led2_acc = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(_led2_acc); return; }

    if (_io_ctask.is_todo()) { Serial.print("relative = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(float(_led1_acc) / _led2_acc); return; }

    // ---------------------------------------------------------
    //  IO
    if (_io_ctask.is_todo()) { Serial.println("[IO]"); return; }
    
    // CONTROL
    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(IO_PRINT_INCLUDE_FLAG_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") io_print_include_flag = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(io_print_include_flag); return; }
    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(IO_PRINT_DRY_RUN_FLAG_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") io_print_dry_run_flag = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(io_print_dry_run_flag); return; }
    if (_io_ctask.is_todo()) { Serial.print("("); return; }
    if (_io_ctask.is_todo()) { Serial.print(IO_PRINT_ACTION_PERIOD_INPUT_KEY); return; }
    if (_io_ctask.is_todo()) { Serial.print(") io_print_action_period = "); return; }
    if (_io_ctask.is_todo()) { Serial.println(io_print_action_period); return; }
        
    // ---------------------------------------------------------
    // END SIGNAL
    if (_io_ctask.is_todo()) { Serial.println(IO_PRINT_END_MARKER); return; }
    if (_io_ctask.is_todo()) { Serial.println(); return; }
        
     
    // ---------------------------------------------------------
    _io_ctask.at_exit();
}

void _io_print_force() {
    _io_print_force_flag = true;
}

void _io_print_free() {
    _io_print_force_flag = false;
}



