#include "Base/1_config.h"
#include "Base/2_Utils.h"
#include "Base/3_CSVLineReader.h"
#include "Base/5_SerialDriver.h"
#include "Base/6_SerialCSVDriver.h"
#include "Base/7_ArduinoDriver.h"

/// -------------------------
/// HANDLE MSG INTERFACE
boolean ArduinoDriver::handleMsg() { 
    
    // Check target code
    if (!SerialCSVDriver::hasValString(0, "INO")) { return false; }

    // TEST MSGS
    // Example: $INO:SAY-HI%
    if (SerialCSVDriver::hasValString(1, "SAY-HI")) {
        ArduinoDriver::sayHi(); 
        return true;
    }
    
    //// ------------
    // PIN-MODE
    // $INO:PIN-MODE:PIN:MODE%
    if (SerialCSVDriver::hasValString(1, "PIN-MODE")) {
        int pin = SerialCSVDriver::getValString(2).toInt();
        int mode = SerialCSVDriver::getValString(3).toInt();
        pinMode(pin, mode);
        return true;
    }

    //// ------------
    // DIGITAL-WRITE
    // $INO:DIGITAL-WRITE:PIN:VAL%
    if (SerialCSVDriver::hasValString(1, "DIGITAL-WRITE")) {
        int pin = SerialCSVDriver::getValString(2).toInt();
        int val = SerialCSVDriver::getValString(3).toInt();
        digitalWrite(pin, val);
        return true;
    }
    
    //// ------------
    // ANALOG-WRITE
    // $INO:ANALOG-WRITE:PIN:VAL%
    if (SerialCSVDriver::hasValString(1, "ANALOG-WRITE")) {
        int pin = SerialCSVDriver::getValString(2).toInt();
        int val = SerialCSVDriver::getValString(3).toInt();
        analogWrite(pin, val);
        return true;
    }
    
    //// ------------
    // ANALOG-READ
    // $INO:ANALOG-READ:PIN%
    if (SerialCSVDriver::hasValString(1, "ANALOG-READ")) {
        int pin = SerialCSVDriver::getValString(2).toInt();
        int val = analogRead(pin);
        SerialCSVDriver::sendMsgResponse("read", val);
        return true;
    }

    //// ------------
    // DIGITAL-READ
    // $INO:DIGITAL-READ:PIN%
    if (SerialCSVDriver::hasValString(1, "DIGITAL-READ")) {
        int pin = SerialCSVDriver::getValString(2).toInt();
        int val = digitalRead(pin);
        SerialCSVDriver::sendMsgResponse("read", val);
        return true;
    }

    //// ------------
    // DIGITAL-PULSE
    // $INO:DIGITAL-PULSE:PIN:VAL:VAL0:TIME%
    if (SerialCSVDriver::hasValString(1, "DIGITAL-PULSE")) {
        int pin = SerialCSVDriver::getValString(2).toInt();
        int val = SerialCSVDriver::getValString(3).toInt();
        int val0 = SerialCSVDriver::getValString(4).toInt();
        int time = SerialCSVDriver::getValString(5).toInt();
        digitalWrite(pin, val);
        delay(time);
        digitalWrite(pin, val0);
        return true;
    }

    // $INO:DIGITAL-PULSE2:PIN1:VAL1:VAL10:PIN2:VAL2:VAL20:TIME%
    if (SerialCSVDriver::hasValString(1, "DIGITAL-PULSE2")) {
        int pin1 = SerialCSVDriver::getValString(2).toInt();
        int val1 = SerialCSVDriver::getValString(3).toInt();
        int val10 = SerialCSVDriver::getValString(4).toInt();
        int pin2 = SerialCSVDriver::getValString(5).toInt();
        int val2 = SerialCSVDriver::getValString(6).toInt();
        int val20 = SerialCSVDriver::getValString(7).toInt();
        int time = SerialCSVDriver::getValString(8).toInt();
        digitalWrite(pin1, val1);
        digitalWrite(pin2, val2);
        delay(time);
        digitalWrite(pin1, val10);
        digitalWrite(pin2, val20);
        return true;
    }

    //// ------------
    // ANALOG-PULSE
    // $INO:ANALOG-PULSE:PIN:VAL:VAL0:TIME%
    if (SerialCSVDriver::hasValString(1, "ANALOG-PULSE")) {
        int pin = SerialCSVDriver::getValString(2).toInt();
        int val = SerialCSVDriver::getValString(3).toInt();
        int val0 = SerialCSVDriver::getValString(4).toInt();
        int time = SerialCSVDriver::getValString(5).toInt();
        analogWrite(pin, val);
        delay(time);
        analogWrite(pin, val0);
        return true;
    }

    // $INO:ANALOG-PULSE2:PIN1:VAL1:VAL10:PIN2:VAL2:VAL20:TIME%
    if (SerialCSVDriver::hasValString(1, "ANALOG-PULSE2")) {
        int pin1 = SerialCSVDriver::getValString(2).toInt();
        int val1 = SerialCSVDriver::getValString(3).toInt();
        int val10 = SerialCSVDriver::getValString(4).toInt();
        int pin2 = SerialCSVDriver::getValString(5).toInt();
        int val2 = SerialCSVDriver::getValString(6).toInt();
        int val20 = SerialCSVDriver::getValString(7).toInt();
        int time = SerialCSVDriver::getValString(8).toInt();
        analogWrite(pin1, val1);
        analogWrite(pin2, val2);
        delay(time);
        analogWrite(pin1, val10);
        analogWrite(pin2, val20);
        return true;
    }

    
    

    //// ------------
    // PULSE-IN
    // $INO:PULSE-IN:PIN:TIME%
    if (SerialCSVDriver::hasValString(1, "PULSE-IN")) {
        int pin = SerialCSVDriver::getValString(2).toInt();
        int time = SerialCSVDriver::getValString(3).toInt(); // sampling time ms
        unsigned long n = ArduinoDriver::_count_pulses2(pin, time);
        SerialCSVDriver::sendMsgResponse("read", n);
        return true;
    }

    // $INO:PULSE-IN:PIN:TIME%
    if (SerialCSVDriver::hasValString(1, "PULSE-IN")) {
        int pin = SerialCSVDriver::getValString(2).toInt();
        int time = SerialCSVDriver::getValString(3).toInt(); // sampling time ms
        unsigned long n = ArduinoDriver::_count_pulses2(pin, time);
        SerialCSVDriver::sendMsgResponse("read", n);
        return true;
    }


    return false;
}

