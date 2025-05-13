#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

//  --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// Some util functions
//  --- --- --- --- --- --- --- --- --- --- --- --- --- ---

namespace Utils
{
    // -------------------------
    // HANDLE MSG INTERFACE
    boolean handleMsg();

    // -------------------------
    // print
    // Just allow to pass multiple arguments in a single call to Serial.print
    template <typename Arg>
    void _print(Arg arg) {
        Serial.print(arg);
    }
    // variadic template with one or more arguments.
    template <typename First, typename... Args>
    void _print(First first, Args... args) {
        Serial.print(first); 
        _print(args...);
    }

    // println
    template <typename Arg>
    void _println(Arg arg) {
        _print(arg);
        Serial.println();
    }
    // variadic template with one or more arguments.
    template <typename First, typename... Args>
    void _println(First first, Args... args) {
        _print(first); 
        _println(args...);
    }

    //  --- --- --- --- --- --- --- --- --- --- --- --- --- ---
    // Hashing
    unsigned int crc16_hash(unsigned int crc, unsigned int c);
    unsigned int crc16_hash(unsigned int crc, String str);
};

#endif // UTILS_H
