#include "Base/1_config.h"
#include "Base/2_Utils.h"
#include "Base/3_CSVLineReader.h"
#include "Base/5_SerialDriver.h"
#include "Base/6_SerialCSVDriver.h"
#include "Base/7_ArduinoDriver.h"

// ----------------------------------------------------
// place for registering MdgHandlers

// pMSG INTERFACE
void SerialCSVDriver::handleAllMsgs(){

    // Serial.println(">>> Chemostat::handleAllMsgs <<<");

    // no cmd is a noop
    if (!SerialCSVDriver::msgAvailable()) { return; }

    // Open response
    SerialCSVDriver::openMsgResponse();
    
    // // call all handlers
    // INTERFACE: place here all CSV Msgs handlers
    if (0) {;}
    else if (Utils::handleMsg()) {;}
    else if (SerialDriver::handleMsg()) {;}
    else if (SerialCSVDriver::handleMsg()) {;}
    else if (ArduinoDriver::handleMsg()) {;}
    else {
        // fallback
        SerialCSVDriver::sendMsgResponse(UNKNOWN_CMD_ERROR_TOKEN);
    }

    // close response
    SerialCSVDriver::closeMsgResponse();

}