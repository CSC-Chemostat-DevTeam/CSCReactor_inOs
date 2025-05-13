#include "Base/1_config.h"
#include "Base/2_Utils.h"
#include "Base/3_CSVLineReader.h"
#include "Base/5_SerialDriver.h"
#include "Base/7_PinDriver.h"

// ----------------------------------------------------
// _DEV INTERFACE
void PinDriver::sayHi() { 
    SerialDriver::println("Hi from PinDriver");
}

// ----------------------------------------------------
// SKETCH INTERFACE
void PinDriver::onsetup(){
    PinDriver::sayHi();
    // Set all pins to INPUT_PULLUP
    for (unsigned int pin = 3; pin < NUM_DIGITAL_PINS; pin++) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    };
}
void PinDriver::onloop(){
    ;
}