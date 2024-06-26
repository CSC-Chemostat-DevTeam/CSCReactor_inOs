#include <Arduino.h>

#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/3_CmdHandler.h"
#include "Base/3_SerialHandler.h"
#include "Base/3_Chemostat.h"

// ----------------------------------------------------
// CONSTRUCTOR
Chemostat::Chemostat() {
    
    // Serial.println(">>> At Chemostat::Chemostat <<<");

    // HANDLERS
    this->pCMD = new CmdHandler(this); // TODO: [HEAP] Check proper free/delete
    this->pSERIAL = new SerialHandler(this); // TODO: [HEAP] Check proper free/delete
    
    // CALLERS INTERFACES
    /// CMD INTERFACE
    this->_CMD_HANDLERS_BUFFER[0] = NULL;
    this->pushCmdHandler(this->pCMD);

}

// ----------------------------------------------------
// CMD INTERFACE
boolean Chemostat::execCmd() {

    CmdHandler* const pCMD = this->pCMD;

    // EQUAL
    if (pCMD->hasKey("TEST-CMD")) {
        pCMD->response("Hi from Chemostat ", (int) this);
        return true;
    }

    // Prefix Depedent
    if (pCMD->hasKeyPrefix("CH-")) { return false; }

    return false;
}

// ----------------------------------------------------
// CALLERS INTERFACES

// pCMD INTERFACE
void Chemostat::execAllCmd(){

    // Serial.println(">>> Chemostat::execAllCmd <<<");
    CmdHandler* const pCMD = this->pCMD;

    // no cmd is a noop
    if (!this->pCMD->hasValidCmd()) { return; }

    // Open response
    pCMD->open_response(); 

    // call myself
    if (this->execCmd()) { 
        // close response
        pCMD->close_response(); 
        return; 
    }

    // call handlers
    for (int i = 0; i < HANDLERS_BUFFER_SIZE; i++) {
        if (_CMD_HANDLERS_BUFFER[i] == NULL){ break; }
        if (_CMD_HANDLERS_BUFFER[i]->execCmd()) { 
            // close response
            pCMD->close_response(); 
            return; 
        }
    }

    // fallback
    pCMD->response("ERROR, UNKNOWN COMMAND");
    // close response
    pCMD->close_response();

}

void Chemostat::pushCmdHandler(AbsHandler* h) {
    for (int i = 0; i < HANDLERS_BUFFER_SIZE; i++) {
        if (_CMD_HANDLERS_BUFFER[i] != NULL){ continue; }
        _CMD_HANDLERS_BUFFER[i] = h;
        if (i+1 == HANDLERS_BUFFER_SIZE) { break; }
        _CMD_HANDLERS_BUFFER[i+1] = NULL;
        break;
    }
}

// ----------------------------------------------------
// SKETCH INTERFACE
void Chemostat::onsetup(){
    // Serial.println(">>> Chemostat::onsetup <<<");

    // ---------------------
    // CHEMOSTAT SETUP

    // ---------------------
    // SETUP HANDLERS

    this->pCMD->onsetup();
    this->pSERIAL->onsetup();

    // ---------------------
    // BANNER
    pSERIAL->println("");
    pSERIAL->println("----------------------");
    pSERIAL->println(" WELCOME TO CSC-CHEMOSTAT");
    pSERIAL->println(" info at https://github.com/josePereiro/CSC_chemostat_board");
    pSERIAL->println("----------------------");
    pSERIAL->println("");
}
    
void Chemostat::onloop(){
    // Serial.println(">>> Chemostat::onloop <<<");
    
    // CHEMOSTAT ONLOOP

    // CALL HANDLERS ONLOOPS
    this->pCMD->onloop();
    this->pSERIAL->onloop();
}