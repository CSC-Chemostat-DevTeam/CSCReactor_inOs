#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/3_Chemostat.h"
#include "Base/3_CmdHandler.h"
#include "Base/3_AbsSDHandler.h"
#include "Base/3_VirtualSDHandler.h"
#include "Base/3_SerialHandler.h"

// ----------------------------------------------------
// CONSTRUCTOR
VirtualSDHandler::VirtualSDHandler(Chemostat* Ch) :
    AbsSDHandler(Ch){
}

// boolean CmdHandler::request(String req) {

//     // TODO: add bloking interface
//     SerialHandler* pSERIAL = this->Ch->pSERIAL;

//     // request
//     String req_str = _request_str(req);
//     pSERIAL->println("\n", req_str);

//     // wait Confirmation
//     String req_hash = String(_request_hash(req_str));
//     boolean ko_flag = false;
//     for (int i = 0; i < 3; i++) {
//         this->tryReadCmd(CMD_INPUT_TIMEOUT);
//         if (this->hasValidCmd()) {
//             if (!this->hasKey("RQCONF")) { return false; }
//             ko_flag = this->getCmdVal().equals(req_hash);
//             this->reset(); // If RQCONF reset
//             break;
//         }
//     }

//     if (ko_flag) {
//         pSERIAL->println(">>> REQUEST: CONFIRMED, req: ", req, ", hash: ", req_hash, " <<<");
//     } else {
//         pSERIAL->println(">>> REQUEST: FAILED, req: ", req, ", hash: ", req_hash, " <<<");
//     }

//     return ko_flag;
// }

// ----------------------------------------------------
// BASIC SD INTERFACE (JULIA LIKE)
boolean VirtualSDHandler::isFile(String file){

    // TODO: add bloking interface

    SerialHandler* pSERIAL = this->Ch->pSERIAL;
    CmdHandler* pCMD = this->Ch->pCMD;

    // Send request
    String req = "SD-ISFILE:" + file;
    if (!pCMD->request(req)) { return false; }

    // wait response
    boolean _isfile = false;
    for (int i = 0; i < 3; i++) {
        pCMD->tryReadCmd(CMD_INPUT_TIMEOUT);
        if (pCMD->hasValidCmd()) {
            if (!pCMD->hasKeyPrefix("RQRESP")) { return false; }
            if (!pCMD->hasKeySuffix("SD-ISFILE")) { return false; }
            _isfile = pCMD->getCmdVal().equals("1");
            pCMD->reset(); // If RQCONF reset
            break;
        }
    }

    return _isfile;
}
boolean VirtualSDHandler::isDir(String file){
    return false;
}

// boolean VirtualSDHandler::mkDir(String file);
// boolean VirtualSDHandler::rm(String file);

// // [Blocking]
// // Read a file and print it
// boolean VirtualSDHandler::readToSerial(String file);

// // Read the first line of a file and returns it
// // It returns an empty string if the file is not present
// String VirtualSDHandler::readFirstLine(String file);

// // Overwrite the first line of a file
// boolean VirtualSDHandler::overwriteFirstLine(String file, String line);

// // Add a new line to a file
// boolean VirtualSDHandler::appendNewLine(String file, String line);