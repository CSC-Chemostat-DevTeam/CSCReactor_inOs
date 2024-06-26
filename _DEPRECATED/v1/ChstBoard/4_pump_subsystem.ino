// ----------------------------------------------------------------------------
// SUBSYSTEM API

void _pump_subsystem_setup() {

    // INIT GLOBAL (DEFAULTS)
    pump_include_flag = PUMP_INCLUDE_FLAG_DFLT_VAL;
    pump_dilution_rate = PUMP_DILUTION_RATE_DFLT_VAL; // the control parameter (1/h)
    pump_working_volume = PUMP_WORKING_VOLUME_DFLT_VAL; // (ml)
    pump_vol_per_pulse = PUMP_VOL_PER_PULSE_DFLT_VAL; // a calibration parameter (ml/pulse)
    pump_pulse_duration = PUMP_PULSE_DURATION_DFLT_VAL; // the length of a pump pulse (ms)
    pump_buffer_time = PUMP_BUFFER_TIME_DFLT_VAL; // idle time before pumping for stabilization (ms)
    pump_tot_pulses = PUMP_TOT_PULSES_DFLT_VAL;
    pump_dry_run_flag = PUMP_DRY_RUN_FLAG_DFLT_VAL;

    // INIT INTERNALS
    _up_pump_period();

    // INIT INTERNALS
    pinMode(PUMP_PIN, OUTPUT);
    _pump_low();
}

// DEV
// $101:1%$102:0%$103:120%$104:25%$205:0.3%$105:25%$106:300%$107:5000%$108:3000% $201:1%$202:0%
// 91
// 91.2
// 91

void _pump_subsystem_action() {

    // ENABLE
    if (!pump_include_flag) { return; } 
    if (!_pump_enable_flag) { return; } 

    // ACTION
    _up_pump_period();

    // Check if somthing to do
    if (pump_dilution_rate == 0.0) { return; } 

    // prepare pump_buffer_time
    if (_pump_timer.time_to_event() <= pump_buffer_time) {
        _do_disable();
        _heater_disable();
        _stirrel_disable();
    }

    if (_pump_timer.notyet()) { return; } 
    
    //  pulse counter
    if (_pump_pulse_counter >= pump_tot_pulses) { 
        _pump_disable();
        return; 
    }
    
    // Pump!
    if (pump_dry_run_flag) { 
        delay(pump_pulse_duration);
    } else {
        _pump_pulse();
    }

    // back to normal
    _do_enable();
    _heater_enable();
    _stirrel_enable();

}

void _pump_enable() {
    _pump_enable_flag = true;
}

void _pump_disable() {
    _pump_enable_flag = false;
}

// ----------------------------------------------------------------------------
// PUMP API

void _pump_high() { digitalWrite(PUMP_PIN, HIGH); }

void _pump_low() { digitalWrite(PUMP_PIN, LOW); }

void _pump_pulse() {
    _pump_high();
    delay(pump_pulse_duration);
    _pump_low();
    _pump_pulse_counter++;
    delay(50);
}

void _up_pump_period() {
  _pump_timer.set_period(3600000 / (pump_dilution_rate * (pump_working_volume / pump_vol_per_pulse)));
}