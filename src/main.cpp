// Global libs
#include <Arduino.h>
#include <Base/4_CSCReactor.h>
#include <Base/5_SerialDriver.h>
#include <Base/6_SerialCSVDriver.h>
#include <Base/7_InoDriver.h>
#include <Base/8_DHT11Driver.h>

// TODO: Stop using Arduino.hString class, use string or char[] (explore string.h, ctype.h)

void setup()
{
    SerialDriver::onsetup();
    SerialCSVDriver::onsetup();
    InoDriver::onsetup();
    DHT11Driver::onsetup();
    CSCReactor::onsetup();
}

void loop()
{
    SerialDriver::onloop();
    SerialCSVDriver::onloop();
}
