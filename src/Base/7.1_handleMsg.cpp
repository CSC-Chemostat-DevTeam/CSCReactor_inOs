#include "Base/1_config.h"
#include "Base/2_Utils.h"
#include "Base/3_CSVLineReader.h"
#include "Base/5_SerialDriver.h"
#include "Base/6_SerialCSVDriver.h"
#include "Base/7_ArduinoDriver.h"

/// -------------------------
#define ANALOG_OP_TYPE 0
#define DIGITAL_OP_TYPE 1
#define DRY_OP_TYPE 2

extern void _serial_pin_mode(int type);
extern void _serial_write(int type);
extern void _serial_read(int type);
extern void _serial_pulse(int type);
extern void _concurrent_pulse(int type);

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
    // $INO:DIGITAL-S-PULSE:PIN:VAL0:TIME:[VAL1]%
    // precise/fast pulse
    if (SerialCSVDriver::hasValString(1, "DIGITAL-S-PULSE")) {
        _serial_pulse(DIGITAL_OP_TYPE);
        return true;
    }

    // ANALOG-S-PULSE
    // $INO:ANALOG-S-PULSE:PIN:VAL0:TIME:[VAL1]%
    // precise/fast pulse
    if (SerialCSVDriver::hasValString(1, "ANALOG-S-PULSE")) {
        _serial_pulse(ANALOG_OP_TYPE);
        return true;
    }

    // DRY-S-PULSE
    // $INO:DRY-S-PULSE:PIN:VAL0:TIME:[VAL1]%
    // precise/fast pulse
    if (SerialCSVDriver::hasValString(1, "DRY-S-PULSE")) {
        _serial_pulse(DRY_OP_TYPE);
        return true;
    }

    //// ------------
    // C-PULSE

    // DIGITAL-C-PULSE
    // $INO:DIGITAL-C-PULSE:PIN1:VAL10:TIME1:VAL11:...%
    // Concurrent
    if (SerialCSVDriver::hasValString(1, "DIGITAL-C-PULSE")) {
        _concurrent_pulse(DIGITAL_OP_TYPE);
        return true;
    }

    // ANALOG-C-PULSE
    // $INO:ANALOG-C-PULSE:PIN1:VAL10:TIME1:VAL11:...%
    // Concurrent
    if (SerialCSVDriver::hasValString(1, "ANALOG-C-PULSE")) {
        _concurrent_pulse(ANALOG_OP_TYPE);
        return true;
    }

    // DRY-C-PULSE
    // $INO:DRY-C-PULSE:PIN1:VAL10:TIME1:VAL11:...%
    // Concurrent
    if (SerialCSVDriver::hasValString(1, "DRY-C-PULSE")) {
        _concurrent_pulse(DRY_OP_TYPE);
        return true;
    }

    // // $INO:DIGITAL-PULSE2:PIN1:VAL1:VAL10:PIN2:VAL2:VAL20:TIME%
    // if (SerialCSVDriver::hasValString(1, "DIGITAL-PULSE2")) {
    //     int pin1 = SerialCSVDriver::getValString(2).toInt();
    //     int val1 = SerialCSVDriver::getValString(3).toInt();
    //     int val10 = SerialCSVDriver::getValString(4).toInt();
    //     int pin2 = SerialCSVDriver::getValString(5).toInt();
    //     int val2 = SerialCSVDriver::getValString(6).toInt();
    //     int val20 = SerialCSVDriver::getValString(7).toInt();
    //     int time = SerialCSVDriver::getValString(8).toInt();
    //     digitalWrite(pin1, val1);
    //     digitalWrite(pin2, val2);
    //     delay(time);
    //     digitalWrite(pin1, val10);
    //     digitalWrite(pin2, val20);
    //     return true;
    // }

    // //// ------------
    // // ANALOG-PULSE
    // // $INO:ANALOG-PULSE:PIN:VAL:VAL0:TIME%
    // if (SerialCSVDriver::hasValString(1, "ANALOG-PULSE")) {
    //     int pin = SerialCSVDriver::getValString(2).toInt();
    //     int val = SerialCSVDriver::getValString(3).toInt();
    //     int val0 = SerialCSVDriver::getValString(4).toInt();
    //     int time = SerialCSVDriver::getValString(5).toInt();
    //     analogWrite(pin, val);
    //     delay(time);
    //     analogWrite(pin, val0);
    //     return true;
    // }

    // // $INO:ANALOG-PULSE2:PIN1:VAL1:VAL10:PIN2:VAL2:VAL20:TIME%
    // if (SerialCSVDriver::hasValString(1, "ANALOG-PULSE2")) {
    //     int pin1 = SerialCSVDriver::getValString(2).toInt();
    //     int val1 = SerialCSVDriver::getValString(3).toInt();
    //     int val10 = SerialCSVDriver::getValString(4).toInt();
    //     int pin2 = SerialCSVDriver::getValString(5).toInt();
    //     int val2 = SerialCSVDriver::getValString(6).toInt();
    //     int val20 = SerialCSVDriver::getValString(7).toInt();
    //     int time = SerialCSVDriver::getValString(8).toInt();
    //     analogWrite(pin1, val1);
    //     analogWrite(pin2, val2);
    //     delay(time);
    //     analogWrite(pin1, val10);
    //     analogWrite(pin2, val20);
    //     return true;
    // }

    // //// ------------
    // // PULSE-IN
    // // $INO:PULSE-IN:PIN:TIME%
    // if (SerialCSVDriver::hasValString(1, "PULSE-IN")) {
    //     int pin = SerialCSVDriver::getValString(2).toInt();
    //     int time = SerialCSVDriver::getValString(3).toInt(); // sampling time ms
    //     unsigned long n = ArduinoDriver::_count_pulses2(pin, time);
    //     SerialCSVDriver::sendMsgResponse("read", n);
    //     return true;
    // }

    // // $INO:PULSE-IN:PIN:TIME%
    // if (SerialCSVDriver::hasValString(1, "PULSE-IN")) {
    //     int pin = SerialCSVDriver::getValString(2).toInt();
    //     int time = SerialCSVDriver::getValString(3).toInt(); // sampling time ms
    //     unsigned long n = ArduinoDriver::_count_pulses2(pin, time);
    //     SerialCSVDriver::sendMsgResponse("read", n);
    //     return true;
    // }


    return false;
}


