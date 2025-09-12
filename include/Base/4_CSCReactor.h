#ifndef CSCREACTOR_H
#define CSCREACTOR_H

#include "Base/2_Utils.h"

// ----------------------------------------------------
// A set of properties
// ---------------------------------------------------

namespace CSCReactor
{

    // ----------------------------------------------------
    // STATE VARIABLES

    // the current running mode
    // - services can modify its behaviour
    // based on the mode
    extern bool devmode;

    // ----------------------------------------------------
    // SKETCH INTERFACE
    void onsetup();
    void onloop();

    // -------------------------
    // HANDLE MSG INTERFACE
    boolean handleMsg();

    // ----------------------------------------------------
    // _DEV INTERFACE
    void sayHi();

}

#endif // CSCREACTOR_H
