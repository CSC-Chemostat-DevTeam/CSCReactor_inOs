// Global libs
#include <Arduino.h>

// TODO: Stop using Arduino.hString class, use string or char[] (explore string.h, ctype.h)

// Local libs
#include "Base/0_Base.h"

void setup() {
    SerialDriver::onsetup();
    SerialCSVDriver::onsetup();
    PinDriver::onsetup();

    // // DEV
    // int LED1_PIN = 49;
    // int LED2_PIN = 37;
    // int LASER_PIN = 5;
    // pinMode(INPUT_PULLUP, LED1_PIN);
    // pinMode(INPUT_PULLUP, LED2_PIN);
    // pinMode(OUTPUT, LASER_PIN);

    // long n = 0;
    // while(1) {
    //     // 11392
    //     // n = PinDriver::_count_pulses2(LED1_PIN, 100);
    //     // SerialDriver::println("led1: ", n);

    //     // 10367
    //     // n = PinDriver::_count_pulses2(LED2_PIN, 100);
    //     // SerialDriver::println("led2: ", n);
    //     // delay(100);
    // }
    
}

void loop() {
    SerialDriver::onloop();
    SerialCSVDriver::onloop();
}

