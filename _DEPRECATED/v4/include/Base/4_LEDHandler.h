#ifndef LED_HANDLER_H
#define LED_HANDLER_H

#include <Arduino.h>

#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/4_Chemostat.h"
#include "Base/4_AbsHandler.h"
#include "Base/4_SerialHandler.h"

//  --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// Handler for logging info/error/dev information
//  --- --- --- --- --- --- --- --- --- --- --- --- --- ---

class LEDHandler : 
    public AbsHandler
{
    private:
        byte pin;

    public:
        // ----------------------------------------------------
        // CONSTRUCTOR
        LEDHandler(Chemostat* Ch, byte pin);

        // ----------------------------------------------------
        // SKETCH INTERFACE
        virtual void onsetup();
        virtual void onloop();

        // ----------------------------------------------------
        // _DEV INTERFACE
        String getClassName();
        void sayHi();

        // -------------------------
        // HANDLE MSG INTERFACE
        boolean handleMsg();

        // ----------------------------------------------------
        // LED INTERFACE
        void ledOn();
        void ledOff();
        void setState(int state);
        int getState();
        void flip();
        

};

#endif // LED_HANDLER_H