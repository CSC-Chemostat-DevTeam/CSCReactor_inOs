#ifndef ARDUINO_DRIVER_H
#define ARDUINO_DRIVER_H

#include "Base/2_Utils.h"
#include "Base/3_CSVLineReader.h"
#include "Base/5_SerialDriver.h"

// ----------------------------------------------------
// All parseble msgs between the PC and the board must be 
// handle by this class
// ----------------------------------------------------

namespace ArduinoDriver
{
    // -------------------------
    // HANDLE MSG INTERFACE
    boolean handleMsg();

    // ----------------------------------------------------
    // _DEV INTERFACE
    void sayHi();

    // ----------------------------------------------------
    // Utils
    unsigned long _count_pulses2(int pin, unsigned long sampling_time);
}

#endif // ARDUINO_DRIVER_H