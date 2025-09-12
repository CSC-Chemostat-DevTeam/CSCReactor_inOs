#include "Base/1_config.h"
#include "Base/2_Utils.h"
#include "Base/3_CSVLineReader.h"
#include "Base/4_CSCReactor.h"
#include "Base/5_SerialDriver.h"
#include "Base/6_SerialCSVDriver.h"
#include "Base/7_InoDriver.h"
#include "Base/8_DHT11Driver.h"

/// -------------------------
/// HANDLE MSG INTERFACE
boolean DHT11Driver::handleMsg()
{

    // Check target code
    if (!SerialCSVDriver::hasValString(0, "DHT11"))
    {
        return false;
    }

    // MARK: SAY-HI
    // Example: $DHT11:SAY-HI%
    if (SerialCSVDriver::hasValString(1, "SAY-HI"))
    {
        DHT11Driver::sayHi();
        return true;
    }

    //// ------------
    // MARK: MEASSURE
    // $DHT11:MEASSURE:PIN%
    if (SerialCSVDriver::hasValString(1, "MEASSURE"))
    {
        float T;
        float H;
        if (CSCReactor::devmode)
        {
            T = random(0, 100) / 1.0;
            H = random(0, 100) / 1.0;
        }
        else
        {
            int pin = SerialCSVDriver::getValString(2).toInt();
            DHT11Driver::begin(pin); // init on demand
            T = DHT11Driver::getTemperature();
            H = DHT11Driver::getHumidity();
        }
        SerialCSVDriver::sendMsgResponse("T", T);
        SerialCSVDriver::sendMsgResponse("H", H);
        return true;
    }

    return false;
}