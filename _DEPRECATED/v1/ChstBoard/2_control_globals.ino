// ----------------------------------------------------------------------------
// PUMP SUBSYSTEM

#define PUMP_INCLUDE_FLAG_INPUT_KEY 101
bool pump_include_flag;
#define PUMP_DRY_RUN_FLAG_INPUT_KEY 102
bool pump_dry_run_flag;
#define PUMP_DILUTION_RATE_INPUT_KEY 103
float pump_dilution_rate; // the control parameter (1/h)
#define PUMP_WORKING_VOLUME_INPUT_KEY 104
float pump_working_volume; // (ml)
#define PUMP_VOL_PER_PULSE_INPUT_KEY 105
float pump_vol_per_pulse; // a calibration parameter (ml/pulse)
#define PUMP_PULSE_DURATION_INPUT_KEY 106
long pump_pulse_duration; // the length of a pump pulse (ms)
#define PUMP_BUFFER_TIME_INPUT_KEY 107
long pump_buffer_time; // idle time before pumping for stabilization (ms)
#define PUMP_TOT_PULSES_INPUT_KEY 108
long pump_tot_pulses;


// ----------------------------------------------------------------------------
// STIRREL SUBSYSTEM

#define STIRREL_INCLUDE_FLAG_INPUT_KEY 201
bool stirrel_include_flag;
#define STIRREL_DRY_RUN_FLAG_INPUT_KEY 202
bool stirrel_dry_run_flag;
#define STIRREL_PULSE_DURATION_INPUT_KEY 203
long stirrel_pulse_duration; // (ms)
#define STIRREL_ACTION_PERIOD_INPUT_KEY 204
long stirrel_action_period; // (ms)

// ----------------------------------------------------------------------------
// HEATER SUBSYSTEM

#define HEATER_INCLUDE_FLAG_INPUT_KEY 301
bool heater_include_flag;
#define HEATER_DRY_RUN_FLAG_INPUT_KEY 302
bool heater_dry_run_flag;
#define HEATER_TARGET_TEMP_INPUT_KEY 303
float heater_target_temp; // celsius
#define HEATER_ACTION_PERIOD_INPUT_KEY 304
long heater_action_period; // (ms)
#define HEATER_PULSE_DURATION_INPUT_KEY 305
long heater_pulse_duration; // (ms)

// ----------------------------------------------------------------------------
// IO SUBSYSTEM

#define IO_PRINT_INCLUDE_FLAG_INPUT_KEY 401
bool io_print_include_flag;
#define IO_PRINT_DRY_RUN_FLAG_INPUT_KEY 402
bool io_print_dry_run_flag;
#define IO_PRINT_ACTION_PERIOD_INPUT_KEY 403 // (ms)
long io_print_action_period; // 5000 // (ms)

// ----------------------------------------------------------------------------
// LOOP

#define LOOP_ENABLE_FLAG_INPUT_KEY 501
bool loop_enable_flag;

// ----------------------------------------------------------------------------
// DO SUBSYSTEM

#define DO_INCLUDE_FLAG_INPUT_KEY 601
bool do_include_flag;
#define DO_DRY_RUN_FLAG_INPUT_KEY 602
bool do_dry_run_flag;
#define DO_LASER_PWD_VAL_INPUT_KEY 603
int do_laser_pwd_val;
#define DO_ACTION_PERIOD_INPUT_KEY 604
long do_action_period; //  10000 // (ms) 
#define DO_LEDS_SAMPLING_TIME_INPUT_KEY  605
long do_leds_sampling_time; // (μs) 
#define LEDS_MAX_PER_PULSE_TIMEOUT_INPUT_KEY 606
long do_leds_per_pulse_timeout; // 10000 // (assert do_leds_per_pulse_timeout < do_leds_sampling_time) (μs)
#define LEDS_BUFFER_TIME_INPUT_KEY 607
long do_buffer_time; // 1000 // (ms)
