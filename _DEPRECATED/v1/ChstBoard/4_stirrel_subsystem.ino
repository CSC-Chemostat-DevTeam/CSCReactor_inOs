// ----------------------------------------------------------------------------
// SUBSYSTEM API

void _stirrel_subsystem_setup() {

    // INIT GLOBAL (DEFAULTS)
    stirrel_include_flag = STIRREL_INCLUDE_FLAG_DFLT_VAL;
    stirrel_dry_run_flag = STIRREL_DRY_RUN_FLAG_DFLT_VAL;
    stirrel_pulse_duration = STIRREL_PULSE_DURATION_DFLT_VAL;
    stirrel_action_period = STIRREL_ACTION_PERIOD_DFLT_VAL;

    // INIT INTERNALS
	_stirrel_timer.set_period(stirrel_action_period);

    // PINS
    pinMode(STIRREL_PIN, OUTPUT);
    _stirrel_low();
}

void _stirrel_subsystem_action() {

	// ENABLE
	if (!stirrel_include_flag) { return; }
	if (!_stirrel_enable_flag) { return; }

	// ACTION
	_stirrel_timer.set_period(stirrel_action_period);
	if (_stirrel_timer.notyet()) { return; }

	if (stirrel_dry_run_flag) {
		delay(stirrel_pulse_duration);
	} else {
		_stirrel_pulse();
	}
	

}

// ----------------------------------------------------------------------------
// STIRREL API

void _stirrel_high(){ digitalWrite(STIRREL_PIN, HIGH); }

void _stirrel_low() { digitalWrite(STIRREL_PIN, LOW); }

void _stirrel_disable() {
  	_stirrel_enable_flag = false;
}

void _stirrel_enable() {
  _stirrel_enable_flag = true;
}

void _stirrel_pulse() {
	_stirrel_high();
	delay(stirrel_pulse_duration);
	_stirrel_low();
	delay(3);
}