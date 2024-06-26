// Global libs
#include <Arduino.h>

// TODO: Stop using Arduino.hString class, use string or char[] (explore string.h, ctype.h)

// Local libs
#include "Base/0_Base.h"

void setup() {
    SerialDriver::onsetup();
    SerialCSVDriver::onsetup();

    // // DEV
    // Collection c = Collection();
    // c.push('B');
    // Serial.println(c.toString());
    // c.push('B');
    // Serial.println(c.toString());
    // c.push('B');
    // Serial.println(c.toString());
    // c.push("BLABLA");
    // Serial.println(c.toString());
    // Serial.println(c.toString());
    // while(1);
}

void loop() {
    SerialDriver::onloop();
    SerialCSVDriver::onloop();

    // DEV
    // long n = _count_pulses2(37, 100);
    // Serial.println(n);
}

