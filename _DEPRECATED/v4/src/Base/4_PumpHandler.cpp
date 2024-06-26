// #include "Base/1_config.h"
// #include "Base/2_utils.h"
// #include "Base/4_PumpHandler.h"
// #include "Base/4_MsgHandler.h"
// #include "Base/4_SerialHandler.h"

// // ----------------------------------------------------
// // CONSTRUCTOR
// PumpHandler::PumpHandler(Chemostat* Ch) : 
//     AbsHandler(
//         /* Chemostat */ Ch
//     ){
//     this->pwd1 = PUMP_DIR1_PWD_DFLT_VAL;
//     this->pwd2 = PUMP_DIR2_PWD_DFLT_VAL;
// }

// // ----------------------------------------------------
// // SKETCH INTERFACE
// void PumpHandler::onsetup() {
//     pinMode(PUMP_DIR1_PIN, OUTPUT);
//     pinMode(PUMP_DIR2_PIN, OUTPUT);
//     analogWrite(PUMP_DIR1_PIN, 0);
//     analogWrite(PUMP_DIR2_PIN, 0);
// }
// void PumpHandler::onloop() {;}

// // ----------------------------------------------------
// // _DEV INTERFACE
// String PumpHandler::getClassName() { return "PumpHandler"; }
// void PumpHandler::sayHi() { 
//     AbsHandler::sayHi(); // Parent
//     Ch->pSERIAL->println(TAB, "dir1_pin: ", PUMP_DIR1_PIN);
//     Ch->pSERIAL->println(TAB, "dir1_pwd: ", this->pwd1);
//     Ch->pSERIAL->println(TAB, "dir2_pin: ", PUMP_DIR2_PIN);
//     Ch->pSERIAL->println(TAB, "dir2_pwd: ", this->pwd2);
// }


// // ----------------------------------------------------
// // BLOCKING INTERFACE
// void onBlokingInit(){
//     analogWrite(PUMP_DIR1_PIN, 0);
//     analogWrite(PUMP_DIR2_PIN, 0);
// }

// // -------------------------
// // HANDLE MSG INTERFACE
// boolean PumpHandler::handleMsg() {

//     MsgHandler* const pMSG = this->Ch->pMSG;

//     // Check target code
//     if (!pMSG->hasValString(0, "PUMP")) { return false; }

//     // Example: $PUMP:PULSE!:1:500%
//     if (pMSG->hasValString(1, "PULSE!")) {
//         int d = pMSG->getValString(2).toInt();
//         int t = pMSG->getValString(3).toInt();
//         if (t == 0) { t = PUMP_PULSE_TIME_DFLT_VAL; }
//         this->pumpPulse(d, t);
//         pMSG->sendMsgResponse("PUMP-PULSE!", d, t);
//         return true;
//     }

//     // Example: $PUMP:PWD:1:250%
//     if (pMSG->hasValString(1, "PWD")) {
//         int d = pMSG->getValString(2).toInt();
//         int pwd = pMSG->getValString(3).toInt();
//         if (d == 1){
//             this->pwd1 = pwd;
//             pMSG->sendMsgResponse("pwd1", this->pwd1);
//         } else {
//             this->pwd2 = pwd;
//             pMSG->sendMsgResponse("pwd2", this->pwd2);
//         }
//         return true;
//     }

//     return false;
// }


// // ----------------------------------------------------
// // LED INTERFACE
// // BLOCKING
// void PumpHandler::pumpPulse(int d, int t){
//     this->Ch->handleBlokingInit("pumpPulse");
//     analogWrite(PUMP_DIR1_PIN, 0);
//     analogWrite(PUMP_DIR2_PIN, 0);
//     if (d == 1) { analogWrite(PUMP_DIR1_PIN, this->pwd1); }
//     if (d == 2) { analogWrite(PUMP_DIR2_PIN, this->pwd2); }
//     delay(t);
//     analogWrite(PUMP_DIR2_PIN, 0);
//     analogWrite(PUMP_DIR1_PIN, 0);
//     this->Ch->handleBlokingEnd("pumpPulse");
// }

// void PumpHandler::pumpOff(){
//     analogWrite(PUMP_DIR1_PIN, 0);
//     analogWrite(PUMP_DIR2_PIN, 0);
// }