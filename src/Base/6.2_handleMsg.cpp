#include "Base/1_config.h"
#include "Base/2_Utils.h"
#include "Base/3_CSVLineReader.h"
#include "Base/5_SerialDriver.h"
#include "Base/6_SerialCSVDriver.h"

/// -------------------------
/// HANDLE MSG INTERFACE
boolean SerialCSVDriver::handleMsg() { 
    
    // Check target code
    if (!SerialCSVDriver::hasValString(0, "CSV")) { return false; }

    // TEST MSGS
    // Example: $CSV:SAY-HI%
    if (SerialCSVDriver::hasValString(1, "SAY-HI")) {
        SerialCSVDriver::sayHi(); 
        return true;
    }

    // ECHO
    // Example: $CSV:ECHO:BLA:10%
    if (SerialCSVDriver::hasValString(1, "ECHO")) {
        int n = 1;
        String val2 = SerialCSVDriver::getValString(2);
        String val3 = SerialCSVDriver::getValString(3);
        if (!val3.equals("")) { n = val3.toInt();}
        for (int i = 0; i < n; i++) {
            SerialCSVDriver::sendMsgResponse(val2);
        }
        return true;
    }

    // TEST-RES
    // Example: $CSV:TEST-RES:VAL1:VAL2:VAL3...%
    if (SerialCSVDriver::hasValString(1, "TEST-RES")) {
        unsigned int i = 2;
        while (1) {
            if (SerialCSVDriver::isEmpty(i)) { break; }
            int val = SerialCSVDriver::getValInt(i);
            SerialCSVDriver::sendMsgResponse("val", val);
            i++;
        }
        return true;
    }

    return false;
}
