#include "Base/1_config.h"
#include "Base/2_Utils.h"
#include "Base/3_CSVLineReader.h"
#include "Base/5_SerialDriver.h"
#include "Base/7_InoDriver.h"

// ----------------------------------------------------
// MARK: _DEV INTERFACE
void InoDriver::sayHi()
{
    SerialDriver::println("Hi from InoDriver");
}

// ----------------------------------------------------
// MARK: SKETCH INTERFACE
void InoDriver::onsetup()
{
    InoDriver::sayHi();
    // Set all pins to INPUT_PULLUP
    for (unsigned int pin = 3; pin < NUM_DIGITAL_PINS; pin++)
    {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    };
}
void InoDriver::onloop()
{
    ;
}