/// -------------------------
int _read(int type, unsigned int pin) {
    if (type == DIGITAL_OP_TYPE) {
        return digitalRead(pin); // digitalWrite
    } 
    if (type == ANALOG_OP_TYPE) {
        return analogRead(pin); // digitalWrit1
    } 
    if (type == DRY_OP_TYPE) {
        Serial.print("dryRead(");
        Serial.print(pin);
        Serial.println(");");
        return -1;
    }
    Serial.println("_read: BAD TYPE");
    return -2;
}

void _write(int type, unsigned int pin, int val) {
    if (type == DIGITAL_OP_TYPE) {
        digitalWrite(pin, val);
        return;
    } 
    if (type == ANALOG_OP_TYPE) {
        analogWrite(pin, val);
        return;
    } 
    if (type == DRY_OP_TYPE) {
        Serial.print("dryWrite(");
        Serial.print(pin);
        Serial.print(",");
        Serial.print(val);
        Serial.println(");");
        return;
    }
    Serial.println("_write: BAD TYPE");
}
void _pin_mode(int type, int pin, int mode) {
    if (type == NONDRY_OP_TYPE) {
        pinMode(pin, mode);
        return;
    }
    if (type == DRY_OP_TYPE) {
        Serial.print("dryPinMode(");
        Serial.print(pin);
        Serial.print(",");
        Serial.print(mode);
        Serial.println(");");
        return;
    }
    Serial.println("_pin_mode: BAD TYPE");
}

/// -------------------------
// "PIN-MODE"
void _serial_pin_mode(int type){
    unsigned int i = 2;
    while (1) {
        // check args
        if (SerialCSVDriver::isEmpty(i)) { break; }     // pin index
        if (SerialCSVDriver::isEmpty(i+1)) { break; }   // mode index

        // do stuff
        int pin = SerialCSVDriver::getValInt(i);
        int mode = SerialCSVDriver::getValInt(i+1);
        _pin_mode(type, pin, mode);
        
        // up index
        i += 2;
    }
}

