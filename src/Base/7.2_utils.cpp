#include "Base/1_config.h"
#include "Base/2_Utils.h"
#include "Base/3_CSVLineReader.h"
#include "Base/5_SerialDriver.h"
#include "Base/6_SerialCSVDriver.h"
#include "Base/7_InoDriver.h"

/// -------------------------
// MARK: _count_pulses2
unsigned long InoDriver::_count_pulses2(int pin, unsigned long sampling_time)
{

    // reset
    unsigned long npulses = 0;
    unsigned long time0 = millis();

    while (true)
    {

        // wait till a HIGH pulse happends and ends
        unsigned long pw = pulseIn(pin, HIGH, PIN_PULSE_IN_TIMEOUT);
        if (pw > 0) {
            npulses++;
        }

        // Time out
        if (millis() - time0 > sampling_time)
        {
            break;
        }
    }

    return npulses;
}

/// -------------------------
// MARK: _count_pulses3
unsigned long InoDriver::_count_pulses3(int pin, unsigned long sampling_time)
{
    unsigned long npulses = 0;
    unsigned long time0 = millis();

    // Ensure pin is INPUT (or INPUT_PULLUP) somewhere in setup / PIN-MODE
    int last = digitalRead(pin);

    while (millis() - time0 < sampling_time)
    {
        int curr = digitalRead(pin);
        // Count rising edges
        if (last == LOW && curr == HIGH)
        {
            npulses++;
        }
        last = curr;
    }
    return npulses;
}

/// -------------------------
// MARK: _count_pulses4

// --- High-speed pulse counter state (file-scope globals) ---
volatile unsigned long ino_pulse_count = 0;

// Simple ISR: just increment the counter on each rising edge
void _count_pulses4_ISR()
{
    ino_pulse_count++;
}

unsigned long InoDriver::_count_pulses4(int pin, unsigned long sampling_time)
{
    // Reset counter
    ino_pulse_count = 0;

    // Map pin to interrupt number
    int intNum = digitalPinToInterrupt(pin);
    if (intNum == NOT_AN_INTERRUPT)
    {
        // You could also return some error code, but 0 is at least well-defined
        return 0;
    }

    // Make sure pin is configured as input somewhere before this
    // (you already have a PIN-MODE command for that)
    // pinMode(pin, INPUT); // often done via your CSV command

    // Attach ISR
    attachInterrupt(intNum, _count_pulses4_ISR, RISING);

    unsigned long t0 = millis();
    while (millis() - t0 < sampling_time)
    {
        // Nothing: just wait. You could call CSCReactor::onloop() here
        // if you want to stay responsive, but then your measurement window
        // is slightly less sharp in time (usually OK for OD).
    }

    // Stop counting
    detachInterrupt(intNum);

    // Return number of pulses seen in sampling_time ms
    return ino_pulse_count;
}


// MARK: _read
int InoDriver::_read(int type, unsigned int pin)
{
    if (type == DIGITAL_OP_TYPE)
    {
        return digitalRead(pin); // digitalWrite
    }
    if (type == ANALOG_OP_TYPE)
    {
        return analogRead(pin); // digitalWrit1
    }
    if (type == DRY_OP_TYPE)
    {
        Serial.print("dryRead(");
        Serial.print(pin);
        Serial.println(");");
        return -1;
    }
    Serial.println("_read: BAD TYPE");
    return -2;
}


// MARK: _write
void InoDriver::_write(int type, unsigned int pin, int val)
{
    if (type == DIGITAL_OP_TYPE)
    {
        digitalWrite(pin, val);
        return;
    }
    if (type == ANALOG_OP_TYPE)
    {
        analogWrite(pin, val);
        return;
    }
    if (type == DRY_OP_TYPE)
    {
        Serial.print("dryWrite(");
        Serial.print(pin);
        Serial.print(",");
        Serial.print(val);
        Serial.println(");");
        return;
    }
    Serial.println("_write: BAD TYPE");
}

