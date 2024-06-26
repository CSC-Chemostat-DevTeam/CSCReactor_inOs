#include "Base/1_config.h"

#include "4_sd_subsystem.h"
#include "4_bottom_subsystem.h"
#include "4_stirrel_subsystem.h"
#include "4_cmd_subsystem.h"
#include "4_do_subsystem.h"
#include "4_pump_subsystem.h"
#include "4_program_subsystem.h"
#include "4_Tcontrol_subsystem.h"
#include "4_datalogger_subsystem.h"
#include "4_uploader_subsystem.h"

// SUBSYSTEMS
extern SDSubsystem SDSYS;
extern CmdSubsystem CMDSYS;
extern StirrelSubsystem STIRSYS;
extern BottomSubsystem BTTSYS;
extern DOSubsystem DOSYS;
extern PumpSubsystem PUMPSYS;
extern ProgramSubsystem PROGSYS;
extern TControlSubsystem TCONTRLSYS;
extern DataLoggerSubsystem LOGGERSYS;
extern UploaderSubsystem UPLOADERSYS;

// -------------------------------------------------------
// BOTTOM INTERFACE
// register here all actions to be taken at bottom pressed
void onBottomPressedI() {
    
    // BTTSYS group
    if (BTTSYS.timer.istime(TIMER_FIXED_MODE)) {
        BTTSYS.timer.set_next(TIMER_ROLLING_MODE);
        
        // onBottomPressed
        BTTSYS.onBottomPressed();
        // SDSYS.onBottomPressed();
        // CMDSYS.onBottomPressed();
        STIRSYS.onBottomPressed();
        BTTSYS.onBottomPressed();
        DOSYS.onBottomPressed();
        PUMPSYS.onBottomPressed();
        TCONTRLSYS.onBottomPressed();
        // UPLOADERSYS.onBottomPressed();
        // LOGGERSYS.onBottomPressed();
    }
}

// -------------------------------------------------------
// BLOKING INTERFACE
void beforeBlockI() {
    STIRSYS.beforeBlock();
}

void afterBlockI() {
    STIRSYS.afterBlock();
}

// ----------------------------------------------------
// CMD INTERFACE

void execCmdI() {

    // no cmd is a noop
    if (!CMDSYS.hasCmd()) { return; }

    String key = CMDSYS.getCmdKey();
    String val = CMDSYS.getCmdVal();

    // Execute all subsystems exec_cmds
    CMDSYS.execCmd(key, val);
    SDSYS.execCmd(key, val);
    STIRSYS.execCmd(key, val);
    DOSYS.execCmd(key, val);
    PUMPSYS.execCmd(key, val);
    PROGSYS.execCmd(key, val);
    TCONTRLSYS.execCmd(key, val);
    LOGGERSYS.execCmd(key, val);
    UPLOADERSYS.execCmd(key, val);
    
}


// ----------------------------------------------------
// PROGRAMMER INTERFACE

void onProgramUpdateI() {

    String chapterid = PROGSYS.getChapter();

    // SUBSYSTEMS
    LOGGERSYS.onProgramUpdate(chapterid);
    // UPLOADERSYS.onProgramUpdate(chapterid);
}

// ----------------------------------------------------
// LOGGER INTERFACE
void onLogWriteI(){

    // Execute all subsystems
    // CMDSYS.onLogWrite(LOGGERSYS);
    // SDSYS.onLogWrite(LOGGERSYS);
    // STIRSYS.onLogWrite(LOGGERSYS);
    // PUMPSYS.onLogWrite(LOGGERSYS);
    PROGSYS.onLogWrite(LOGGERSYS);
    DOSYS.onLogWrite(LOGGERSYS);
    TCONTRLSYS.onLogWrite(LOGGERSYS);
    LOGGERSYS.onLogWrite(LOGGERSYS);
    // UPLOADERSYS.onLogWrite(LOGGERSYS);
}

// ----------------------------------------------------
// STOP INTERFACE
void onStopI(){
    // Execute all subsystems
    // CMDSYS.onStop();
    SDSYS.onStop();
    STIRSYS.onStop();
    PUMPSYS.onStop();
    PROGSYS.onStop();
    DOSYS.onStop();
    TCONTRLSYS.onStop();
    LOGGERSYS.onStop();
    UPLOADERSYS.onStop();
}
