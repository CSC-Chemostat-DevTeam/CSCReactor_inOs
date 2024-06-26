#ifndef PROGRAM_SUBSYSTEM_H
#define PROGRAM_SUBSYSTEM_H

#include <Arduino.h>
#include <SD.h>

#include "Base/3_Timer.h"
#include "Base/3_SubSystem.h"
#include "4_datalogger_subsystem.h"

#define PROGRAMMER_UP_TIME 3000

// TODO: add Error handling, stop if error

// A class to handle the SD program files and updating the board ram accordintly
class ProgramSubsystem :
    public SubSystem
{       
    private:
        
        long progress; // a persistant program counter (to be sync with disk)
        long progress_t0; // helper (millis)
        String chapterid; // a persistant program id (to be sync from disk)
        String jumpto;
        Timer up_timer;
        long jumpat;

    public:

        // ----------------------------------------------------
        // CONSTRUCTOR    
        ProgramSubsystem();

        // ----------------------------------------------------
        // SKETCH INTERFACE
        
		void onsetup();
		
		void onloop();

        // ----------------------------------------------------
        // PROGRAM INTERFACE
        void onProgramUpdate(String chapterid);

        // returns the prog File handler
        File progFile(String suffix);

        void resolveChapter();

        String getChapter();
        long getProgress();
        String getJumpTo();
        long getJumpAt();

        // ----------------------------------------------------
        // CMD INTERFACE
        boolean execCmd(String& key, String& val);

        // ----------------------------------------------------
        // LOGGER INTERFACE
        // Concurrent
        void onLogWrite(DataLoggerSubsystem& logger);

        // ----------------------------------------------------
        // STOP INTERFACE
        void onStop();

};




#endif // PROGRAM_SUBSYSTEM_H