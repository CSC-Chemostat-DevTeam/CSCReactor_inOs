// Global libs
#include <Arduino.h>

// TODO: Stop using Arduino.hString class, use string or char[] (explore string.h, ctype.h)

// Local libs
#include "Base/0_Base.h"

void setup() {
    SerialDriver::onsetup();
    SerialCSVDriver::onsetup();

    // DEV
    // pinMode(37, INPUT_PULLUP);
    // A1
}

void loop() {
    SerialDriver::onloop();
    SerialCSVDriver::onloop();

    // DEV
    // long n = _count_pulses2(37, 100);
    // Serial.println(n);
}

