#include <Arduino.h>

#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/4_Chemostat.h"
#include "Base/4_SerialHandler.h"
#include "Base/4_MsgHandler.h"
#include "Base/4_SDHandler.h"
#include "Base/4_LogHandler.h"
#include "Base/4_LEDHandler.h"
#include "Base/4_DOHandler.h"
#include "Base/4_StirrelHandler.h"

// ----------------------------------------------------
// CONSTRUCTOR
Chemostat::Chemostat() {
    
    // Serial.println(">>> At Chemostat::Chemostat <<<");

    // HANDLERS
    this->pMSG = new MsgHandler(this); // TODO: [HEAP] Check proper free/delete
    this->pSERIAL = new SerialHandler(this); // TODO: [HEAP] Check proper free/delete
    // this->pSD = new SDHandler(this); // TODO: [HEAP] Check proper free/delete
    this->pLOG = new LogHandler(this); // TODO: [HEAP] Check proper free/delete
    this->pBLED = new LEDHandler(this, LED_BUILTIN); // TODO: [HEAP] Check proper free/delete
    this->pDO = new DOHandler(this); // TODO: [HEAP] Check proper free/delete
    this->pSTRR = new StirrelHandler(this); // TODO: [HEAP] Check proper free/delete

    /// ALL HANDLERS INTERFACE
    this->_ALL_HANDLERS_BUFFER[0] = NULL;
    this->pushHandler(this->pMSG);
    this->pushHandler(this->pSERIAL);
    // this->pushHandler(this->pSD);
    this->pushHandler(this->pLOG);
    this->pushHandler(this->pBLED);
    this->pushHandler(this->pDO);
    this->pushHandler(this->pSTRR);
}

//  TODO: Use _ALL_HANDLERS_BUFFER for setting a Chemostat destroyer

// ----------------------------------------------------
// TIMETAG INTERFACE
// TODO: If a clock module is installed use it as TimeTag, 
// or use the accumulated SD aided progress
String Chemostat::nowTimeTag() { return String(millis()); }

// ----------------------------------------------------
// _DEV INTERFACE
String Chemostat::getClassName() { return "Chemostat"; }
void Chemostat::sayHi() {
    pSERIAL->println("Hi from ", this->getClassName(), " *", (unsigned int)this);
    // Handlers
    for (int i = 0; i < CHEMOSTAT_HANDLERS_BUFFER_SIZE; i++) {
        if (_ALL_HANDLERS_BUFFER[i] == NULL){ break; }
        _ALL_HANDLERS_BUFFER[i]->sayHi();
    }
}

// ----------------------------------------------------
// MSG INTERFACE
boolean Chemostat::handleMsg() {

    // Check target code
    if (!pMSG->hasValString(0, "CH")) { return false; }

    // TEST MSGS
    // Example: $CH:SAY-HI%
    if (pMSG->hasValString(1, "SAY-HI")) {
        sayHi(); 
        return true;
    }

    // ECHO
    // Example: $CH:ECHO:BLA:10%
    if (pMSG->hasValString(1, "ECHO")) {
        int n = 1;
        String val2 = pMSG->getValString(2);
        String val3 = pMSG->getValString(3);
        if (!val3.equals("")) { n = val3.toInt();}
        for (int i = 0; i < n; i++) {
            pMSG->sendMsgResponse(val2);
        }
        return true;
    }

    // GET-TEST-REPORT
    // 
    if (pMSG->hasValString(1, "GET-TEST-REPORT")) {
        int n = 1;
        String val2 = pMSG->getValString(2);
        String val3 = pMSG->getValString(3);
        if (!val3.equals("")) { n = val3.toInt();}
        for (int i = 0; i < n; i++) {
            pMSG->sendMsgResponse(val2);
        }
        return true;
    }

    return false;
}

// ----------------------------------------------------
// CALLERS INTERFACES

