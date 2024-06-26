#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/4_LEDHandler.h"
#include "Base/4_MsgHandler.h"
#include "Base/4_SerialHandler.h"

// ----------------------------------------------------
// CONSTRUCTOR
LEDHandler::LEDHandler(Chemostat* Ch, byte pin) : 
    AbsHandler(
        /* Chemostat */ Ch
    ){
    this->pin = pin;
}


// ----------------------------------------------------
// SKETCH INTERFACE
void LEDHandler::onsetup() {
    pinMode(this->pin, OUTPUT);
    digitalWrite(this->pin, HIGH);
}
void LEDHandler::onloop() {;}

// ----------------------------------------------------
// _DEV INTERFACE
String LEDHandler::getClassName() { return "LEDHandler"; }
void LEDHandler::sayHi() { 
    AbsHandler::sayHi(); // Parent
    Ch->pSERIAL->println(TAB, "pin: ", this->pin);
    Ch->pSERIAL->println(TAB, "state: ", this->getState());
}

// ----------------------------------------------------
// LED INTERFACE
void LEDHandler::ledOn(){
    digitalWrite(this->pin, HIGH);
}
void LEDHandler::ledOff(){
    digitalWrite(this->pin, LOW);
}
void LEDHandler::setState(int state){
    digitalWrite(this->pin, state);
}
int LEDHandler::getState(){
    return digitalRead(this->pin);
}
void LEDHandler::flip(){
    if (this->getState() == HIGH) { ledOff(); }
     else { ledOn(); }
}

// -------------------------
// HANDLE MSG INTERFACE
boolean LEDHandler::handleMsg() {

    MsgHandler* const pMSG = this->Ch->pMSG;

    // Check target code
    if (!pMSG->hasValString(0, "LED")) { return false; }
    if (pMSG->getValString(1).toInt() != this->pin) { return false; }

    // Example: $LED:13:ON%
    if (pMSG->hasValString(2, "ON")) {
        this->ledOn();
        pMSG->sendMsgResponse("LED", this->pin, this->getState());
        return true;
    }
    // Example: $LED13:OFF%
    if (pMSG->hasValString(2, "OFF")) {
        this->ledOff();
        pMSG->sendMsgResponse("LED", this->pin, this->getState());
        return true;
    }
    // Example: $LED13:FLIP%
    if (pMSG->hasValString(2, "FLIP")) {
        this->flip();
        pMSG->sendMsgResponse("LED", this->pin, this->getState());
        return true;
    }

    return false;
}