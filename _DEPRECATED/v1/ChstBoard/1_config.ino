// ----------------------------------------------------------------------------
// PINS
// 2 3 4 5 6 - 8 9 10 11 12 13

#define DO_LED1_PIN 2
#define DO_LASER_PWD_PIN 3 // PWD
#define DO_LED2_PIN 4
#define HEATER_T_SENSOR_PIN 5
#define STIRREL_PIN 6
#define PUMP_PIN 8
#define HEATER_PIN 9
#define SD_CS_PIN 10
#define SD_MOSI_PIN 11 // FIXXED
#define SD_MISO_PIN 12 // FIXXED
#define SD_SCK_PIN 13 // FIXXED

// ----------------------------------------------------------------------------
// IO

#define IO_BAUDRATE 9600

#define IO_INPUT_TIMEOUT 100
#define IO_INPUT_INIT_CHAR '$'
#define IO_INPUT_SEP_CHAR ':'
#define IO_INPUT_END_CHAR '%'

#define IO_PRINT_START_MARKER "+++"
#define IO_PRINT_END_MARKER "---"

// ----------------------------------------------------------------------------
// DEFAULTS CONTROL GLOBALS

// PUMP SUBSYSTEM
#define PUMP_INCLUDE_FLAG_DFLT_VAL false
#define PUMP_DRY_RUN_FLAG_DFLT_VAL true
#define PUMP_DILUTION_RATE_DFLT_VAL 0.0
#define PUMP_WORKING_VOLUME_DFLT_VAL 0.0
#define PUMP_VOL_PER_PULSE_DFLT_VAL 0.0
#define PUMP_PULSE_DURATION_DFLT_VAL 300 // (ms)
#define PUMP_BUFFER_TIME_DFLT_VAL 5000 // (ms)
#define PUMP_TOT_PULSES_DFLT_VAL INFTY_LONG

// STIRREL SUBSYSTEM
#define STIRREL_INCLUDE_FLAG_DFLT_VAL false
#define STIRREL_DRY_RUN_FLAG_DFLT_VAL false
#define STIRREL_PULSE_DURATION_DFLT_VAL 200 // (ms)
#define STIRREL_ACTION_PERIOD_DFLT_VAL 1000 // (ms)

// HEATER SUBSYSTEM
#define HEATER_INCLUDE_FLAG_DFLT_VAL false
#define HEATER_DRY_RUN_FLAG_DFLT_VAL true
#define HEATER_TARGET_TEMP_DFLT_VAL 0.0
#define HEATER_ACTION_PERIOD_DFLT_VAL 3000 // (ms)
#define HEATER_PULSE_DURATION_DFLT_VAL 1000 // (ms)

// IO SUBSYSTEM
#define IO_PRINT_INCLUDE_FLAG_DFLT_VAL true
#define IO_PRINT_DRY_RUN_FLAG_DFLT_VAL false
#define IO_PRINT_ACTION_PERIOD_DFLT_VAL 5000 // (ms)

// LOOP CONTROL
#define LOOP_ENABLE_FLAG_DFLT_VAL false

// DO SUBSYSTEM
#define DO_INCLUDE_FLAG_DFLT_VAL false
#define DO_DRY_RUN_FLAG_DFLT_VAL true
#define DO_LASER_PWD_VAL_DFLT_VAL 190
#define DO_ACTION_PERIOD_DFLT_VAL 5000 // (ms)
#define DO_LEDS_SAMPLING_TIME_DFLT_VAL 50000 // (μs) 
#define LEDS_MAX_PER_PULSE_TIMEOUT_DFLT_VAL 10000 // (assert do_leds_per_pulse_timeout < do_leds_sampling_time) (μs)
#define LEDS_BUFFER_TIME_DFLT_VAL 1000 // (ms) 