// pMSG INTERFACE
void Chemostat::handleAllMsgs(){

    // Serial.println(">>> Chemostat::handleAllMsgs <<<");

    // no cmd is a noop
    if (!this->pMSG->hasValidMsg()) { return; }

    // // Open response
    pMSG->openMsgResponse();

    // call myself
    if (this->handleMsg()) { 
        // close response
        pMSG->closeMsgResponse();
        return; 
    }

    // call all handlers
    for (int i = 0; i < CHEMOSTAT_HANDLERS_BUFFER_SIZE; i++) {
        if (_ALL_HANDLERS_BUFFER[i] == NULL){ break; }
        if (_ALL_HANDLERS_BUFFER[i]->handleMsg()) { 
            // close response
            pMSG->closeMsgResponse();
            return; 
        }
    }

    // fallback
    pMSG->sendMsgResponse(UNKNOWN_CMD_ERROR_TOKEN);
    
    // close response
    pMSG->closeMsgResponse();

}

void Chemostat::handleBlokingInit(const String& msg){
    this->pLOG->info("BLOCKING INIT by ", msg);

    // call myself
    this->onBlokingInit();

    // call all handlers
    for (int i = 0; i < CHEMOSTAT_HANDLERS_BUFFER_SIZE; i++) {
        if (_ALL_HANDLERS_BUFFER[i] == NULL){ break; }
        _ALL_HANDLERS_BUFFER[i]->onBlokingInit();
    }
}

void Chemostat::handleBlokingEnd(const String& msg){
    this->pLOG->info("BLOCKING ENDS by ", msg);

    // call myself
    this->onBlokingEnd();

    // call all handlers
    for (int i = 0; i < CHEMOSTAT_HANDLERS_BUFFER_SIZE; i++) {
        if (_ALL_HANDLERS_BUFFER[i] == NULL){ break; }
        _ALL_HANDLERS_BUFFER[i]->onBlokingEnd();
    }
}


// ----------------------------------------------------
// BLOCKING INTERFACE
void Chemostat::onBlokingInit(){;}
void Chemostat::onBlokingEnd(){;}

// ----------------------------------------------------
// ALL HANDLERS INTERFACE
void Chemostat::pushHandler(AbsHandler* h) {
    _pushHandler(_ALL_HANDLERS_BUFFER, h);
}

// ----------------------------------------------------
// SKETCH INTERFACE
void Chemostat::onsetup(){
    // Serial.println(">>> Chemostat::onsetup <<<");

    // ---------------------
    // CHEMOSTAT SETUP
    // noop for now

    // ---------------------
    // SETUP HANDLERS
    // Handlers
    for (int i = 0; i < CHEMOSTAT_HANDLERS_BUFFER_SIZE; i++) {
        if (_ALL_HANDLERS_BUFFER[i] == NULL){ break; }
        _ALL_HANDLERS_BUFFER[i]->onsetup();
    }

    // ---------------------
    // WELCOME
    printWelcome();
}

void Chemostat::printWelcome() {

    pSERIAL->newLine();
    pSERIAL->println(LINE_SEPARATOR);
    pSERIAL->println(" WELCOME TO CSC-CHEMOSTAT");
    pSERIAL->println(" info at https://github.com/CSC-Chemostat-DevTeam");
    pSERIAL->println(LINE_SEPARATOR);
    pSERIAL->newLine();

    this->sayHi();
    pSERIAL->newLine();
}

    
void Chemostat::onloop(){
    // Serial.println(">>> Chemostat::onloop <<<");

    // ---------------------
    // CHEMOSTAT ONLOOP
    // noop for now

    // ---------------------
    // ONLOOP HANDLERS
    // Handlers
    for (int i = 0; i < CHEMOSTAT_HANDLERS_BUFFER_SIZE; i++) {
        if (_ALL_HANDLERS_BUFFER[i] == NULL){ break; }
        _ALL_HANDLERS_BUFFER[i]->onloop();
    }
}

// ----------------------------------------------------
// Utils
void _pushHandler(AbsHandler* buffer[], AbsHandler* h) {
    for (int i = 0; i < CHEMOSTAT_HANDLERS_BUFFER_SIZE; i++) {
        if (buffer[i] != NULL){ continue; }
        buffer[i] = h;
        if (i+1 == CHEMOSTAT_HANDLERS_BUFFER_SIZE) { break; }
        buffer[i+1] = NULL;
        break;
    }
}