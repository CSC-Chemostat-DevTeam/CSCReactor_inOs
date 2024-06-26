// ----------------------------------------------------------------------------
// SUBSYSTEM API

void _heater_subsystem_setup() {

    // INIT GLOBAL (DEFAULTS)
    heater_include_flag = HEATER_INCLUDE_FLAG_DFLT_VAL;
    heater_target_temp = HEATER_TARGET_TEMP_DFLT_VAL;
    heater_action_period = HEATER_ACTION_PERIOD_DFLT_VAL;
    heater_pulse_duration = HEATER_PULSE_DURATION_DFLT_VAL;
    heater_dry_run_flag = HEATER_DRY_RUN_FLAG_DFLT_VAL;

    // INIT INTERNALS
    _T_sensor.begin();
    _heater_timer.set_period(heater_action_period);
    delay(3);

    // PINS
    // HEATER
    pinMode(HEATER_PIN, OUTPUT);
}

void _heater_subsystem_action() {
    
    // ENABLE
    if (!heater_include_flag) { return; }
    if (!_heater_enable_flag) { return; }

    // ACTION
    _heater_timer.set_period(heater_action_period);
    if (_heater_timer.notyet()) { return; }

    // MEASURE
    _heater_measure_temp();

    // ACTIVATE
    if (_heater_temp_val < heater_target_temp) { 
        if (heater_dry_run_flag) {
		    delay(heater_pulse_duration);
        } else {
            _heater_high(); 
		    delay(heater_pulse_duration);
            _heater_low(); 
        }
    }
}

// ----------------------------------------------------------------------------
// HEATER API

void _heater_enable() {
    _heater_enable_flag = true;
}

void _heater_disable() {
    _heater_enable_flag = false;
}

void _heater_high() {
    digitalWrite(HEATER_PIN, HIGH);
}

void _heater_low() {
    digitalWrite(HEATER_PIN, LOW);
}

// ----------------------------------------------------------------------------
// T SENSOR API
void _heater_measure_temp() {
    _T_sensor.requestTemperatures();
    delay(3);
    _heater_temp_val = _T_sensor.getTempCByIndex(0);
}

