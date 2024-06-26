#ifndef STATIC_INT_ARRAY
#define STATIC_INT_ARRAY

#include <Arduino.h>
#include "1_config.h"

// ----------------------------------------------------
// An string of known fix length
// ----------------------------------------------------

class StaticUIntArray{
    private:
        int idx;
        unsigned int buffer[STATIC_UINT_ARRAY_BUFFER_LEN];

    public:
        // ----------------------------------------------------
        // CONSTRUCTOR
        StaticUIntArray();
        // TODO: build from vector
        // StaticUIntArray(String& str);

        // ----------------------------------------------------
        // STATIC STRING INTERFACE
        void reset();

        
        boolean push(unsigned int n);
        // TODO: push a vector
        // boolean push(String str);

        boolean isEmpty();

        boolean isFull();
        
        unsigned int  length();

        // ----------------------------------------------------
        // HASH INTERFACE
        unsigned int hash(unsigned int crc);
        unsigned int hash();
};


#endif // STATIC_INT_ARRAY