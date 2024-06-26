#ifndef T_CONTROL_SUBSYSTEMS_H
#define T_CONTROL_SUBSYSTEMS_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "Base/3_Timer.h"
#include "Base/3_SubSystem.h"
#include "Base/3_SubSystem.h"
#include "4_datalogger_subsystem.h"

// A class to handle the temperature control
class TControlSubsystem :
    public SubSystem
{       
    private:
        OneWire _one_wire;
        DallasTemperature _T_sensor;
        Timer sensor_timer;
        Timer heater_timer;
        float temp;

    public:

        // ----------------------------------------------------
        // CONSTRUCTOR
        TControlSubsystem();

        // ----------------------------------------------------
        // SKETCH INTERFACE
        void onsetup();
        
        void onloop();

        // ----------------------------------------------------------------------------
        // T SENSOR API
        void measureTemp();

        float getTemp();

        // ----------------------------------------------------
        // CMD INTERFACE

        boolean execCmd(String& key, String& val);

        // ----------------------------------------------------
        // BOTTOM INTERFACE
        void onBottomPressed();

        // ----------------------------------------------------
        // LOGGER INTERFACE
        void onLogWrite(DataLoggerSubsystem& logger);

        // ----------------------------------------------------
        // STOP INTERFACE
        void onStop();

};





#endif // T_CONTROL_SUBSYSTEMS_H