#include "Base/1_config.h"
#include "Base/2_Utils.h"
#include "Base/3_CSVLineReader.h"
#include "Base/5_SerialDriver.h"
#include "Base/6_SerialCSVDriver.h"

// ----------------------------------------------------
CSVLineReader SerialCSVDriver::csvline = CSVLineReader();
unsigned long SerialCSVDriver::respcount = 0;

// ----------------------------------------------------
// SKETCH INTERFACE
void SerialCSVDriver::onsetup(){
    SerialCSVDriver::sayHi();
}

void SerialCSVDriver::onloop(){

    // Serial.println(">>> SerialCSVDriver::onloop <<<");

    // read cmd
    if (SerialDriver::available() > 0) {
        SerialCSVDriver::tryReadMsg(TRY_READ_MSG_TIMEOUT);
    }

    // handle all handlers commands
    SerialCSVDriver::handleAllMsgs();

    // Reset reader
    SerialCSVDriver::reset(); // reset reader
}


/// -------------------------
// MSG INTERFACE
String SerialCSVDriver::getValString(byte i) {
    return SerialCSVDriver::csvline.getValString(i);
}

/// -------------------------
/// MSG VALS QUERYS
boolean SerialCSVDriver::hasValString(byte i, const String& str) {
    return SerialCSVDriver::getValString(i).equals(str);
}

boolean SerialCSVDriver::hasValStringPrefix(byte i, const String& prefix) {
    return SerialCSVDriver::getValString(i).startsWith(prefix);
}

boolean SerialCSVDriver::hasValStringSuffix(byte i, const String& suffix) {
    return SerialCSVDriver::getValString(i).endsWith(suffix);
}

/// -------------------------
void SerialCSVDriver::reset(){
    SerialCSVDriver::csvline.reset(); // reset reader
    SerialCSVDriver::respcount = 0;
}

// If cmd buffers are empty, listen for incoming commands for 'tout' time;
void SerialCSVDriver::tryReadMsg(unsigned long tout){
    // Serial.println(">>> SerialCSVDriver::tryReadMsg <<<");

    // If non reset called, skip
    if (SerialCSVDriver::msgAvailable()) { return; }

    // local
    long t0 = millis();
    int flag = PARSER_READY_FOR_NEXT;
    while (1) { 
        if (millis() - t0 > tout) { break; } // TIME OUT
        while (SerialDriver::available() > 0) {
            // parse char
            char c = SerialDriver::read();
            int flag = SerialCSVDriver::csvline.parseChar(c);
            if (flag == PARSER_READY_FOR_NEXT) { continue; }
            if (flag == PARSER_ERROR) { SerialCSVDriver::reset(); break; }
            if (flag == PARSER_MSG_COMPLETED) { break; }
        }
        if (flag == PARSER_ERROR) { SerialCSVDriver::reset(); break; }
        if (SerialCSVDriver::msgAvailable()) { break; }
    }
}

void SerialCSVDriver::tryReadMsg(const String& msg){
    // Serial.println(">>> SerialCSVDriver::tryReadMsg <<<");

    // If non reset called, skip
    if (SerialCSVDriver::msgAvailable()) { return; }

    int flag = SerialCSVDriver::csvline.parseChar(msg);
    if (flag == PARSER_ERROR) { SerialCSVDriver::reset(); }
}

/// -------------------------
/// RESPONSE INTERFACE

void SerialCSVDriver::openMsgResponse(){
    // Some pretty formatting
    SerialDriver::println(LINE_SEPARATOR);

    // ACKNOWLADGE
    // Example $ACK:REQ-HASH:TIMETAG:RECIEVED!!!%
    SerialCSVDriver::sendMsgAcknowladge(MSG_RECIEVED_TOKEN);
    SerialDriver::println(SerialCSVDriver::msgCsvLineString()); 
}

void SerialCSVDriver::closeMsgResponse(){

    // ACKNOWLADGE
    SerialCSVDriver::sendMsgAcknowladge(MSG_RESPONSE_DONE_TOKEN);
    
    // Some pretty formatting
    SerialDriver::newLine();

    // flush
    SerialDriver::flush();
}

// ----------------------------------------------------
// CSVLineReader INTERFACE

boolean SerialCSVDriver::msgAvailable(){
    return SerialCSVDriver::csvline.valid_input;
}
unsigned int SerialCSVDriver::linehash(){
    return SerialCSVDriver::csvline.hash();
}
unsigned long SerialCSVDriver::timetag(){
    return (unsigned int)(millis());
}

String SerialCSVDriver::msgCsvLineString(){
    return SerialCSVDriver::csvline.csvLineString();
}

// ----------------------------------------------------
// _DEV INTERFACE
void SerialCSVDriver::sayHi() { 
    SerialDriver::println("Hi from SerialCSVDriver");
}
