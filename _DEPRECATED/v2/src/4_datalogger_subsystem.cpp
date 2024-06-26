#include "Base/1_config.h"
#include "4_datalogger_subsystem.h"
#include "4_sd_subsystem.h"
#include "4_cmd_subsystem.h"
#include "5_interfaces.h"

// ----------------------------------------------------
// CONSTRUCTOR
// TODO: Split into uploader and logger
DataLoggerSubsystem::DataLoggerSubsystem() :
    SubSystem(
        /* enable */ true, 
        /* enable0 */ DATALOGGER_INCLUDE_FLAG_DFLT_VAL
    ){
    // logger
    this->wchapter = "";
    this->wheader = ""; // TODO: use STATIC STRING
    this->wline = ""; // TODO: use STATIC STRING
    this->log_timer = Timer(LOGGER_LOG_FREC, TIMER_ROLLING_MODE);
}

// ----------------------------------------------------
// SKETCH INTERFACE
void DataLoggerSubsystem::onsetup(){

}

void DataLoggerSubsystem::onloop(){
    
    if (!this->log_timer.istime()) { return; }

    // devmode
    if (DEV_MODE) {
        this->wchapter = "DEV-CHAPTER";
    }
    
    if (this->wchapter.equals("")) { return; }
    
    // empty
    this->wheader = "";
    this->wline = "";

    // collect
    onLogWriteI();

    // write
    // HEADER FILE
    String fn;
    fn = String(this->wchapter) + "/DATAHEADER";
    _sd_writeLineFile(fn, this->wheader);

    // DATA FILE
    fn = String(this->wchapter) + "/DATA";
    _sd_writeNewLine(fn, this->wline);

}

// ----------------------------------------------------
// CMD INTERFACE
boolean DataLoggerSubsystem::execCmd(String& key, String& val){
    // get cmd
    String cmd = _parseCmdString(key, "LOG-");
    if (cmd.equals("")) {return false; }

    // Call parent
    if (this->SubSystem::execCmd(cmd, val)) { return true; }

    return false;
}

// ----------------------------------------------------
// PROGRAM INTERFACE
void DataLoggerSubsystem::onProgramUpdate(String chapterid){
    this->wchapter = String(chapterid);
}

// ----------------------------------------------------
// LOGGER INTERFACE

void DataLoggerSubsystem::onLogWrite(DataLoggerSubsystem& logger){
    ;
}

void DataLoggerSubsystem::appendHeader(String header){
    this->wheader.concat(header);
    this->wheader.concat(DATALOGGER_SEPARATOR);
}

void DataLoggerSubsystem::appendValue(String val){
    this->wline.concat(val);
    this->wline.concat(DATALOGGER_SEPARATOR);
}

// ----------------------------------------------------
// STOP INTERFACE
void DataLoggerSubsystem::onStop(){
    ;
}