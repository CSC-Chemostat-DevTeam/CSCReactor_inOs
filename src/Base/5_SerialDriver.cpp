#include "Base/1_config.h"
#include "Base/2_Utils.h"
#include "Base/5_SerialDriver.h"

// ----------------------------------------------------
unsigned long SerialDriver::baud_rate = SERIAL_BAUDRATE;

// ----------------------------------------------------
void SerialDriver::onsetup()
{
    SerialDriver::initConnection(SERIAL_BAUDRATE);
    SerialDriver::sayHi();
}
void SerialDriver::onloop() { ; }

void SerialDriver::initConnection(unsigned long baud_rate)
{
    // Up baud_rate
    SerialDriver::baud_rate = baud_rate;

    // first time
    while (!Serial)
    {
        Serial.begin(baud_rate);
        delay(3);
        if (Serial)
        {
            return;
        }
    }

    // from here: https://forum.arduino.cc/t/change-baud-rate-at-runtime/368191/3
    Serial.flush(); // wait for last transmitted data to be sent
    Serial.begin(baud_rate);
    delay(3);
    while (Serial.available())
        Serial.read(); // empty  out possible garbage from input buffer
    // if the device was sending data while you changed the baud rate, the info in the input buffer is corrupted.

    // this->info("Serial connected, boud rate: ", this->baud_rate);
}

int SerialDriver::available() { return Serial.available(); }
int SerialDriver::read() { return Serial.read(); }
void SerialDriver::newLine() { Serial.println(); }
void SerialDriver::flush() { Serial.flush(); }

// ----------------------------------------------------
// _DEV INTERFACE
void SerialDriver::sayHi()
{
    SerialDriver::println("Hi from SerialDriver");
    SerialDriver::println(TAB, "boud_rate: ", SerialDriver::baud_rate);
}
