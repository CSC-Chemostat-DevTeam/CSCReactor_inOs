#ifndef CHEMOSTAT_H
#define CHEMOSTAT_H

#include "1_config.h"

// foward declaration
class AbsHandler;
class MsgHandler;
class SerialHandler;
class SDHandler;
class LogHandler;
class LEDHandler;
class DOHandler;
class StirrelHandler;

// TODO: use 'cost' stuff whn required

class Chemostat {
    private: 
        AbsHandler* _ALL_HANDLERS_BUFFER[CHEMOSTAT_HANDLERS_BUFFER_SIZE];

    public:
        // ----------------------------------------------------
        // HANDLERS
        MsgHandler* pMSG;
        SerialHandler* pSERIAL;
        SDHandler* pSD;
        LogHandler* pLOG;
        LEDHandler* pBLED;
        DOHandler* pDO;
        StirrelHandler* pSTRR;

        // ----------------------------------------------------
        // CONSTRUCTOR
        Chemostat();

        // ----------------------------------------------------
        // SKETCH INTERFACE
        void onsetup();
            
        void onloop();

        // ----------------------------------------------------
        // _DEV INTERFACE
        String getClassName();
        void sayHi();

        // ----------------------------------------------------
        // MSG INTERFACE
        boolean handleMsg();

        // ----------------------------------------------------
        // TIME INTERFACE
        // Use a clock module if present, otherwise use millis or progress
        String nowTimeTag();

        // ----------------------------------------------------
        // BLOCKING INTERFACE
        void onBlokingInit();
        void onBlokingEnd();
        
        // ----------------------------------------------------
        // HANDLERS INTERFACE

        // MSG INTERFACE
        void handleAllMsgs();
        void handleBlokingInit(const String& msg);
        void handleBlokingEnd(const String& msg);

        // TODO: Add an handleBlokingInit/End where all handlers are called (by other handler) 
        // to act upon a blocking event

        void pushHandler(AbsHandler* h);
        
        // ----------------------------------------------------
        // OTHERS
        void printWelcome();
};


void _pushHandler(AbsHandler* buffer[], AbsHandler* h);

#endif // CHEMOSTAT_H