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
    // DHT11 object
    extern DHT dht;
    extern uint8_t curr_pin;

    // ----------------------------------------------------
    void begin(uint8_t pin);
    float getTemperature();
    float getHumidity();

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
    

}

#endif // DHT11_DRIVER_H