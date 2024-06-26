#include "Base/2_utils.h"
#include "Base/4_AbsHandler.h"
#include "Base/4_MsgHandler.h"


// ----------------------------------------------------
// CONSTRUCTORS
AbsHandler::AbsHandler(Chemostat* Ch){
    // Serial.println(">>> At AbsHandler::AbsHandler <<<");
    this->Ch = Ch;
    this->enable = false;
    this->enable0 = false;
}

// ----------------------------------------------------
// BLOCKING INTERFACE
void AbsHandler::onBlokingInit(){;}
void AbsHandler::onBlokingEnd(){;}

// ----------------------------------------------------
// ENABLE INTERFACE
void AbsHandler::Enable(boolean flag){
    // Serial.println(">>> At AbsHandler::Enable <<<");
    this->enable = flag;
}
void AbsHandler::Enable0(boolean flag){
    // Serial.println(">>> At AbsHandler::Enable <<<");
    this->enable0 = flag;
}
// "privates"
boolean AbsHandler::_enable(){
    return this->enable;
}
boolean AbsHandler::_enable0(){
    return this->enable0;
}

boolean AbsHandler::isEnable(){
    // Serial.println(">>> At AbsHandler::isEnable <<<");
    if (!this->enable) { return false; }
    if (!this->enable0) { return false; }
    return true;
}

// ----------------------------------------------------
// SKETCH INTERFACE
void onsetup() {;}
void onloop() {;}

// // ----------------------------------------------------
// MSG INTERFACE
boolean AbsHandler::handleMsg(){

    // Serial.println(">>> At AbsHandler::handleMsg <<<");

    MsgHandler* const pMSG = this->Ch->pMSG;

    // --------------------
    // CMDS
    // All AbsHandler are placed on Val1 so Val0 is for subclasses

    // if (pMSG->hasValString(1, "ECHO")) {

    /// --------------------
    /// ENABLE INTERFACE
    // Example $X:GET-EN:%
    if (pMSG->hasValString(1, "GET-EN")) {
        pMSG->sendMsgResponse("enable", this->_enable());
        return true;
    }
    // Example $X:SET-EN:1%
    if (pMSG->hasValString(1, "SET-EN")) {
        this->Enable(pMSG->hasValString(2, "1"));
        pMSG->sendMsgResponse("enable", this->_enable());
        return true;
    }
    // enable0
    // Example $X:GET-EN0:%
    if (pMSG->hasValString(1, "GET-EN0")) {
        pMSG->sendMsgResponse("enable0", this->_enable0());
        return true;
    }
    // Example $X:SET-EN0:1%
    if (pMSG->hasValString(1, "SET-EN0")) {
        this->Enable0(pMSG->hasValString(2, "1"));
        pMSG->sendMsgResponse("enable0", this->_enable0());
        return true;
    }
    return false;
}

// ----------------------------------------------------
// _DEV INTERFACE
String AbsHandler::getClassName() { return "AbsHandler"; }
void AbsHandler::sayHi() {
    Ch->pSERIAL->println("Hi from ", this->getClassName(), " *", (unsigned int)this);
}