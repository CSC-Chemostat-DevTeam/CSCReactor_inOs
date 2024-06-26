// #include "Base/1_config.h"
// #include "Base/2_utils.h"
// #include "Base/3_StaticString.h"
// #include "Base/4_SDHandler.h"
// #include "Base/4_MsgHandler.h"
// #include "Base/4_SerialHandler.h"
// #include "Base/4_LogHandler.h"

// // ----------------------------------------------------
// // CONSTRUCTOR
// SDHandler::SDHandler(Chemostat* Ch) :
//     AbsHandler(
//         /* Chemostat */ Ch
//     ){
//     this->_LINE_BUFFER = StaticString();
// }


// // ----------------------------------------------------
// // SKETCH INTERFACE
// void SDHandler::onsetup() {
//     // TODO: This is a fatal error, do ErrorHandler
//     // TODO: Add proper printing stuff
//     // TODO: Add enable stuff

//     Serial.print("Initializing SD card...");

//     // Pin handling
//     pinMode(SD_CS_PIN, OUTPUT);

//     // see if the card is present and can be initialized:
//     if (!SD.begin(SPI_QUARTER_SPEED, SD_CS_PIN)) {
//         Serial.println("Card failed, or not present");
//         delay(3000);
//         this->onsetup();
//         // Error just if enable
//         // if (this->isEnable()) { 
//         //     // TODO: Add ERROR INTERFACE ex: SD logging + led signal + soud + Serial log
            
//         //     // if (DEV_MODE) {
//         //     //     Serial.println("DEV MODE: card initialized.");
//         //     // } else {
//         //         Serial.println("Stoping till fix");
//         //         while (1);
//         //     // }
//         // }
//     } else {
//         Serial.println("card initialized.");
//     }
// }

// void SDHandler::onloop() {

// }


// // -------------------------
// // HANDLE MSG INTERFACE
// boolean SDHandler::handleMsg() {

//     MsgHandler* const pMSG = this->Ch->pMSG;

//     // Check target code
//     if (!pMSG->hasValString(0, "SD")) { return false; }

//     // CHECK WRITE & READ
//     // Example: $SD:CHECK-WR%
//     if (pMSG->hasValString(1, "CHECK-WR")) {
//         pMSG->sendMsgResponse("write_test_check", this->checkReadWrite());
//         return true;
//     }

//     // DELETE
//     // Example: $SD:DELETE:FILE%
//     if (pMSG->hasValString(1, "DELETE")) {
//         this->remove(pMSG->getValString(2));
//         return true;
//     }

//     // .fseventsd

//     return false;
// }

// // ----------------------------------------------------
// // _DEV INTERFACE
// String SDHandler::getClassName() { return "SDHandler"; }
// void SDHandler::sayHi() { 
//     AbsHandler::sayHi(); // Parent
//     Ch->pSERIAL->println(TAB, "SD_CS_PIN: ", SD_CS_PIN);
//     Ch->pSERIAL->println(TAB, "SD_MOSI_PIN: ", SD_MOSI_PIN);
//     Ch->pSERIAL->println(TAB, "SD_MISO_PIN: ", SD_MISO_PIN);
//     Ch->pSERIAL->println(TAB, "SD_SCK_PIN: ", SD_SCK_PIN);
// }


// // ----------------------------------------------------
// // SD INTERFACE

// /// ----------------------------------------------------
// /// LINE FILE INTERFACE
// String SDHandler::readLineFile(String file, String onerr) {
//     // reset
//     this->_LINE_BUFFER.reset();

//     // open the file for reading:
//     this->exists(file); // TODO: fix this, I'm using it only for logging
//     File IO = SD.open(file, FILE_READ);
//     char c = '0';
//     if (IO) {
//         while(IO.available()){
//             if (this->_LINE_BUFFER.isFull()) {
//                 this->Ch->pLOG->dev("Single line file too long!!!, file: ", file);
//                 this->_LINE_BUFFER.reset();
//                 IO.close(); delay(5);
//                 return onerr;
//             }
//             c = IO.read(); delay(5);
//             if (c == '\n') { break; } // end of line
//             this->_LINE_BUFFER.push(c);
//         }
//         String str = this->_LINE_BUFFER.toString();
//         str.trim();
//         IO.close(); delay(5);
//         this->Ch->pLOG->dev("Reading succeed!!!, file: ", file);
//         return str;
//     }
//     // TO ERR HANDLE
//     this->Ch->pLOG->dev("Reading failed!!!, file: ", file);
//     IO.close(); delay(5);
//     return onerr;
// }

// String SDHandler::getLineString() {
//     String str = this->_LINE_BUFFER.toString();
//     str.trim();
//     return str;
// }

// // TRIM line
// boolean SDHandler::writeLineFile(String file, String line) {
//     line.trim();
//     // open the file for reading:
//     this->remove(file);
//     // TODO: make this stable (on DataHandle interface)
//     File IO = SD.open(file, FILE_WRITE);
//     if (IO) {
//         IO.print(line); delay(5);
//         IO.close(); delay(5);
//         this->Ch->pLOG->dev("Writing succeed!!!, file: ", file);
//         return true;
//     } else {
//         this->Ch->pLOG->error("Writing failed!!!, file: ", file);
//         IO.close(); delay(5);
//         return false;
//     };
// }

// /// ----------------------------------------------------
// /// HARDWARE TEST INTERFACE
// // - check file write and read
// boolean SDHandler::checkReadWrite() {
//     this->remove(SD_TEST_FILE_PATH);
//     if (this->exists(SD_TEST_FILE_PATH)) { return false; }
//     String token = String(millis());
//     if (!writeLineFile(SD_TEST_FILE_PATH, token)) {return false; }
//     if (!this->exists(SD_TEST_FILE_PATH)) { return false; }
//     String line = readLineFile(SD_TEST_FILE_PATH, "_");
//     this->remove(SD_TEST_FILE_PATH);
//     return line.equals(token);
// }

// /// ----------------------------------------------------
// /// FILE UTILS

// boolean SDHandler::exists(String file) {
//     boolean e = SD.exists(file); delay(5);
//     this->Ch->pLOG->dev("SD.exists(\"", file, "\") = ", e);
//     return e;
// }

// void SDHandler::mkdir(String file) {
//     SD.mkdir(file); delay(5);
//     this->Ch->pLOG->dev("SD.mkdir(\"", file, "\")");
//     this->exists(file); // check
// }

// void SDHandler::remove(String file) {
//     SD.rmdir(file); delay(5);
//     SD.remove(file); delay(5);
//     this->Ch->pLOG->dev("SD.remove(\"", file, "\")");
//     this->exists(file); // check
// }

