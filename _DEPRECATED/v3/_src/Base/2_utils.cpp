#include <Arduino.h>

#include "Base/1_config.h"
#include "Base/2_utils.h"

//  --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// SHOW
void _show_name(const char name[]){
    Serial.print(name);
    Serial.print(" = ");
}

void show(const char name[], const String &val) {
    _show_name(name);
    Serial.println(val);
}

void show(const char name[], const char val[]) {
    _show_name(name);
    Serial.println(val);
}

void show(const char name[], char val) {
    _show_name(name);
    Serial.println(val);
}
void show(const char name[], char val, int base) {
    _show_name(name);
    Serial.println(val, base);
}

void show(const char name[], unsigned char val) {
    _show_name(name);
    Serial.println(val);
}
void show(const char name[], unsigned char val, int base) {
    _show_name(name);
    Serial.println(val, base);
}

void show(const char name[], int val) {
    _show_name(name);
    Serial.println(val);
}
void show(const char name[], int val, int base) {
    _show_name(name);
    Serial.println(val, base);
}

void show(const char name[], unsigned int val) {
    _show_name(name);
    Serial.println(val);
}
void show(const char name[], unsigned int val, int base) {
    _show_name(name);
    Serial.println(val, base);
}

void show(const char name[], long val) {
    _show_name(name);
    Serial.println(val);
}
void show(const char name[], long val, int base) {
    _show_name(name);
    Serial.println(val, base);
}

void show(const char name[], unsigned long val) {
    _show_name(name);
    Serial.println(val);
}
void show(const char name[], unsigned long val, int base) {
    _show_name(name);
    Serial.println(val, base);
}

void show(const char name[], double val) {
    _show_name(name);
    Serial.println(val);
}
void show(const char name[], double val, int digits) {
    _show_name(name);
    Serial.println(val, digits);
}

void show(const char name[], const Printable& val) {
    _show_name(name);
    Serial.println(val);
}


//  --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// Hashing
// from: https://forum.arduino.cc/t/simple-checksum-that-a-noob-can-use/300443/3
// TOSYNC
unsigned int crc16_hash(unsigned int crc, char c){
  int i;
  crc ^= c;
  for (i = 0; i < 8; ++i)
  {
    if (crc & 1) {
        crc = (crc >> 1) ^ 0xA001;
    } else {
        crc = (crc >> 1);
    }
  }
  return crc;
}

unsigned int crc16_hash(unsigned int crc, String str){
    for (unsigned int i = 0; i < str.length(); i++) {
        crc = crc16_hash(crc, str.charAt(i));
    }
    return crc;
}

// ----------------------------------------------------
// Returns "" if prefix does not match
String _parseSuffix(String& key, const String& prefix){
    if (!key.startsWith(prefix)) { return ""; }
    return key.substring(prefix.length());
}
