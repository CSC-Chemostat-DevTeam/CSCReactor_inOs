#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ----------------------------------------------------
// Serial communication (to be sync with PC side)

#define IO_BAUDRATE               115200

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

#define DO_LED1_PIN                   A8
#define DO_LED2_PIN                   A12

#define STIRREL_PIN                   29 
#define SD_MOSI_PIN                   51 // FIXXED
#define SD_MISO_PIN                   50 // FIXXED

#define STIRREL_DIR1_PIN              8
#define STIRREL_DIR2_PIN              8

#define DO_LASER_PWD_PIN              5  // PWD

#define HEATER_T_SENSOR_PIN           35
#define BOTTOM_INTERRUP_PIN           3  


// ----------------------------------------------------
// StaticStrings.h

#define STATIC_STRING_BUFFER_LEN 128

// ----------------------------------------------------
// Chemostat.h

#define CHEMOSTAT_HANDLERS_BUFFER_SIZE 32

// ----------------------------------------------------
// CSVLineReader.h

#define CSV_LINE_READER_VALS_NUMBER 5

// (to be sync with PC side)
// Example of CSV line $key:VAL0:VAL1%
#define CSV_LINE_INIT_CHAR '$'
#define CSV_LINE_SEP_CHAR ':'
#define CSV_LINE_END_CHAR '%'

// ----------------------------------------------------
// DOHandler
#define DO_LASER_PWD_DFLT_VALUE              200  // PROPTO LASER POWER
#define DO_LED_SAMPLING_TIME                 100  // (ms) led pulse collection time

// ----------------------------------------------------
// MsgHandler

#define TRY_READ_MSG_TIMEOUT 300 // ms
// #define MSG_ACK_WAIT_TIMEOUT 50 // ms

// (to be sync with PC side)
// TODO: find the cpp way of handling strings constants
#define MSG_RECIEVED_TOKEN "RECIEVED!!!"
#define MSG_RESPONSE_DONE_TOKEN  "DONE!!!"
#define MSG_ACKNOWLADGE_TOKEN "ACK"
#define UNKNOWN_CMD_ERROR_TOKEN "ERROR, UNKNOWN COMMAND!!!"
#define SD_TEST_FILE_PATH "TEST"

// ----------------------------------------------------
// LogHandler

#define LOG_ERROR_LEVEL       40
#define LOG_WARN_LEVEL        30
#define LOG_INFO_LEVEL        20
#define LOG_DEV_LEVEL         10
#define LOG_NOTSET_LEVEL      0

#define LOG_INIT_TOKEN ">>>"
#define LOG_END_TOKEN "<<<"

#define LOG_ERR_TAG "ERROR"
#define LOG_INFO_TAG "INFO"
#define LOG_WARN_TAG "WARN"
#define LOG_DEV_TAG "DEV"

#define LOG_SERIAL_VLEVEL 10
#define LOG_SD_VLEVEL 0


// ----------------------------------------------------
// Stirrel

#define STIRREL_PULSE_TIME_DFLT_VAL 300
#define STIRREL_DIR1_PWD_DFLT_VAL 250
#define STIRREL_DIR2_PWD_DFLT_VAL 250

// ----------------------------------------------------
// UTILS

#define TAB "   "
#define LINE_SEPARATOR "----------------------"


#endif // CONFIG_H