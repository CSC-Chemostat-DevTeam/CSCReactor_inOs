#include "Base/1_config.h"
#include "Base/2_Utils.h"
#include "Base/4_CSCReactor.h"
#include "Base/5_SerialDriver.h"
#include "Base/6_SerialCSVDriver.h"

/// -------------------------
/// HANDLE MSG INTERFACE
boolean CSCReactor::handleMsg()
{

    // Check target code
    if (!SerialCSVDriver::hasValString(0, "SYS"))
    {
        return false;
    }

    // TEST MSGS
    // Example: $SYS:SAY-HI%
    if (SerialCSVDriver::hasValString(1, "SAY-HI"))
    {
        CSCReactor::sayHi();
        return true;
    }

    // GET-DEVMODE
    // Example: $SYS:GET-DEVMODE%
    if (SerialCSVDriver::hasValString(1, "GET-DEVMODE"))
    {
        boolean mode = CSCReactor::devmode;
        SerialCSVDriver::sendMsgResponse("devmode", mode);
        return true;
    }

    // SET-DEVMODE
    // Example: $SYS:SET-DEVMODE:mode%
    if (SerialCSVDriver::hasValString(1, "SET-DEVMODE"))
    {
        String val2 = SerialCSVDriver::getValString(2);
        int mode = 0;
        if (!val2.equals(""))
        {
            mode = val2.toInt();
        }
        CSCReactor::devmode = (mode == 1);
        SerialCSVDriver::sendMsgResponse(val2);
        return true;
    }

    return false;
}
