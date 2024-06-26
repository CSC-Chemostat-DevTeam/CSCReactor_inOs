#include "Base/1_config.h"
#include "Base/2_Utils.h"
#include "Base/6_SerialCSVDriver.h"

/// -------------------------
// DEV
// unsigned int _crc16_hash2(unsigned int crc, char c) {
//     Utils::_println("[] ", "c=", c, ", crc=", crc);
//     crc ^= c;
//     Utils::_println("[crc ^= c] ", "crc=", crc);
//     for (int i = 0; i < 8; ++i)
//     {
//         if (crc & 1) {
//             crc = (crc >> 1) ^ 0xA001;
//             Utils::_println("[(crc >> 1) ^ 0xA001] ", "crc=", crc);
//         } else {
//             crc = (crc >> 1);
//             Utils::_println("[crc = (crc >> 1)] ", "crc=", crc);
//         }
//     }
//     Utils::_println("[] ", "crc=", crc);
//     return crc;
// }

/// -------------------------
/// HANDLE MSG INTERFACE
boolean Utils::handleMsg() { 
    
    // Check target code
    if (!SerialCSVDriver::hasValString(0, "UT")) { return false; }

    // TEST MSGS
    // Example: $UT:SAY-HI%
    if (SerialCSVDriver::hasValString(1, "SAY-HI")) {
        SerialCSVDriver::sendMsgResponse("Hi from Utils");
        return true;
    }

    // $UT:HASH:STR%
    if (SerialCSVDriver::hasValString(1, "HASH-STR")) {
        String str = SerialCSVDriver::getValString(2);
        unsigned int h = Utils::crc16_hash(0, str);
        SerialCSVDriver::sendMsgResponse("hash", h);
        return true;
    }

    return false;
}