// MARK: _pin_mode
void InoDriver::_pin_mode(int type, int pin, int mode)
{
    if (type == NONDRY_OP_TYPE)
    {
        pinMode(pin, mode);
        return;
    }
    if (type == DRY_OP_TYPE)
    {
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
// MARK: _serial_pin_mode
void InoDriver::_serial_pin_mode(int type)
{
    unsigned int i = 2;
    while (1)
    {
        // check args
        if (SerialCSVDriver::isEmpty(i))
        {
            break;
        } // pin index
        if (SerialCSVDriver::isEmpty(i + 1))
        {
            break;
        } // mode index

        // do stuff
        int pin = SerialCSVDriver::getValInt(i);
        int mode = SerialCSVDriver::getValInt(i + 1);
        _pin_mode(type, pin, mode);

        // up index
        i += 2;
    }
}

// S-READ
// MARK: _serial_read
void InoDriver::_serial_read(int type)
{
    unsigned int i = 2;
    while (1)
    {
        // check args
        if (SerialCSVDriver::isEmpty(i))
        {
            break;
        } // pin

        // do stuff
        int pin = SerialCSVDriver::getValInt(i);
        int val = _read(type, pin);
        SerialCSVDriver::sendMsgResponse("read", val);

        // up index
        i += 1;
    }
}

// S-WRITE
// MARK: _serial_write
void InoDriver::_serial_write(int type)
{
    unsigned int i = 2;
    while (1)
    {
        // check args
        if (SerialCSVDriver::isEmpty(i))
        {
            break;
        } // pin
        if (SerialCSVDriver::isEmpty(i + 1))
        {
            break;
        } // val

        // do stuff
        int pin = SerialCSVDriver::getValInt(i);
        int val = SerialCSVDriver::getValInt(i + 1);
        _write(type, pin, val);

        // up index
        i += 2;
    }
}

// DOING: complete all other calls...
// TODO: Maybe move to other file...

// S-PULSE
// MARK: _serial_pulse_out
extern void InoDriver::_serial_pulse_out(int type)
{
    unsigned int i = 2;
    while (1)
    {
        // check args
        if (SerialCSVDriver::isEmpty(i))
        {
            break;
        } // pin
        if (SerialCSVDriver::isEmpty(i + 1))
        {
            break;
        } // val0
        if (SerialCSVDriver::isEmpty(i + 2))
        {
            break;
        } // time
        if (SerialCSVDriver::isEmpty(i + 3))
        {
            break;
        } // val1

        // do stuff
        int pin = SerialCSVDriver::getValInt(i);
        int val0 = SerialCSVDriver::getValInt(i + 1);
        int time = SerialCSVDriver::getValInt(i + 2);
        int val1 = SerialCSVDriver::getValInt(i + 3);
        _write(type, pin, val0);
        delay(time);
        _write(type, pin, val1);
        SerialCSVDriver::sendMsgResponse("pin", pin, "et", time);

        // up index
        i += 4;
    }
}

// C-PULSE
// MARK: _concurrent_pulse_out
// $INO[0]:ANALOG-C-PULSE[1]:PIN1[2]:VAL10[3]:TIME1[4]:VAL11[5]:...%
void InoDriver::_concurrent_pulse_out(int type)
{

    // variables
    unsigned long t0 = millis(); // Use intervals to avoid int overflow
    unsigned int i = 2; // pin
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
    while (1)
    {
        // check args
        // $...:PIN1:VAL10:TIME1:VAL11:...%
        if (SerialCSVDriver::isEmpty(i))
        { // pin
            break;
        }
        if (SerialCSVDriver::isEmpty(i + 1))
        { // val0
            break;
        }
        if (SerialCSVDriver::isEmpty(i + 2))
        { // time
            break;
        }
        if (SerialCSVDriver::isEmpty(i + 3))
        { // val1
            break;
        }

        // do stuff
        // load
        // $...:PIN1:VAL10:TIME1:VAL11:...%
        pin = SerialCSVDriver::getValInt(i);
        val0 = SerialCSVDriver::getValInt(i + 1);
        time = SerialCSVDriver::getValInt(i + 2);
        val1 = SerialCSVDriver::getValInt(i + 3);

        // store
        SerialCSVDriver::aux0.set(pin, i);
        SerialCSVDriver::aux0.set(val0, i + 1);
        SerialCSVDriver::aux0.set(time, i + 2);
        SerialCSVDriver::aux0.set(val1, i + 3);

        // up index
        i += 4;
    }
    i1 = i; // store the first invalid arg set

    // digitalWrite
    for (i = 2; i < i1; i += 4)
    {
        pin = SerialCSVDriver::aux0.get(i);
        val0 = SerialCSVDriver::aux0.get(i + 1);

        _write(type, pin, val0);

        wrt = static_cast<int>(millis() - t0); // write time - ref time
        SerialCSVDriver::aux1.set(wrt, i);     // store rel write time
        SerialCSVDriver::aux2.set(1, i);       // flag on
    }

    // concurrent action
    while (1)
    {
        boolean someone = false;
        for (i = 2; i < i1; i += 4)
        {

            // check flag
            flag = SerialCSVDriver::aux2.get(i); // flag on
            if (!flag)
            {
                continue;
            }
            someone = true;

            // check time
            wrt = SerialCSVDriver::aux1.get(i);    // write time - ref time
            crt = static_cast<int>(millis() - t0); // check time - ref time
            et = crt - wrt;                        // elapsed time = ct - t0 - wt + t0 = ct - wt

            tt = SerialCSVDriver::aux0.get(i + 2); // target time
            // SerialDriver::println("et: ", et, ", tt: ", tt);
            if (et < tt)
            {
                continue;
            }
            if (et > PIN_PULSE_OUT_MAX_TIME)
            {
                continue;
            }

            // action
            pin = SerialCSVDriver::aux0.get(i);
            val1 = SerialCSVDriver::aux0.get(i + 3);

            _write(type, pin, val1);

            SerialCSVDriver::aux2.set(0, i);  // flag off
            SerialCSVDriver::aux1.set(et, i); // store elapsed
        }
        if (!someone)
        {
            break;
        }
    }

    // responde
    for (i = 2; i < i1; i += 4)
    {
        pin = SerialCSVDriver::aux0.get(i);
        et = SerialCSVDriver::aux1.get(i); // stored elapsed
        SerialCSVDriver::sendMsgResponse("pin", pin, "et", et);
    }
}

// TODO: Make a multi pin reading method
// By measuring the HIGH/LOW average time we should be able to get the frequency
// TODO: Finish this

// TOUT:PIN1:PIN2:PIN3...
// void InoDriver::_concurrent_pulse_in() {

//     unsigned int i = 2;
//     unsigned int i1 = 0;
//     int pin = 0;
//     int tout = 0;
//     unsigned long t0 = 0; // Use intervals to avoid int overflow

//     // tout
//     if (SerialCSVDriver::isEmpty(i)) { return; }
//     tout = SerialCSVDriver::getValInt(i);
//     i++;

//     // load
//     while (1) {
//         // check args
//         if (SerialCSVDriver::isEmpty(i)) { break; }   // pin
//         pin = SerialCSVDriver::getValInt(i);
//         SerialCSVDriver::aux0.set(pin, i);
//         SerialCSVDriver::aux1.set(INT_MIN, i); // accumulator
//         SerialCSVDriver::aux2.set(INT_MIN, i); // counter
//         i += 1;
//     }
//     i1 = i; // store the first invalid arg index

//     // concurrent pulse in
//     t0 = millis();
//     while (true) {
//     }

//     // // reset
//     // unsigned long n = 0;
//     // unsigned long time0 = millis();

//     // while (true) {

//     //     // wait till a HIGH pulse happends and ends
//     //     pulseIn(pin, HIGH, PIN_PULSE_IN_TIMEOUT);
//     //     n++;

//     //     // Time out
//     //     if (millis() - time0 > sampling_time) { break; }
//     // }

//     // return n;

//     // // concurrent "sleep"
//     // while (1) {
//     //     boolean someone = false;
//     //     for (i = 2; i < i1; i += 4) {

//     //         // check flag
//     //         flag = SerialCSVDriver::aux2.get(i); // flag on
//     //         if (!flag) { continue; }
//     //         someone = true;

//     //         // check time
//     //         wrt = SerialCSVDriver::aux1.get(i);     // write time - ref time
//     //         crt = static_cast<int>(millis() - t0);  // check time - ref time
//     //         et = crt - wrt;                         // elapsed time = ct - t0 - wt + t0 = ct - wt
//     //         tt = SerialCSVDriver::aux0.get(i+2);    // target time
//     //         if (et >= tt || et >= PIN_PULSE_OUT_MAX_TIME) {
//     //             pin = SerialCSVDriver::aux0.get(i);
//     //             val1 = SerialCSVDriver::aux0.get(i+3);

//     //             _write(type, pin, val1);

//     //             SerialCSVDriver::aux2.set(0, i); // flag off
//     //             SerialCSVDriver::aux1.set(et, i); // store elapsed
//     //         }
//     //     }
//     //     if (!someone) { break; }
//     // }

//     // // responde
//     // for (i = 2; i < i1; i += 4) {
//     //     et = SerialCSVDriver::aux1.get(i); // store elapsed
//     //     SerialCSVDriver::sendMsgResponse("et", et);
//     // }
// }