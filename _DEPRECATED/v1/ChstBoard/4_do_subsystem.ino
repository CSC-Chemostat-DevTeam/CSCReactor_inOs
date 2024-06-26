// ----------------------------------------------------------------------------
// SUBSYSTEM API

void _do_subsystem_setup() {

    // INIT GLOBAL (DEFAULTS)
    do_include_flag = DO_INCLUDE_FLAG_DFLT_VAL;
    do_laser_pwd_val = DO_LASER_PWD_VAL_DFLT_VAL;
    do_action_period = DO_ACTION_PERIOD_DFLT_VAL;
    do_leds_sampling_time = DO_LEDS_SAMPLING_TIME_DFLT_VAL;
    do_leds_per_pulse_timeout = LEDS_MAX_PER_PULSE_TIMEOUT_DFLT_VAL;
    do_buffer_time = LEDS_BUFFER_TIME_DFLT_VAL;
    do_dry_run_flag = DO_DRY_RUN_FLAG_DFLT_VAL;

    // INIT INTERNALS
    _do_timer.set_period(do_action_period);

    // PINS
    // LASER
    pinMode(DO_LASER_PWD_PIN, OUTPUT);
    _do_laser_low();

    // LEDS
    pinMode(DO_LED1_PIN, INPUT_PULLUP);
    pinMode(DO_LED2_PIN, INPUT_PULLUP);

}

// ----------------------------------------------------------------------------
void _do_subsystem_action() {

	// ENABLE
	if (!do_include_flag) { return; }
	if (!_do_enable_flag) { return; }

	// ACTION
    _do_timer.set_period(do_action_period);
	if (_do_timer.notyet()) { return; }

	// PREPARE
	// turn off the stirrel
	if (!do_dry_run_flag) {
		_pump_disable();
		_stirrel_disable();
		_stirrel_low();
		_do_laser_high();
	}
	delay(do_buffer_time);

	// MEASURE
	_measure_led_sensor_1();
	_measure_led_sensor_2();

	// RESTORE
	if (!do_dry_run_flag) {
		_do_laser_low();
		_stirrel_enable();
		_pump_enable();
	}

}

void _do_enable() {
    _do_enable_flag = true;
}

void _do_disable() {
    _do_enable_flag = false;
}

// ----------------------------------------------------------------------------
// LASER API

void _do_laser_high(int pwd){
	do_laser_pwd_val = pwd;
	analogWrite(DO_LASER_PWD_PIN, do_laser_pwd_val);
	delay(100); // Safety time
}

void _do_laser_high(){
	_do_laser_high(do_laser_pwd_val);
}

void _do_laser_low() {
	digitalWrite(DO_LASER_PWD_PIN, LOW);
}

// ----------------------------------------------------------------------------
// LED SENSOR API

// ----------------------------------------------------------------------------
void _wait_pulse(int pin, long stime){
	pulseIn(pin, HIGH, stime);
}

long _count_pulses(int pin, long sampling_time, long pulse_max_time) {
    // reset
    long n = 0;

    long t0 = micros();
    while (true) {

        // detect
        _wait_pulse(pin, pulse_max_time);

        n++;

        // Time out
        if (micros() - t0 > sampling_time) { break; }
    }
    return n;
}

// ----------------------------------------------------------------------------
void _measure_led_sensor_1(long stime, long ptime){
    _led1_acc = _count_pulses(DO_LED1_PIN, stime, ptime);
}

void _measure_led_sensor_1() {
    _measure_led_sensor_1(do_leds_sampling_time, do_leds_per_pulse_timeout);
}

void _measure_led_sensor_2(long stime, long ptime){
    _led2_acc = _count_pulses(DO_LED2_PIN, stime, ptime);
}

void _measure_led_sensor_2() {
    _measure_led_sensor_2(do_leds_sampling_time, do_leds_per_pulse_timeout);
}


