#include "Base/1_config.h"
#include "Base/2_Utils.h"
#include "Base/3_CSVLineReader.h"
#include "Base/4_CSCReactor.h"
#include "Base/5_SerialDriver.h"
#include "Base/6_SerialCSVDriver.h"
#include "Base/7_InoDriver.h"
#include "Base/8_DHT11Driver.h"

// ----------------------------------------------------
// place for registering MdgHandlers

// pMSG INTERFACE
void SerialCSVDriver::handleAllMsgs()
{

    // Serial.println(">>> Chemostat::handleAllMsgs <<<");

    // no cmd is a noop
    if (!SerialCSVDriver::isEmpty())
    {
        return;
    }

    // Open response
    SerialCSVDriver::openMsgResponse();

    // call all handlers
    // INTERFACE: place here all CSV Msgs handlers
    while (1)
    {
        if (Utils::handleMsg())
        {
            break;
        }
        if (SerialDriver::handleMsg())
        {
            break;
        }
        if (SerialCSVDriver::handleMsg())
        {
            break;
        }
        if (InoDriver::handleMsg())
        {
            break;
        }
        if (CSCReactor::handleMsg())
        {
            break;
        }
        if (DHT11Driver::handleMsg())
        {
            break;
        }
        // fallback
        SerialCSVDriver::sendMsgResponse(UNKNOWN_CMD_ERROR_TOKEN);
        break;
    }

    // close response
    SerialCSVDriver::closeMsgResponse();
}