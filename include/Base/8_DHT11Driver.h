#ifndef DHT11_DRIVER_H
#define DHT11_DRIVER_H

#include "Base/2_Utils.h"
#include <DHT.h>
#include <DHT_U.h>

// ----------------------------------------------------
// All parseble msgs between the PC and the board must be
// handle by this class
// ----------------------------------------------------

namespace DHT11Driver
{
    // MARK: DHT11 object
    extern DHT dht;
    extern uint8_t curr_pin;

    // ----------------------------------------------------
    void begin(uint8_t pin);
    float getTemperature();
    float getHumidity();

    // ----------------------------------------------------
    // MARK: SKETCH INTERFACE
    void onsetup();
    void onloop();

    // -------------------------
    // MARK: HANDLE MSG INTERFACE
    boolean handleMsg();

    // ----------------------------------------------------
    // MARK: _DEV INTERFACE
    void sayHi();

    // ----------------------------------------------------
    // MARK: UTILS

}

#endif // DHT11_DRIVER_H