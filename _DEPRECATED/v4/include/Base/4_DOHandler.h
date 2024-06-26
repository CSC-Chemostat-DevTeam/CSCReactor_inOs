#ifndef DOHANDLER_H
#define DOHANDLER_H


#include <Arduino.h>

#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/4_Chemostat.h"
#include "Base/4_AbsHandler.h"
#include "Base/4_SerialHandler.h"

//  --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// Handler for logging info/error/dev information
//  --- --- --- --- --- --- --- --- --- --- --- --- --- ---

class DOHandler : 
    public AbsHandler
{
    private:
        // TODO: Add controls (laser_pwd, led_waiting_time, etc...)
        int laser_pwd;
        long led1_val;
        long led2_val;

    public:
        // ----------------------------------------------------
        // CONSTRUCTOR
        DOHandler(Chemostat* Ch);

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
        // DO INTERFACE
        void laserOn();
        void laserOff();
        void measureDO();

};


// ----------------------------------------------------
// DO UTILS
// BLOCKING
long _count_pulses(int pin, unsigned long sampling_time);

#endif // DOHANDLER_H
