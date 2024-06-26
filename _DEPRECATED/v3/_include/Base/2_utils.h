#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

//  --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// TODO: Use templates
void _show_name(const char name[]);
void show(const char name[], const String &val);
void show(const char name[], const char val[]);
void show(const char name[], char val);
void show(const char name[], char val, int base);
void show(const char name[], unsigned char val);
void show(const char name[], unsigned char val, int base);
void show(const char name[], int val);
void show(const char name[], int val, int base);
void show(const char name[], unsigned int val);
void show(const char name[], unsigned int val, int base);
void show(const char name[], long val);
void show(const char name[], long val, int base);
void show(const char name[], unsigned long val);
void show(const char name[], unsigned long val, int base);
void show(const char name[], double val);
void show(const char name[], double val, int digits);
void show(const char name[], const Printable& val);

//  --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// Hashing
unsigned int crc16_hash(unsigned int crc, char c);
unsigned int crc16_hash(unsigned int crc, String str);

//  --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// My printing

// print
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

#endif // UTILS_H