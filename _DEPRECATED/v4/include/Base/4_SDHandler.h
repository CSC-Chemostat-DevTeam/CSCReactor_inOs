// #ifndef SD_HANDLER_H
// #define SD_HANDLER_H

// #include <Arduino.h>
// #include <SD.h>

// #include "Base/1_config.h"
// #include "Base/2_utils.h"
// #include "Base/3_StaticString.h"
// #include "Base/4_AbsHandler.h"
// #include "Base/4_Chemostat.h"

// // ----------------------------------------------------
// // ALL SD actions must happend using this class
// // TODO: Make a 'virtual' SD?
// // ----------------------------------------------------

// class SDHandler : 
//     public AbsHandler
// {
//     private:
//         StaticString _LINE_BUFFER;

//     public:
//         // ----------------------------------------------------
//         // CONSTRUCTOR
//         SDHandler(Chemostat* Ch);

//         // ----------------------------------------------------
//         // SKETCH INTERFACE
//         void onsetup();
//         void onloop();

//         // ----------------------------------------------------
//         // _DEV INTERFACE
//         String getClassName();
//         void sayHi();

//         // -------------------------
//         // HANDLE MSG INTERFACE
//         boolean handleMsg();

//         // -------------------------
//         // SD INTERFACE

//         /// ONE LINE FILE INTERFACE
//         // - read a one line file
//         String readLineFile(String file, String onerr);
//         // - write/overwrite a one line file
//         boolean writeLineFile(String file, String line);
//         String getLineString(); // get last one line file read
        
//         /// MULTI LINE FILE INTERFACE
//         // - append a line to a file
//         // - read a line from a multiline file

//         /// FILE/DIR INTERFACE
//         //  - create file/dir
//         void mkdir(String file);
//         // - check isFile/isDir/isPath
//         boolean exists(String file);
//         // - delete path
//         void remove(String file);
//         // - copy file/dir
//         // - file hash?

//         /// HARDWARE TEST INTERFACE
//         // - check read & write file
//         boolean checkReadWrite();

// };



// #endif // SD_HANDLER_H