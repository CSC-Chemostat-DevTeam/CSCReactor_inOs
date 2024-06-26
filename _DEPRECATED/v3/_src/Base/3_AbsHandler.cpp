#include "Base/3_AbsHandler.h"
#include "Base/3_CmdHandler.h"

// foward declare

// ----------------------------------------------------
// CONSTRUCTORS
AbsHandler::AbsHandler(Chemostat* Ch){
    // Serial.println(">>> At AbsHandler::AbsHandler <<<");
    this->Ch = Ch;
    this->enable = false;
    this->enable0 = false;
}

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

// TODO: Use high level function for CMD response printing, or printing in general

// ----------------------------------------------------
// CMD INTERFACE
boolean AbsHandler::execCmd(){

    // Serial.println(">>> At AbsHandler::execCmd <<<");

    CmdHandler* const pCMD = this->Ch->pCMD;

    // --------------------
    // Suffixes

    /// --------------------
    /// ENABLE INTERFACE
    if (pCMD->hasKeySuffix("GET-EN")) {
        pCMD->response("enable: ", this->_enable());
        return true;
    }
    if (pCMD->hasKeySuffix("SET-EN")) {
        this->Enable(pCMD->getCmdVal().toInt() != 0);
        pCMD->response("enable: ", this->_enable());
        return true;
    }
    // enable0
    if (pCMD->hasKeySuffix("GET-EN0")) {
        pCMD->response("enable0: ", this->_enable0());
        return true;
    }
    if (pCMD->hasKeySuffix("SET-EN0")) {
        this->Enable0(pCMD->getCmdVal().toInt() != 0);
        pCMD->response("enable0: ", this->_enable0());
        return true;
    }
    return false;
}

// ----------------------------------------------------
// TEST INTERFACE
void AbsHandler::sayHi() {
    Serial.print("Hi from AbsHandler ");
    Serial.println((unsigned int)this);
}