#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include "Base/1_constants.h"

// ----------------------------------------------------------------------------
// This is the entry file for manual configuration of the Board
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// MODES
#define DEV_MODE                true

// ----------------------------------------------------------------------------
// INCLUDE FLAGS
#define CMD_INCLUDE_FLAG_DFLT_VAL                true
#define PUMP_INCLUDE_FLAG_DFLT_VAL               false
#define TSENSOR_INCLUDE_FLAG_DFLT_VAL            true
#define STIRREL_INCLUDE_FLAG_DFLT_VAL            true
#define DO_INCLUDE_FLAG_DFLT_VAL                 true
#define SD_INCLUDE_FLAG_DFLT_VAL                 true
#define BOTT_INCLUDE_FLAG_DFLT_VAL               true
#define DATALOGGER_INCLUDE_FLAG_DFLT_VAL         true
#define UPLOADER_INCLUDE_FLAG_DFLT_VAL           true
#define PROGRAMER_INCLUDE_FLAG_DFLT_VAL          true

// ----------------------------------------------------------------------------
// PINS

// // Arduino UNO
// #define DO_LED1_PIN                 2
// #define DO_LASER_PWD_PIN            3 // PWD
// #define DO_LED2_PIN                 4
// #define HEATER_T_SENSOR_PIN         5
// #define STIRREL_PIN                 6
// #define PUMP_PIN                    8
// #define HEATER_PIN                  9
// #define SD_CS_PIN                   10
// #define SD_MOSI_PIN                 11 // FIXXED
// #define SD_MISO_PIN                 12 // FIXXED
// #define SD_SCK_PIN                  13 // FIXXED

// Arduino Mega
#define PUMP_PIN                      32
#define SD_CS_PIN                     53 // FIXXED
#define HEATER_PIN                    24
#define SD_SCK_PIN                    52 // FIXXED
#define DO_LED1_PIN                   43
#define DO_LED2_PIN                   38
#define STIRREL_PIN                   29 
#define SD_MOSI_PIN                   51 // FIXXED
#define SD_MISO_PIN                   50 // FIXXED
#define DO_LASER_PWD_PIN              7  // PWD
#define HEATER_T_SENSOR_PIN           35
#define BOTTOM_INTERRUP_PIN           3  

// ----------------------------------------------------------------------------
// IO protocole (to be sync with master side)

#define IO_BAUDRATE               115200
#define IO_PRINT_START_MARKER     "+++"
#define IO_PRINT_END_MARKER       "---"
#define DATALOGGER_SEPARATOR      ","

// ----------------------------------------------------------------------------
// BOTTOM SUBSYSTEM
#define BOTTOM_SAFE_PERIOD                   1000 // ms

// ----------------------------------------------------------------------------
// PUMP SUBSYSTEM
#define PUMP_DRY_RUN_FLAG_DFLT_VAL           true // For testing
// #define PUMP_DILUTION_RATE_DFLT_VAL       0.0
// #define PUMP_WORKING_VOLUME_DFLT_VAL      0.0
// #define PUMP_VOL_PER_PULSE_DFLT_VAL       0.0
#define PUMP_PULSE_PERIOD_DFLT_VAL           5000 // (ms)
#define PUMP_PULSE_DURATION_DFLT_VAL         300 // (ms)
#define PUMP_BUFFER_TIME_DFLT_VAL            500 // (ms)
#define PUMP_TOT_PULSES_DFLT_VAL             INFTY_LONG

// ----------------------------------------------------------------------------
// STIRREL SUBSYSTEM
#define STIRREL_DRY_RUN_FLAG_DFLT_VAL        false
#define STIRREL_PULSE_HIGH_TIME_DFLT_VAL     100 // (ms)
#define STIRREL_PULSE_LOW_TIME_DFLT_VAL      300 // (ms)

// ----------------------------------------------------------------------------
// HEATER SUBSYSTEM
#define HEATER_DRY_RUN_FLAG_DFLT_VAL          true
#define HEATER_TARGET_TEMP_DFLT_VAL           0.0 // Celsious
#define TSENSOR_MEASUREMENT_PERIOD_DFLT_VAL   3000 // (ms)
#define HEATER_ACTION_PERIOD_DFLT_VAL         3000 // (ms)
#define HEATER_PULSE_DURATION_DFLT_VAL        1000 // (ms)

// ----------------------------------------------------------------------------
// IO SUBSYSTEM
#define IO_PRINT_DRY_RUN_FLAG_DFLT_VAL        false
#define IO_PRINT_ACTION_PERIOD_DFLT_VAL       5000 // (ms)

// ----------------------------------------------------------------------------
// LOOP CONTROL SUBSYSTEM
#define LOOP_ENABLE_FLAG_DFLT_VAL             false

// ----------------------------------------------------------------------------
// DO SUBSYSTEM
#define DO_DRY_RUN_FLAG_DFLT_VAL              true
#define DO_LASER_PWD_VAL_DFLT_VAL             190
#define DO_ACTION_PERIOD_DFLT_VAL             10000 // (ms)
#define DO_LEDS_SAMPLING_TIME_DFLT_VAL        50    // (ms) 
#define DO_MAX_PER_PULSE_TIMEOUT_DFLT_VAL     10    // (assert do_leds_per_pulse_timeout < do_leds_sampling_time) (ms)
#define DO_BUFFER_TIME_DFLT_VAL               500   // (ms) 

// ----------------------------------------------------------------------------
// SD SUBSYSTEM
#define SD_LOOP_ACTION_TIMER_FREC             100


#endif // BOARD_CONFIG_H
