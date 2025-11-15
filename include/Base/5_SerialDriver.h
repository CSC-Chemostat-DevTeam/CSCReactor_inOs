#ifndef SERIAL_DRIVER_H
#define SERIAL_DRIVER_H

#include <Arduino.h>
#include "Base/1_config.h"
#include "Base/2_Utils.h"

// ----------------------------------------------------
// All Chemostat serial printing must use this Handler
// ----------------------------------------------------

namespace SerialDriver
{
    // byte vlevel;
    extern unsigned long baud_rate;

    // ----------------------------------------------------
    // MARK: SKETCH INTERFACE
    void onsetup();
    void onloop();

    // ----------------------------------------------------
    // MARK: SERIAL INTERFACE
    // void setBaudRate(unsigned long brate);
    unsigned long getBaudRate();
    void initConnection(unsigned long baud_rate);

    template <typename T0, typename... Ts>
    inline void print(T0 arg0, Ts... args)
    {
        Utils::_print(arg0, args...);
    }

    template <typename T0, typename... Ts>
    inline void println(T0 arg0, Ts... args)
    {
        Utils::_println(arg0, args...);
    }
    void newLine();

    int available();
    int read();
    void flush();

    // -------------------------
    // MARK: HANDLE MSG INTERFACE
    boolean handleMsg();

    // ----------------------------------------------------
    // MARK: _DEV INTERFACE
    void sayHi();

};

#endif // SERIAL_DRIVER_H