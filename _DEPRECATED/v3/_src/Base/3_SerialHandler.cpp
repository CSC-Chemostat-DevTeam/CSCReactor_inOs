#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/3_SerialHandler.h"

// ----------------------------------------------------
// CONSTRUCTOR
SerialHandler::SerialHandler(Chemostat* Ch) : 
    AbsHandler(
        /* Chemostat */ Ch
    ){
    this->baud_rate = IO_BAUDRATE; // [DEFAULT]
    this->vlevel = 100; // TODO: create [DEFAULT]
}

// ----------------------------------------------------
// SKETCH INTERFACE
void SerialHandler::onsetup(){ 
    // Create a Serial System?
    Serial.begin(this->baud_rate);
    while (!Serial) {
        ;  // wait for serial port to connect. Needed for native USB port only
    }
    this->info("Serial connected, boud rate: ", this->baud_rate);
}

void SerialHandler::onloop(){ ; }

// ----------------------------------------------------
// PRINT INTERFACE

// See header

// ----------------------------------------------------
// SERIAL LOG INTERFACE
void SerialHandler::setVLevel(byte vlv) { this->vlevel = vlv; }
byte SerialHandler::getVLevel() { return this->vlevel; }
void SerialHandler::setBaudRate(unsigned long brate) { this->baud_rate = brate; }
unsigned long SerialHandler::getBaudRate() { return this->baud_rate; }