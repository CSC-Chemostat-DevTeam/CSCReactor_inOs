#include <Arduino.h>

#include "Base/1_config.h"
#include "Base/2_Utils.h"

//  --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// Hashing
// from: https://forum.arduino.cc/t/simple-checksum-that-a-noob-can-use/300443/3
// TOSYNC with PC implementations
// MARK: crc16_hash
unsigned int Utils::crc16_hash(unsigned int c, unsigned int crc)
{
    int i;
    crc ^= c;
    for (i = 0; i < 8; ++i)
    {
        if (crc & 1)
        {
            crc = (crc >> 1) ^ 0xA001;
        }
        else
        {
            crc = (crc >> 1);
        }
    }
    return crc;
}

// For debb
// MARK: crc16_hash
unsigned int Utils::crc16_hash(String str, unsigned int crc)
{
    for (unsigned int i = 0; i < str.length(); i++)
    {
        crc = Utils::crc16_hash((unsigned int)str.charAt(i), crc);
    }
    return crc;
}

/// -------------------------
// For deving
unsigned int _traced_crc16_hash2(char c, unsigned int crc)
{
    Utils::_println("[] ", "c=", c, ", crc=", crc);
    crc ^= c;
    Utils::_println("[crc ^= c] ", "crc=", crc);
    for (int i = 0; i < 8; ++i)
    {
        if (crc & 1)
        {
            crc = (crc >> 1) ^ 0xA001;
            Utils::_println("[(crc >> 1) ^ 0xA001] ", "crc=", crc);
        }
        else
        {
            crc = (crc >> 1);
            Utils::_println("[crc = (crc >> 1)] ", "crc=", crc);
        }
    }
    Utils::_println("[] ", "crc=", crc);
    return crc;
}
