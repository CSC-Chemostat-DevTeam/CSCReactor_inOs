#include "Base/1_config.h"
#include "Base/2_Utils.h"
#include "Base/3_CSVLineReader.h"
#include "Base/5_SerialDriver.h"
#include "Base/6_SerialCSVDriver.h"
#include "Base/7_PinDriver.h"

/// -------------------------
/// HANDLE MSG INTERFACE
boolean PinDriver::handleMsg() { 
    
    // Check target code
    if (!SerialCSVDriver::hasValString(0, "INO")) { return false; }

    // TEST MSGS
    // Example: $INO:SAY-HI%
    if (SerialCSVDriver::hasValString(1, "SAY-HI")) {
        PinDriver::sayHi(); 
        return true;
    }
    
    //// ------------
    // PIN-MODE
    
    // PIN-MODE
    // $INO:PIN-MODE:PIN1:MODE1:...%
    if (SerialCSVDriver::hasValString(1, "PIN-MODE")) {
        _serial_pin_mode(NONDRY_OP_TYPE);
        return true;
    }
    // DRY-PIN-MODE
    // $INO:DRY-PIN-MODE:PIN1:MODE1:...%
    if (SerialCSVDriver::hasValString(1, "DRY-PIN-MODE")) {
        _serial_pin_mode(DRY_OP_TYPE);
        return true;
    }

    //// ------------
    // WRITE

    // DIGITAL-WRITE
    // $INO:DIGITAL-WRITE:PIN1:VAL1:...%
    if (SerialCSVDriver::hasValString(1, "DIGITAL-WRITE")) {
        _serial_write(DIGITAL_OP_TYPE);
        return true;
    }

    // ANALOG-WRITE
    // $INO:ANALOG-WRITE:PIN1:VAL1:...%
    if (SerialCSVDriver::hasValString(1, "ANALOG-WRITE")) {
        _serial_write(ANALOG_OP_TYPE);
        return true;
    }

    // DRY-WRITE
    // $INO:DRY-WRITE:PIN1:VAL1:...%
    if (SerialCSVDriver::hasValString(1, "DRY-WRITE")) {
        _serial_write(DRY_OP_TYPE);
        return true;
    }
    
    //// ------------
    // READ
    
    // DIGITAL-READ
    // $INO:DIGITAL-READ:PIN1:...%
    if (SerialCSVDriver::hasValString(1, "DIGITAL-READ")) {
        _serial_read(DIGITAL_OP_TYPE);
        return true;
    }
    
    // ANALOG-READ
    // $INO:ANALOG-READ:PIN1:...%
    if (SerialCSVDriver::hasValString(1, "ANALOG-READ")) {
        _serial_read(ANALOG_OP_TYPE);
        return true;
    }

    // DRY-READ
    // $INO:DRY-READ:PIN1:...%
    if (SerialCSVDriver::hasValString(1, "DRY-READ")) {
        _serial_read(DRY_OP_TYPE);
        return true;
    }

    //// ------------
    // S-PULSE

    // DIGITAL-S-PULSE
    // $INO:DIGITAL-S-PULSE:PIN1:VAL01:TIME1:VAL11...%
    // precise/fast pulse
    if (SerialCSVDriver::hasValString(1, "DIGITAL-S-PULSE")) {
        _serial_pulse_out(DIGITAL_OP_TYPE);
        return true;
    }

    // ANALOG-S-PULSE
    // $INO:ANALOG-S-PULSE:PIN1:VAL01:TIME1:VAL11...%
    // precise/fast pulse
    if (SerialCSVDriver::hasValString(1, "ANALOG-S-PULSE")) {
        _serial_pulse_out(ANALOG_OP_TYPE);
        return true;
    }

    // DRY-S-PULSE
    // $INO:DRY-S-PULSE:PIN:VAL0:TIME:[VAL1]%
    // precise/fast pulse
    if (SerialCSVDriver::hasValString(1, "DRY-S-PULSE")) {
        _serial_pulse_out(DRY_OP_TYPE);
        return true;
    }

    //// ------------
    // C-PULSE

    // DIGITAL-C-PULSE
    // $INO:DIGITAL-C-PULSE:PIN1:VAL10:TIME1:VAL11:...%
    // Concurrent
    if (SerialCSVDriver::hasValString(1, "DIGITAL-C-PULSE")) {
        _concurrent_pulse_out(DIGITAL_OP_TYPE);
        return true;
    }

    // ANALOG-C-PULSE
    // $INO:ANALOG-C-PULSE:PIN1:VAL10:TIME1:VAL11:...%
    // Concurrent
    if (SerialCSVDriver::hasValString(1, "ANALOG-C-PULSE")) {
        _concurrent_pulse_out(ANALOG_OP_TYPE);
        return true;
    }

    // DRY-C-PULSE
    // $INO:DRY-C-PULSE:PIN1:VAL10:TIME1:VAL11:...%
    // Concurrent
    if (SerialCSVDriver::hasValString(1, "DRY-C-PULSE")) {
        _concurrent_pulse_out(DRY_OP_TYPE);
        return true;
    }

    //// ------------
    // DOING: CREATE A CONCURRENT (NON-BLOCKING) _count_pulses2
    // use mean(time_on)/(mean(time_on) + mean(time_off))
    // each mean can be computed concurrently (there is not need to capture all pulses)

    // PULSE-IN
    // $INO:PULSE-IN:PIN:TIME%
    if (SerialCSVDriver::hasValString(1, "PULSE-IN")) {
        int pin = SerialCSVDriver::getValString(2).toInt();
        int time = SerialCSVDriver::getValString(3).toInt(); // sampling time ms
        unsigned long n = PinDriver::_count_pulses2(pin, time);
        SerialCSVDriver::sendMsgResponse("read", n);
        return true;
    }

    return false;
}

