#ifndef STATIC_POINTER_ARRAY_H
#define STATIC_POINTER_ARRAY_H

#include <Arduino.h>
#include "1_config.h"

// ----------------------------------------------------
// A resizable vector with max length
// The user is resonsable of tracking the type
// ----------------------------------------------------

class StaticPointerArray{
    private:
        int idx;
        void* buffer[STATIC_POINTER_ARRAY_BUFFER_LEN];

    public:
        // ----------------------------------------------------
        // CONSTRUCTOR
        StaticPointerArray();

        // ----------------------------------------------------
        // STATIC STRING INTERFACE
        void reset();

        
        boolean push(void* n);
        boolean push(const void* n);
        // TODO: push a vector
        // boolean push(String str);

        boolean isEmpty();

        boolean isFull();
        
        unsigned int length();

        //  getters
        void* getPointer(int i);
        unsigned int getUInt(int i);
        int getInt(int i);
        char getChar(int i);
};


#endif // STATIC_POINTER_ARRAY_H