#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/3_Timer.h"

#include "4_sd_subsystem.h"
#include "4_cmd_subsystem.h"
#include "4_program_subsystem.h"
#include "4_datalogger_subsystem.h"
#include "5_interfaces.h"

// SUBSYSTEMS

// ----------------------------------------------------
// CONSTRUCTOR
ProgramSubsystem::ProgramSubsystem() :
    SubSystem(
        /* enable */ true, 
        /* enable0 */ PROGRAMER_INCLUDE_FLAG_DFLT_VAL
    ){
    this->progress = 0;
    this->jumpto = "";
    this->jumpat = 0;
    this->progress_t0 = millis();
    this->chapterid = "";
    this->up_timer = Timer(PROGRAMMER_UP_TIME, TIMER_ROLLING_MODE);
}

// ----------------------------------------------------
// TODO: Create a default program
// TODO: Create an interface to set up a program
// Add an END chapter (stop all)

// ----------------------------------------------------
// SKETCH INTERFACE

void ProgramSubsystem::onsetup(){
    ;
}

void ProgramSubsystem::onloop(){

    if (!this->isEnable()) { return; }
    if (!this->up_timer.istime()) { return; }

    // Resolve chapter
    this->resolveChapter();

    // Update chapter program
    // TODO

    // callback
    onProgramUpdateI();
}

// SD -> RAM
void ProgramSubsystem::resolveChapter() {

    // Serial.println("---------");

    // Locals
    String fn;

    // read MAIN
    fn = "MAIN";
    String chapid0 = _sd_readLineFile(fn, "_");
    if (chapid0.equals("_")) { return; }
    
    // read READ PROGRESS
    fn = "PROGRESS";
    long progress0 = _sd_readLineFile(fn, "-1").toDouble();
    if (progress0 == -1) { return; }

    long jumpat;
    String chapid1;
    while (1) {
        // JUMPAT
        // read READ PROGRESS
        fn = chapid0 + "/JUMPAT";
        jumpat = _sd_readLineFile(fn, "-1").toDouble();
        if (jumpat == -1) { return; }
        
        // JUMPTO
        // read READ PROGRESS
        fn = chapid0 + "/JUMPTO";
        chapid1 = _sd_readLineFile(fn, "");
        if (chapid1.equals("")) { 
            SD.remove(fn);
            return;
        }

        // CHECK FOR JUMPS OR BREAK
        if (progress0 >= jumpat) {
            chapid0 = chapid1;
        } else { 
            break; 
        }
    }

    // Sync Programmer
    this->chapterid = chapid0;
    // TODO: add a controler for updating the progress
    this->progress = progress0 + (millis() - this->progress_t0);
    this->progress_t0 = millis();
    _sd_writeLineFile("PROGRESS", String(this->progress));
    this->jumpto = chapid1; // next chapter
    this->jumpat = jumpat; // next checkpoint
}

String ProgramSubsystem::getChapter(){ return this->chapterid; }
String ProgramSubsystem::getJumpTo(){ return this->jumpto; }
long ProgramSubsystem::getProgress(){ return this->progress; }
long ProgramSubsystem::getJumpAt(){ return this->jumpat; }


// ----------------------------------------------------
// CMD INTERFACE
boolean ProgramSubsystem::execCmd(String& key, String& val){

    // get cmd
    String cmd = _parseCmdString(key, "PROG-");
    if (cmd.equals("")) {return false; }

    // Call parent
    if (this->SubSystem::execCmd(cmd, val)) { return true; }

    // resolve
    if (cmd.equals("RESOLVE")) {
        this->resolveChapter();
        Serial.print("chapter: ");
        Serial.println(this->getChapter());
        Serial.print("progress: ");
        Serial.println(this->getProgress());
        Serial.print("jumpat: ");
        Serial.println(this->getJumpAt());
        Serial.print("jumpto: ");
        Serial.println(this->getJumpTo());
        return true;
    }

    return false;
}

// ----------------------------------------------------
// LOGGER INTERFACE
// Concurrent
void ProgramSubsystem::onLogWrite(DataLoggerSubsystem& logger){
    // Temperature
    logger.appendHeader("Progress");
    logger.appendValue(String(this->getProgress()));
    return;
}

// ----------------------------------------------------
// STOP INTERFACE
void ProgramSubsystem::onStop(){
    ;
}