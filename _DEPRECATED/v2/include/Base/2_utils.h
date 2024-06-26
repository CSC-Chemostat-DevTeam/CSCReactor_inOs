#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

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



// Hashing
unsigned int crc16_hash(unsigned int crc, char c);


#endif // UTILS_H