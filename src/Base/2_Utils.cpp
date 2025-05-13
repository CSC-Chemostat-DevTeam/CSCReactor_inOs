#include <Arduino.h>

#include "Base/1_config.h"
#include "Base/2_Utils.h"

//  --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// Hashing
// from: https://forum.arduino.cc/t/simple-checksum-that-a-noob-can-use/300443/3
// TOSYNC with PC implementations
// MARK: crc16_hash
unsigned int Utils::crc16_hash(unsigned int crc, unsigned int c){
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

// For debb
// MARK: crc16_hash
unsigned int Utils::crc16_hash(unsigned int crc, String str){
    for (unsigned int i = 0; i < str.length(); i++) {
        crc = Utils::crc16_hash(crc, (unsigned int)str.charAt(i));
    }
    return crc;
}
