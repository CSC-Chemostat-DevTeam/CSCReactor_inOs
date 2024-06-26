#ifndef VIRTUAL_SD_HANDLER
#define VIRTUAL_SD_HANDLER

#include "1_config.h"
#include "2_utils.h"
#include "3_Chemostat.h"
#include "3_AbsSDHandler.h"


// An Virtual SD, it is based on PC comunications... The files will be on the PC
class VirtualSDHandler :
    public AbsSDHandler
{
    private:

    public:
        // ----------------------------------------------------
        // CONSTRUCTOR
        VirtualSDHandler(Chemostat* Ch);

        // ----------------------------------------------------
        // BASIC SD INTERFACE (JULIA LIKE)
        boolean isFile(String file);
        boolean isDir(String file);
        
        boolean mkDir(String file);
        boolean rm(String file);

        // [Blocking]
        // Read a file and print it
        boolean readToSerial(String file);
        
        // Read the first line of a file and returns it
        // It returns an empty string if the file is not present
        String readFirstLine(String file);
        
        // Overwrite the first line of a file
        boolean overwriteFirstLine(String file, String line);

        // Add a new line to a file
        boolean appendNewLine(String file, String line);

        // ----------------------------------------------------
        // CMD INTERFACE
		boolean execCmd();

};



#endif // VIRTUAL_SD_HANDLER