// S-READ
void _serial_read(int type) {
    unsigned int i = 2;
    while (1) {
        // check args
        if (SerialCSVDriver::isEmpty(i)) { break; } // pin
        
        // do stuff
        int pin = SerialCSVDriver::getValInt(i);
        int val = _read(type, pin);
        SerialCSVDriver::sendMsgResponse("read", val);

        // up index
        i += 1;
    }
}

// S-WRITE
void _serial_write(int type) {
    unsigned int i = 2;
    while (1) {
        // check args
        if (SerialCSVDriver::isEmpty(i)) { break; }   // pin
        if (SerialCSVDriver::isEmpty(i+1)) { break; } // val

        // do stuff
        int pin = SerialCSVDriver::getValInt(i);
        int val = SerialCSVDriver::getValInt(i+1);
        _write(type, pin, val);

        // up index
        i += 2;
    }
}

// DOING: complete all other calls...
// TODO: Maybe move to other file...

// S-PULSE
extern void _serial_pulse(int type) {
    int pin = SerialCSVDriver::getValInt(2);
    int val0 = SerialCSVDriver::getValInt(3);
    int time = SerialCSVDriver::getValInt(4);
    int val1 = SerialCSVDriver::getValInt(5, 0);
    _write(type, pin, val0);
    delay(time);
    _write(type, pin, val1);
    SerialCSVDriver::sendMsgResponse("et", time);
}

// C-PULSE
void _concurrent_pulse(int type){
 
    // variables
    unsigned long t0 = millis(); // Use intervals to avoid int overflow
    unsigned int i = 2;
    unsigned int i1 = 0;
    int pin = 0;
    int val0 = 0;
    int time = 0;
    int val1 = 0;
    int flag = 0;
    int wrt = 0;
    int crt = 0;
    int et = 0;
    int tt = 0;

    // load
    while (1) {
        // check args
        if (SerialCSVDriver::isEmpty(i)) { break; }   // pin
        if (SerialCSVDriver::isEmpty(i+1)) { break; } // val0
        if (SerialCSVDriver::isEmpty(i+2)) { break; } // time
        if (SerialCSVDriver::isEmpty(i+3)) { break; } // val1

        // do stuff
        // load
        pin = SerialCSVDriver::getValInt(i); 
        val0 = SerialCSVDriver::getValInt(i+1); 
        time = SerialCSVDriver::getValInt(i+2);
        val1 = SerialCSVDriver::getValInt(i+3);
        
        // store
        SerialCSVDriver::aux0.set(pin, i);
        SerialCSVDriver::aux0.set(val0, i+1); 
        SerialCSVDriver::aux0.set(time, i+2); 
        SerialCSVDriver::aux0.set(val1, i+3); 

        // up index
        i += 4;
    }
    i1 = i; // store the first invalid arg set
    

    // digitalWrite
    for (i = 2; i < i1; i += 4) {
        pin = SerialCSVDriver::aux0.get(i);
        val0 = SerialCSVDriver::aux0.get(i+1); 

        _write(type, pin, val0);
        
        wrt = static_cast<int>(millis() - t0); // write time - ref time
        SerialCSVDriver::aux1.set(wrt, i); // store rel write time
        SerialCSVDriver::aux2.set(1, i); // flag on
    }

    // "sleep"
    while (1) {
        boolean someone = false;
        for (i = 2; i < i1; i += 4) {

            // check flag
            flag = SerialCSVDriver::aux2.get(i); // flag on
            if (!flag) { continue; }
            someone = true;

            // check time
            wrt = SerialCSVDriver::aux1.get(i);     // write time - ref time
            crt = static_cast<int>(millis() - t0);  // check time - ref time
            et = crt - wrt;                         // elapsed time = ct - t0 - wt + t0 = ct - wt
            tt = SerialCSVDriver::aux0.get(i+2);    // target time
            if (et >= tt || et >= ARDUINO_MAX_PULSE_TIME) {
                pin = SerialCSVDriver::aux0.get(i);
                val1 = SerialCSVDriver::aux0.get(i+3);

                _write(type, pin, val1);

                SerialCSVDriver::aux2.set(0, i); // flag off
                SerialCSVDriver::aux1.set(et, i); // store elapsed
            }
        }
        if (!someone) { break; }
    }

    // responde
    for (i = 2; i < i1; i += 4) {
        et = SerialCSVDriver::aux1.get(i); // store elapsed
        SerialCSVDriver::sendMsgResponse("et", et);
    }
}