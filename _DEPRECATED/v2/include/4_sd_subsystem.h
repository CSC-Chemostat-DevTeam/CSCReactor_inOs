#ifndef SD_SUBSYSTEM_H
#define SD_SUBSYSTEM_H

#include "Base/3_SubSystem.h"

#include <Arduino.h>
#include <SD.h>
#include "Base/3_Timer.h"
#include "Base/3_concurrent_task.h"

class SDSubsystem :
    public SubSystem
{       
	private:
		Timer loop_timer;
		ConcurrentTask ctask;

	public:
        String file; // File for read/write
        String line; // Text line for read/write

        // ----------------------------------------------------
        // CONSTRUCTOR
		
		SDSubsystem();

        // ----------------------------------------------------
        // SKETCH INTERFACE
        
		void onsetup();
		
		void onloop();

		void onloop_dev();

        // ----------------------------------------------------
        // CMD INTERFACE
		boolean execCmd(String& key, String& val);

        // ----------------------------------------------------
        // SD INTERFACE

        // ----------------------------------------------------
        // BLOCKING INTERFACE
        void beforeBlock();

        void afterBlock();

        // ----------------------------------------------------
        // STOP INTERFACE
        void onStop();

        // ----------------------------------------------------
        // ERROR INTERFACE
        void onError(byte errcode);

};


// ----------------------------------------------------
// STATIC
String _sd_readLineFile(String file, String onerr);

boolean _sd_writeLineFile(String file, String line);

boolean _sd_writeNewLine(String file, String line);

boolean _sd_exists(String& file);

void _sd_remove(String& file);

void _sd_mkdir(String& file);



#endif // SD_SUBSYSTEM_H