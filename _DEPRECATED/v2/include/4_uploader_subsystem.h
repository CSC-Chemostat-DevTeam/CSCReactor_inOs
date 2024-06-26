#ifndef UPLOADER_SUBSYSTEM_H 
#define UPLOADER_SUBSYSTEM_H 

#include <Arduino.h>
#include <SD.h>
#include "Base/1_config.h"
#include "Base/3_SubSystem.h"
#include "Base/3_concurrent_task.h"
#include "Base/3_concurrent_task.h"

// A SUBSYSTEM FOR TRANFERING DATA TO THE PC
class UploaderSubsystem :
    public SubSystem
{       
    private:
        // uploader
        String file;
        boolean busy; // Move to ConcurrentTask
        ConcurrentTask ctask;

    public:
        // ----------------------------------------------------
        // CONSTRUCTOR
        UploaderSubsystem();

        // ----------------------------------------------------
        // SKETCH INTERFACE
        void onsetup();
        
        void onloop();

        // ----------------------------------------------------
        // CMD INTERFACE
        boolean execCmd(String& key, String& val);

        // ----------------------------------------------------
        // UPLOADER INTERFACE
        void upload();

        boolean isBusy();

        // ----------------------------------------------------
        // STOP INTERFACE
        void onStop();

};


#endif // UPLOADER_SUBSYSTEM_H