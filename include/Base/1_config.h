#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <limits.h>

// ----------------------------------------------------
// MARK: Serial communication
// #NOTE: to be sync with PC side

#define SERIAL_BAUDRATE 19200

// ----------------------------------------------------
// MARK: Collection.h
#define COLLECTION_NULL_TOKEN INT_MIN
#define COLLECTION_BUFFER_LEN 32

// ----------------------------------------------------
// MARK: InoDriver.h

#define PIN_PULSE_OUT_MAX_TIME 2000

#define ANALOG_OP_TYPE 0
#define DIGITAL_OP_TYPE 1
#define DRY_OP_TYPE 2
#define NONDRY_OP_TYPE 3

#define PIN_PULSE_IN_TIMEOUT 500UL // micro seconds

// ----------------------------------------------------
// MARK: CSVLineReader.h

#define CSV_LINE_READER_VALS_NUMBER 32

// (to be sync with PC side)
// Example of CSV line $key:VAL0:VAL1%
#define CSV_LINE_INIT_CHAR '$'
#define CSV_LINE_SEP_CHAR ':'
#define CSV_LINE_END_CHAR '%'

// parser states
#define PARSER_READY_FOR_NEXT 1
#define PARSER_ERROR 2
#define PARSER_MSG_COMPLETED 3

// ----------------------------------------------------
// MARK: 4_CSCReactor.h
#define PROD_RUN_MODE 0
#define DEV_RUN_MODE 1

// ----------------------------------------------------
// MARK: MsgHandler

#define TRY_READ_MSG_TIMEOUT 300 // ms

// (to be sync with PC side)
// TODO: find the cpp way of handling strings constants
#define MSG_RECIEVED_TOKEN "RECIEVED!!!"
#define MSG_RESPONSE_DONE_TOKEN "DONE!!!"
#define MSG_ACKNOWLADGE_TOKEN "ACK"
#define MSG_ECHO_TOKEN "ECHO"
#define UNKNOWN_CMD_ERROR_TOKEN "ERROR, UNKNOWN COMMAND!!!"

// ----------------------------------------------------
// MARK: LogHandler

#define LOG_ERROR_LEVEL 40
#define LOG_WARN_LEVEL 30
#define LOG_INFO_LEVEL 20
#define LOG_DEV_LEVEL 10
#define LOG_NOTSET_LEVEL 0

#define LOG_INIT_TOKEN ">>>"
#define LOG_END_TOKEN "<<<"

#define LOG_ERR_TAG "ERROR"
#define LOG_INFO_TAG "INFO"
#define LOG_WARN_TAG "WARN"
#define LOG_DEV_TAG "DEV"

#define LOG_SERIAL_VLEVEL 10
#define LOG_SD_VLEVEL 0

// ----------------------------------------------------
// MARK: UTILS

#define TAB "   "
#define LINE_SEPARATOR "----------------------"

#endif // CONFIG_H