#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/4_LogHandler.h"
#include "Base/4_MsgHandler.h"
#include "Base/4_SerialHandler.h"

// ----------------------------------------------------
// CONSTRUCTOR
LogHandler::LogHandler(Chemostat* Ch) : 
    AbsHandler(
        /* Chemostat */ Ch
    ){
    this->serial_vlevel = LOG_SERIAL_VLEVEL;
    this->sd_vlevel = LOG_SD_VLEVEL;
}


// ----------------------------------------------------
// SKETCH INTERFACE
void LogHandler::onsetup() {;}
void LogHandler::onloop() {;}


// ----------------------------------------------------
// _DEV INTERFACE
String LogHandler::getClassName() { return "LogHandler"; }
void LogHandler::sayHi() { 
    AbsHandler::sayHi(); // Parent
}

// ----------------------------------------------------
// LOG INTERFACE
void LogHandler::setSerialVLevel(byte vlv) { this->serial_vlevel = vlv; }
byte LogHandler::getSerialVLevel() { return this->serial_vlevel; }
void LogHandler::setSDVLevel(byte vlv) { this->sd_vlevel = vlv; }
byte LogHandler::getSDVLevel() { return this->sd_vlevel; }


// -------------------------
// HANDLE MSG INTERFACE
boolean LogHandler::handleMsg() { 

    MsgHandler* const pMSG = this->Ch->pMSG;

    // Check target code
    if (!pMSG->hasValString(0, "LOG")) { return false; }

    // VLEVEL INTERFACE
    // Example: $LOG:SET-SERIAL-VLEVEL:2%
    if (pMSG->hasValString(1, "SET-SERIAL-VLEVEL")) {
        this->setSerialVLevel(pMSG->getValString(2).toInt());
        pMSG->sendMsgResponse("serial_vlevel", this->getSerialVLevel());
        return true;
    }
    // Example: $LOG:GET-SERIAL-VLEVEL%
    if (pMSG->hasValString(1, "GET-SERIAL-VLEVEL")) {
        pMSG->sendMsgResponse("serial_vlevel", this->getSerialVLevel());
        return true;
    }

    // Example: $LOG:SET-SD-VLEVEL:2%
    if (pMSG->hasValString(1, "SET-SD-VLEVEL")) {
        this->setSDVLevel(pMSG->getValString(2).toInt());
        pMSG->sendMsgResponse("sd_vlevel", this->getSDVLevel());
        return true;
    }
    // Example: $LOG:GET-SD-VLEVEL%
    if (pMSG->hasValString(1, "GET-SD-VLEVEL")) {
        pMSG->sendMsgResponse("sd_vlevel", this->getSDVLevel());
        return true;
    }

    return false;
}