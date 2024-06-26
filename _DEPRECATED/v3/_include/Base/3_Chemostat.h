#ifndef CHEMOSTAT_H
#define CHEMOSTAT_H

// foward declaration
class AbsHandler;
class CmdHandler;
class SerialHandler;

#define HANDLERS_BUFFER_SIZE 32

// TODO: make a sayHi system for tracking obj pointers
// To see why they change with time

// TODO: use 'cost' stuff whn required

class Chemostat {
    private: 
        AbsHandler* _CMD_HANDLERS_BUFFER[HANDLERS_BUFFER_SIZE];

    public:
        // ----------------------------------------------------
        // HANDLERS
        CmdHandler* pCMD;
        SerialHandler* pSERIAL;

        // ----------------------------------------------------
        // CONSTRUCTOR
        Chemostat();

        // ----------------------------------------------------
        // SKETCH INTERFACE
        void onsetup();
            
        void onloop();

        // ----------------------------------------------------
        // CMD INTERFACE
        boolean execCmd();
        
        // ----------------------------------------------------
        // ALL CALLERS

        // CMD INTERFACE
        void execAllCmd();
        void pushCmdHandler(AbsHandler* h);
};


#endif // CHEMOSTAT_H