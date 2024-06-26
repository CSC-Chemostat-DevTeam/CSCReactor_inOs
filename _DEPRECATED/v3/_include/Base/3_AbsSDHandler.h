#ifndef ABS_SD_H
#define ABS_SD_H

#include <Arduino.h>
#include <SD.h>

#include "1_config.h"
#include "3_Timer.h"
#include "3_AbsHandler.h"
#include "3_ConcurrentTask.h"
#include "3_AbsSDHandler.h"
#include "3_Chemostat.h"

// An abstract SD
class AbsSDHandler :
    public AbsHandler
{
    private:

    public:

        // ----------------------------------------------------
        // CONSTRUCTOR
        AbsSDHandler(Chemostat* Ch) : AbsHandler(Ch) { ; }

        // ----------------------------------------------------
        // BASIC SD INTERFACE (JULIA LIKE)
        virtual boolean isFile(String file);
        virtual boolean isDir(String file);
        
        virtual boolean mkDir(String file);
        virtual boolean rm(String file);

        // [Blocking]
        // Read a file and print it
        virtual boolean readToSerial(String file);
        
        // Read the first line of a file and returns it
        // It returns an empty string if the file is not present
        virtual String readFirstLine(String file);
        
        // Overwrite the first line of a file
        virtual boolean overwriteFirstLine(String file, String line);

        // Add a new line to a file
        virtual boolean appendNewLine(String file, String line);

        // ----------------------------------------------------
        // CMD INTERFACE
		virtual boolean execCmd();


};


#endif // ABS_SD_H