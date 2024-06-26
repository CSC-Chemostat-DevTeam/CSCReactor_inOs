#ifndef STATIC_STRING_H
#define STATIC_STRING_H

#include <Arduino.h>
#include "1_config.h"

// ----------------------------------------------------
// An string of known fix length
// ----------------------------------------------------

class StaticString{
    private:
        int idx;
        char buffer[STATIC_STRING_BUFFER_LEN];

    public:
        // ----------------------------------------------------
        // CONSTRUCTOR
        StaticString();
        StaticString(String& str);

        // ----------------------------------------------------
        // STATIC STRING INTERFACE
        void reset();

        String toString();
        char* c_string();
        
        boolean push(char c);
        boolean push(String str);

        boolean isEmpty();

        boolean isFull();

        // ----------------------------------------------------
        // HASH INTERFACE
        unsigned int hash(unsigned int crc);
        unsigned int hash();
};


#endif // STATIC_STRING_H