#ifndef STIRREL_HANDLER_H
#define STIRREL_HANDLER_H


#include <Arduino.h>

#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/4_Chemostat.h"
#include "Base/4_AbsHandler.h"
#include "Base/4_SerialHandler.h"

//  --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// Handler for logging info/error/dev information
//  --- --- --- --- --- --- --- --- --- --- --- --- --- ---

class StirrelHandler : 
    public AbsHandler
{
    private:
        int pwd1;
        int pwd2;

    public:
        // ----------------------------------------------------
        // CONSTRUCTOR
        StirrelHandler(Chemostat* Ch);

        // ----------------------------------------------------
        // SKETCH INTERFACE
        virtual void onsetup();
        virtual void onloop();

        // ----------------------------------------------------
        // _DEV INTERFACE
        String getClassName();
        void sayHi();

        // -------------------------
        // HANDLE MSG INTERFACE
        boolean handleMsg();

        // ----------------------------------------------------
        // LED INTERFACE
        void stirrelPulse(int d, int t);
        void stirrelOff();
        

};




#endif // STIRREL_HANDLER_H