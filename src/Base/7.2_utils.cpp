#include "Base/1_config.h"
#include "Base/2_Utils.h"
#include "Base/3_CSVLineReader.h"
#include "Base/5_SerialDriver.h"
#include "Base/6_SerialCSVDriver.h"
#include "Base/7_ArduinoDriver.h"

// config
unsigned long PULSEIN_TIMEOUT = 500; // micro seconds

// TODO: Make a muli pin reading method
// By measuring the HIGH/LOW average time we should be able to get the frequency

unsigned long ArduinoDriver::_count_pulses2(int pin, unsigned long sampling_time) {

    // reset
    unsigned long n = 0;
    unsigned long time0 = millis();

    while (true) {

        // wait till a HIGH pulse happends and ends
        pulseIn(pin, HIGH, PULSEIN_TIMEOUT);
        n++;

        // Time out
        if (millis() - time0 > sampling_time) { break; }
    }

    return n;
}

