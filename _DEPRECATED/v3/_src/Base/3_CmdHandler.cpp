#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/3_KVReader.h"
#include "Base/3_CmdHandler.h"
#include "Base/3_SerialHandler.h"

// Interfaces will be called using the Chemostat object

// ----------------------------------------------------
// CONSTRUCTOR
CmdHandler::CmdHandler(Chemostat* Ch) :
    AbsHandler(
        /* Chemostat */ Ch
    ){
    // Serial.println(">>> At CmdHandler::CmdHandler <<<");
    this->kvreader = KVReader();
    this->respcount = 0;
}

// ----------------------------------------------------
// SKETCH INTERFACE
void CmdHandler::onsetup(){ ; }

void CmdHandler::onloop(){
    
    // Serial.println(">>> CmdHandler::onloop <<<");

    // read cmd
    if (Serial.available() > 0) {
        this->tryReadCmd(CMD_INPUT_TIMEOUT);
    }

    // exec all handlers commands
    this->Ch->execAllCmd();

    // Reset reader
    this->reset(); // reset reader
}

// ----------------------------------------------------
// CMD INTERFACE

/// -------------------------
/// EXEC CMD
boolean CmdHandler::execCmd() {

    CmdHandler* const pCMD = this->Ch->pCMD;

    // Unique
    if (pCMD->hasKey("ECHO")) {
        int n = 1;
        if (!pCMD->getCmdVal1().equals("")) {
            n = getCmdVal1().toInt();
        }
        for (int i = 0; i < n; i++) {
            pCMD->response(pCMD->getCmdVal0());
        }
        return true;
    }

    // Prefix Depedent
    if (pCMD->hasKeyPrefix("CMD-")) { return false; }

    // Call parent
    // if (this->AbsHandler::execCmd()) { return true; }

    return false;

}

/// -------------------------
/// RECEIVE CMD
boolean CmdHandler::hasKey(const String& str) {
    return this->getCmdKey().equals(str);
}

boolean CmdHandler::hasKeyPrefix(const String& prefix) {
    return this->getCmdKey().startsWith(prefix);
}

boolean CmdHandler::hasKeySuffix(const String& suffix) {
    return this->getCmdKey().startsWith(suffix);
}

unsigned int CmdHandler::cmdhash(){
    return this->kvreader.hash();
}

void CmdHandler::reset(){
    this->kvreader.reset(); // reset reader
}

// If cmd buffers are empty, listen for incoming commands for 'tout' time;
void CmdHandler::tryReadCmd(unsigned long tout){

    // Serial.println(">>> CmdHandler::tryReadCmd <<<");

    // If non reset called, skip
    if (this->hasValidCmd()) { return; }

    // local
    SerialHandler* pSERIAL = this->Ch->pSERIAL;
    long t0 = millis();
    while (1) { 
        if (millis() - t0 > tout) { break; } // TIME OUT
        while (pSERIAL->available() > 0) {
            // parse char
            char c = pSERIAL->read();
            boolean ok_flag = this->kvreader.parseChar(c);
            if (!ok_flag) { reset(); break; }
            delay(1); // Stability?
        } 
        if (this->hasValidCmd()) { break; }
    }
}

/// -------------------------
/// RESPONSE INTERFACE
void CmdHandler::open_response(){
    this->Ch->pSERIAL->println(
        "\n"
        ">>> ", "CMD RECEIVED ", 
        "[", millis(), "-", this->cmdHash(), "] ",
        this->cmdKvString(), " >>>"
    );
}

void CmdHandler::close_response(){
    this->Ch->pSERIAL->println(
        "<<< ", 
        "CMD FINISHED ",
        "[", millis(), "-", this->cmdHash(), "-", this->respcount, "] ",
        this->cmdKvString(),
        " <<<"
    );
    this->respcount = 0;
}

/// ----------------------------------------------------
/// REQUEST INTERFACE

String _request_str(String& req) { return "$$$ " + req + " $$$"; }
unsigned int _request_hash(String& req) { return crc16_hash(0, req); }

// [BLOKING]
// This will wait for a confirmation
// If a new CMd arrive that is not a confirmation it returns
// without reseting the reader
boolean CmdHandler::request(String req) {

    // TODO: add bloking interface
    SerialHandler* pSERIAL = this->Ch->pSERIAL;

    // request
    String req_str = _request_str(req);
    pSERIAL->println("\n", req_str);

    // wait Confirmation
    String req_hash = String(_request_hash(req_str));
    boolean ko_flag = false;
    for (int i = 0; i < 3; i++) {
        this->tryReadCmd(CMD_INPUT_TIMEOUT);
        if (this->hasValidCmd()) {
            if (!this->hasKey("RQCONF")) { return false; }
            ko_flag = this->getCmdVal().equals(req_hash);
            this->reset(); // If RQCONF reset
            break;
        }
    }

    if (ko_flag) {
        pSERIAL->println(">>> REQUEST: CONFIRMED, req: ", req, ", hash: ", req_hash, " <<<");
    } else {
        pSERIAL->println(">>> REQUEST: FAILED, req: ", req, ", hash: ", req_hash, " <<<");
    }

    return ko_flag;
}

// ----------------------------------------------------
// KVReader INTERFACE

boolean CmdHandler::hasValidCmd(){
    return this->kvreader.valid_input;
}

unsigned int CmdHandler::cmdHash(){
    return this->kvreader.hash();
}

String CmdHandler::cmdKvString(){
    return this->kvreader.kvString();
}

String CmdHandler::getCmdKey() {
    return this->kvreader.getKey();
}

String CmdHandler::getCmdVal() {
    return this->kvreader.getVal();
}
String CmdHandler::getCmdVal0() {
    return this->kvreader.getVal0();
}
String CmdHandler::getCmdVal1() {
    return this->kvreader.getVal1();
}
String CmdHandler::getCmdVal2() {
    return this->kvreader.getVal2();
}
