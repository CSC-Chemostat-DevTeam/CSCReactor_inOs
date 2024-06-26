#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/4_SerialHandler.h"
#include "Base/4_MsgHandler.h"

// ----------------------------------------------------
// CONSTRUCTOR
SerialHandler::SerialHandler(Chemostat* Ch) : 
    AbsHandler(
        /* Chemostat */ Ch
    ){
    this->baud_rate = IO_BAUDRATE;
}

// ----------------------------------------------------
// SKETCH INTERFACE
void SerialHandler::onsetup(){ 
    Serial.begin(this->baud_rate);
    while (!Serial) {
        ;  // wait for serial port to connect. Needed for native USB port only
    }
    // this->info("Serial connected, boud rate: ", this->baud_rate);
}

void SerialHandler::onloop(){ ; }

// ----------------------------------------------------
// _DEV INTERFACE
String SerialHandler::getClassName() { return "SerialHandler"; }
void SerialHandler::sayHi() { 
    AbsHandler::sayHi(); // Parent
    Ch->pSERIAL->println(TAB, "boud rate: ", this->baud_rate);
}

// ----------------------------------------------------
// PRINT INTERFACE
// See header
void SerialHandler::newLine() { Serial.println(); }

// -------------------------
// HANDLE MSG INTERFACE
boolean SerialHandler::handleMsg() { 

    MsgHandler* const pMSG = this->Ch->pMSG;

    // Check target code
    if (!pMSG->hasValString(0, "SERIAL")) { return false; }

    // PING
    // Example: $SERIAL:PING%
    if (pMSG->hasValString(1, "PING")) {
        // empty msg, just akc
        return true;
    }

    // BAUD
    // Example: $SERIAL:BAUD-RATE%
    if (pMSG->hasValString(1, "BAUD-RATE")) {
        pMSG->sendMsgResponse("baud_rate", this->baud_rate);
        return true;
    }

    return false; 
}


