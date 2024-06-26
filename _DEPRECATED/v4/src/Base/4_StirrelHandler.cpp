#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/4_StirrelHandler.h"
#include "Base/4_MsgHandler.h"
#include "Base/4_SerialHandler.h"

// ----------------------------------------------------
// CONSTRUCTOR
StirrelHandler::StirrelHandler(Chemostat* Ch) : 
    AbsHandler(
        /* Chemostat */ Ch
    ){
    this->pwd1 = STIRREL_DIR1_PWD_DFLT_VAL;
    this->pwd2 = STIRREL_DIR2_PWD_DFLT_VAL;
}

// ----------------------------------------------------
// SKETCH INTERFACE
void StirrelHandler::onsetup() {
    pinMode(STIRREL_DIR1_PIN, OUTPUT);
    pinMode(STIRREL_DIR2_PIN, OUTPUT);
    analogWrite(STIRREL_DIR1_PIN, 0);
    analogWrite(STIRREL_DIR2_PIN, 0);
}
void StirrelHandler::onloop() {;}

// ----------------------------------------------------
// _DEV INTERFACE
String StirrelHandler::getClassName() { return "StirrelHandler"; }
void StirrelHandler::sayHi() { 
    AbsHandler::sayHi(); // Parent
    Ch->pSERIAL->println(TAB, "dir1_pin: ", STIRREL_DIR1_PIN);
    Ch->pSERIAL->println(TAB, "dir1_pwd: ", this->pwd1);
    Ch->pSERIAL->println(TAB, "dir2_pin: ", STIRREL_DIR2_PIN);
    Ch->pSERIAL->println(TAB, "dir2_pwd: ", this->pwd2);
}


// ----------------------------------------------------
// BLOCKING INTERFACE
void onBlokingInit(){
    analogWrite(STIRREL_DIR1_PIN, 0);
    analogWrite(STIRREL_DIR2_PIN, 0);
}

// -------------------------
// HANDLE MSG INTERFACE
boolean StirrelHandler::handleMsg() {

    MsgHandler* const pMSG = this->Ch->pMSG;

    // Check target code
    if (!pMSG->hasValString(0, "STRR")) { return false; }

    // Example: $STRR:PULSE!:1:500%
    if (pMSG->hasValString(1, "PULSE!")) {
        int d = pMSG->getValString(2).toInt();
        int t = pMSG->getValString(3).toInt();
        if (t == 0) { t = STIRREL_PULSE_TIME_DFLT_VAL; }
        this->stirrelPulse(d, t);
        pMSG->sendMsgResponse("STRR-PULSE!", d, t);
        return true;
    }

    // Example: $STRR:PWD:1:250%
    if (pMSG->hasValString(1, "PWD")) {
        int d = pMSG->getValString(2).toInt();
        int pwd = pMSG->getValString(3).toInt();
        if (d == 1){
            this->pwd1 = pwd;
            pMSG->sendMsgResponse("pwd1", this->pwd1);
        } else {
            this->pwd2 = pwd;
            pMSG->sendMsgResponse("pwd2", this->pwd2);
        }
        return true;
    }

    return false;
}


// ----------------------------------------------------
// LED INTERFACE
// BLOCKING
void StirrelHandler::stirrelPulse(int d, int t){
    this->Ch->handleBlokingInit("stirrelPulse");
    analogWrite(STIRREL_DIR1_PIN, 0);
    analogWrite(STIRREL_DIR2_PIN, 0);
    if (d == 1) { analogWrite(STIRREL_DIR1_PIN, this->pwd1); }
    if (d == 2) { analogWrite(STIRREL_DIR2_PIN, this->pwd2); }
    delay(t);
    analogWrite(STIRREL_DIR2_PIN, 0);
    analogWrite(STIRREL_DIR1_PIN, 0);
    this->Ch->handleBlokingEnd("stirrelPulse");
}

void StirrelHandler::stirrelOff(){
    analogWrite(STIRREL_DIR1_PIN, 0);
    analogWrite(STIRREL_DIR2_PIN, 0);
}