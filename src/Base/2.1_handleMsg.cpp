#include "Base/1_config.h"
#include "Base/2_Utils.h"
#include "Base/6_SerialCSVDriver.h"

/// -------------------------
/// HANDLE MSG INTERFACE
boolean Utils::handleMsg()
{

    // Check target code
    if (!SerialCSVDriver::hasValString(0, "UT"))
    {
        return false;
    }

    // TEST MSGS
    // Example: $UT:SAY-HI%
    if (SerialCSVDriver::hasValString(1, "SAY-HI"))
    {
        SerialCSVDriver::sendMsgResponse("Hi from Utils");
        return true;
    }

    // $UT:HASH:STR%
    if (SerialCSVDriver::hasValString(1, "HASH-STR"))
    {
        String str = SerialCSVDriver::getValString(2);
        unsigned int h = Utils::crc16_hash(str, 0);
        SerialCSVDriver::sendMsgResponse("hash", h);
        return true;
    }

    return false;
}
