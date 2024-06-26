#ifndef STIRREL_SUBSYSTEM_H
#define STIRREL_SUBSYSTEM_H

#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/3_Timer.h"
#include "Base/3_SubSystem.h"
#include "Base/3_SubSystem.h"

class StirrelSubsystem :
    public SubSystem
{       
	public:
		Timer timer;
        long pulse_high_time;
        long pulse_low_time;
        byte state;

        // ----------------------------------------------------
        // CONSTRUCTOR
        
        StirrelSubsystem();

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
        // STOP INTERFACE
        void onStop();
};





#endif // STIRREL_SUBSYSTEM_H