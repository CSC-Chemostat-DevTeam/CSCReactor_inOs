#include <Arduino.h>
#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/4_DOHandler.h"
#include "Base/4_MsgHandler.h"
#include "Base/4_SerialHandler.h"
#include "Base/4_LogHandler.h"
#include "Base/4_Chemostat.h"

// ----------------------------------------------------
// CONSTRUCTOR
DOHandler::DOHandler(Chemostat* Ch) : 
    AbsHandler(
        /* Chemostat */ Ch
    ){

    this->laser_pwd = DO_LASER_PWD_DFLT_VALUE;
    this->led1_val = 0;
    this->led2_val = 0;
}


// ----------------------------------------------------
// SKETCH INTERFACE
void DOHandler::onsetup() {
    pinMode(DO_LED1_PIN, INPUT_PULLUP);
    pinMode(DO_LED2_PIN, INPUT_PULLUP);
    pinMode(DO_LASER_PWD_PIN, OUTPUT);  
}
void DOHandler::onloop() {;}

// ----------------------------------------------------
// _DEV INTERFACE
String DOHandler::getClassName() { return "DOHandler"; }
void DOHandler::sayHi() { 
    AbsHandler::sayHi(); // Parent
    Ch->pSERIAL->println(TAB, "led1 pin: ", DO_LED1_PIN);
    Ch->pSERIAL->println(TAB, "led2 pin: ", DO_LED2_PIN);
    Ch->pSERIAL->println(TAB, "laser pin: ", DO_LASER_PWD_PIN);
}

// ----------------------------------------------------
// DO INTERFACE
void DOHandler::laserOn(){
    analogWrite(DO_LASER_PWD_PIN, this->laser_pwd);
}
void DOHandler::laserOff(){
    analogWrite(DO_LASER_PWD_PIN, 0);
}
// BLOCKING
void DOHandler::measureDO(){

    this->Ch->handleBlokingInit("measureDO");

    this->laserOn();
    delay(20); // stabilization?
    this->led1_val = _count_pulses(DO_LED1_PIN, DO_LED_SAMPLING_TIME);
    this->led2_val =_count_pulses(DO_LED2_PIN, DO_LED_SAMPLING_TIME);
    this->laserOff();
    
    this->Ch->handleBlokingEnd("measureDO");

}

// -------------------------
// HANDLE MSG INTERFACE
boolean DOHandler::handleMsg() {

    MsgHandler* const pMSG = this->Ch->pMSG;

    // Check target code
    if (!pMSG->hasValString(0, "DO")) { return false; }

    // Example: $DO:LASER-ON%
    if (pMSG->hasValString(1, "LASER-ON")) {
        this->laserOn();
        pMSG->sendMsgResponse("laser_pwd", this->laser_pwd);
        return true;
    }
    // Example: $DO:LASER-OFF%
    if (pMSG->hasValString(1, "LASER-OFF")) {
        this->laserOff();
        return true;
    }
    // Example: $DO:LASER-PWD:250%
    if (pMSG->hasValString(1, "LASER-PWD")) {
        pMSG->sendMsgResponse("laser_pwd", this->laser_pwd);
        String arg2 = pMSG->getValString(2);
        if (!arg2.equals("")) { 
            this->laser_pwd = arg2.toInt();
            pMSG->sendMsgResponse("new_laser_pwd", this->laser_pwd);
        }
        return true;
    }
    // Example: $DO:LED-MEASURE!%
    if (pMSG->hasValString(1, "LED-MEASURE!")) {
        this->measureDO(); // BLOCKING
        pMSG->sendMsgResponse("led1_val", this->led1_val);
        pMSG->sendMsgResponse("led2_val", this->led2_val);
        return true;
    }

    return false;
}

// ----------------------------------------------------
// DO UTILS
// BLOCKING
long _count_pulses3(int pin, unsigned long sampling_time) {
    
    sampling_time = sampling_time * 1000; // to micro

    // reset
    long n = 0;

    long t0 = micros();
    while (true) {

        // Time out
        if (micros() - t0 > sampling_time) { break; }

        // wait till a HIGH pulse happends and ends
        noInterrupts();
        if (pulseIn(pin, HIGH, sampling_time) > 0L) { n++; }
        interrupts();
        // 3 * 10^6 s -> 1000 kHz

    }

    // Serial.println(n);

    return n;
}

long _count_pulses2(int pin, unsigned long sampling_time) {
    
    // noInterrupts();
    sampling_time = sampling_time * 1000; // to micro

    // reset
    long n = 0;
    unsigned long pulse_time = 0;

    while (true) {

        // wait till a HIGH pulse happends and ends
        // pulseIn(pin, HIGH, 100);
        pulse_time += pulseIn(pin, HIGH, 1);
        pulse_time += pulseIn(pin, LOW, 1);
        Serial.println(pulse_time);
        // pulseIn(pin, HIGH, DO_MAX_PER_PULSE_TIMEOUT_DFLT_VAL);

        n++;

        // Time out
        if (pulse_time > sampling_time) { break; }
    }

    // interrupts();

    return n;
}

long _count_pulses(int pin, unsigned long sampling_time) {
    int N = 1000;
    long acc = 0L;
    for (int i = 0; i < N; i++) {
        acc += analogRead(pin);
    }
    return acc / N;
}