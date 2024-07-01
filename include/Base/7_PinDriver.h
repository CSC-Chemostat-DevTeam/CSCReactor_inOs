#ifndef ARDUINO_DRIVER_H
#define ARDUINO_DRIVER_H

#include "Base/2_Utils.h"
#include "Base/3_CSVLineReader.h"
#include "Base/5_SerialDriver.h"

// ----------------------------------------------------
// All parseble msgs between the PC and the board must be 
// handle by this class
// ----------------------------------------------------

namespace PinDriver
{

    // ----------------------------------------------------
    // SKETCH INTERFACE
    void onsetup();
    void onloop();

    // -------------------------
    // HANDLE MSG INTERFACE
    boolean handleMsg();

    // ----------------------------------------------------
    // _DEV INTERFACE
    void sayHi();

    // ----------------------------------------------------
    // Utils
    unsigned long _count_pulses2(int pin, unsigned long sampling_time);
    unsigned long _count_pulses3(int pin, unsigned long sampling_time);
    void _serial_pin_mode(int type);
    void _serial_write(int type);
    void _serial_read(int type);
    void _serial_pulse_out(int type);
    void _concurrent_pulse_out(int type);
    void _concurrent_pulse_in();
    int _read(int type, unsigned int pin);
    void _write(int type, unsigned int pin, int val);
    void _pin_mode(int type, int pin, int mode);

}

#endif // ARDUINO_DRIVER_H