#ifndef DO_SUBSYSTEM_H
#define DO_SUBSYSTEM_H

#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/3_Timer.h"
#include "Base/3_SubSystem.h"
#include "4_datalogger_subsystem.h"

class DOSubsystem :
    public SubSystem
{       
    private: 
        
	public:
		Timer timer;
        byte laser_pwd;
        unsigned long led1_count;
        unsigned long led2_count;
        unsigned long samp_time;

        // ----------------------------------------------------
        // CONSTRUCTOR
        
        DOSubsystem();

        // ----------------------------------------------------
        // SKETCH INTERFACE
        void onsetup();
        
        void onloop();

        // ----------------------------------------------------
        // CMD INTERFACE
		boolean execCmd(String& key, String& val);

        // ----------------------------------------------------
        // STIRREL INTERFACE

        // ----------------------------------------------------
        // BLOCKING INTERFACE
        void beforeBlock();

        void afterBlock();

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





#endif // DO_SUBSYSTEM_H