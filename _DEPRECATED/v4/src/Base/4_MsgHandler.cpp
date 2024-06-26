#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/3_CSVLineReader.h"
#include "Base/4_MsgHandler.h"
#include "Base/4_SerialHandler.h"

// ----------------------------------------------------
// CONSTRUCTOR
MsgHandler::MsgHandler(Chemostat* Ch) :
    AbsHandler(
        /* Chemostat */ Ch
    ){
    // Serial.println(">>> At MsgHandler::MsgHandler <<<");
    this->csvline = CSVLineReader();
    this->respcount = 0;
}

// ----------------------------------------------------
// SKETCH INTERFACE
void MsgHandler::onsetup(){ ; }

void MsgHandler::onloop(){
    
    // Serial.println(">>> MsgHandler::onloop <<<");

    // read cmd
    SerialHandler* pSERIAL = this->Ch->pSERIAL;
    if (pSERIAL->available() > 0) {
        this->tryReadMsg(TRY_READ_MSG_TIMEOUT);
    }

    // handle all handlers commands
    this->Ch->handleAllMsgs();

    // Reset reader
    this->reset(); // reset reader
}

/// -------------------------
/// HANDLE MSG INTERFACE
boolean MsgHandler::handleMsg() { return false; }

/// -------------------------
// MSG INTERFACE
String MsgHandler::getValString(byte i) {
    return this->csvline.getValString(i);
}

/// -------------------------
/// MSG VALS QUERYS
boolean MsgHandler::hasValString(byte i, const String& str) {
    return this->getValString(i).equals(str);
}

boolean MsgHandler::hasValStringPrefix(byte i, const String& prefix) {
    return this->getValString(i).startsWith(prefix);
}

boolean MsgHandler::hasValStringSuffix(byte i, const String& suffix) {
    return this->getValString(i).startsWith(suffix);
}

/// -------------------------
void MsgHandler::reset(){
    this->csvline.reset(); // reset reader
    this->hash = 0;
    this->respcount = 0;
}

// If cmd buffers are empty, listen for incoming commands for 'tout' time;
void MsgHandler::tryReadMsg(unsigned long tout){

    // Serial.println(">>> MsgHandler::tryReadMsg <<<");

    // If non reset called, skip
    if (this->hasValidMsg()) { return; }

    // local
    SerialHandler* pSERIAL = this->Ch->pSERIAL;
    long t0 = millis();
    while (1) { 
        if (millis() - t0 > tout) { break; } // TIME OUT
        while (pSERIAL->available() > 0) {
            // parse char
            char c = pSERIAL->read();
            boolean ok_flag = this->csvline.parseChar(c);
            if (!ok_flag) { this->reset(); break; }
            delay(1); // Stability?
        } 
        // Done
        if (this->hasValidMsg()) { 
            this->hash = this->msgHash(); // msg hash
            break; 
        }
    }
}

void MsgHandler::tryReadMsg(const String& msg){
    
    // Serial.println(">>> MsgHandler::tryReadMsg <<<");

    // If non reset called, skip
    if (this->hasValidMsg()) { return; }

    boolean ok_flag = this->csvline.parseChar(msg);
    if (!ok_flag) { this->reset(); }
    if (this->hasValidMsg()) { this->hash = this->msgHash(); }
}


/// -------------------------
/// RESPONSE INTERFACE

void MsgHandler::openMsgResponse(){
    
    // Some pretty formatting
    this->Ch->pSERIAL->println(LINE_SEPARATOR);
    this->Ch->pSERIAL->println("MSG ", this->Ch->pMSG->msgCsvLineString()); 

    // ACKNOWLADGE
    // Example $ACK:REQ-HASH:TIMETAG:RECIEVED!!!%
    sendMsgAcknowladge(MSG_RECIEVED_TOKEN);
}

void MsgHandler::closeMsgResponse(){

    // ACKNOWLADGE
    // Example $ACK:REQ-HASH:TIMETAG:RECIEVED%
    if (this->respcount > 0) { // ignore if no response was triggered
        sendMsgAcknowladge(MSG_RESPONSE_DONE_TOKEN);
    }
    
    // Some pretty formatting
    this->Ch->pSERIAL->newLine(); 
}

// ----------------------------------------------------
// CSVLineReader INTERFACE

boolean MsgHandler::hasValidMsg(){
    return this->csvline.valid_input;
}

unsigned int MsgHandler::msgHash(){
    return this->csvline.hash();
}

String MsgHandler::msgCsvLineString(){
    return this->csvline.csvLineString();
}


// ----------------------------------------------------
// _DEV INTERFACE
String MsgHandler::getClassName() { return "MsgHandler"; }
