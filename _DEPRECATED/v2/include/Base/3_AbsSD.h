#ifndef ABSSD_H
#define ABSSD_H

#include <Arduino.h>

#include "1_config.h"
#include "3_AbsSD.h"

// An abstract SD
class AbsSD {

    public:
        // ----------------------------------------------------
        // SKETCH INTERFACE
        void onsetup();
            
        void onloop();


};


#endif // ABSSD_H