#ifndef STATIC_STRING_H
#define STATIC_STRING_H

#include <Arduino.h>

const byte BUFFERED_STRING_BUFFER_LEN = 128;

class StaticString{
    private:
        int idx;
        char* buffer;

    public:
        // ----------------------------------------------------
        // CONSTRUCTOR
        StaticString();
        StaticString(String& str);

        // ----------------------------------------------------
        // BUFFERED STRING INTERFACE
        void reset();

        String toString();
        char* c_string();
        
        boolean push(char c);
        boolean push(String str);

        boolean isEmpty();

        boolean isFull();

        unsigned int hash(unsigned int crc);
        unsigned int hash();
};


#endif // STATIC_STRING_H