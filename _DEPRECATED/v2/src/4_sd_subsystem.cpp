#include <SD.h>
#include "Base/1_config.h"
#include "Base/3_StaticString.h"
#include "4_sd_subsystem.h"
#include "4_cmd_subsystem.h"
#include "5_interfaces.h"

// API
// download/upload: comunication with the PC
// read/write: comunication with the SD

// API 2
// pc_read/pc_write: comunication with the PC
// sd_read/sd_write: comunication with the SD

StaticString _SD_BUFFER = StaticString();

// ----------------------------------------------------
// CONSTRUCTOR
SDSubsystem::SDSubsystem() :
    SubSystem(
        /* enable */ true, 
        /* enable0 */ SD_INCLUDE_FLAG_DFLT_VAL
    ){
    this->loop_timer = Timer(SD_LOOP_ACTION_TIMER_FREC, TIMER_FIXED_MODE);
    this->ctask = ConcurrentTask();
    this->file = ""; // File for read/write
    this->line = ""; // Text line for read/write
}

// ----------------------------------------------------
// SKETCH INTERFACE
void SDSubsystem::onsetup(){
    Serial.print("Initializing SD card...");

    // see if the card is present and can be initialized:
    if (!SD.begin(SD_CS_PIN)) {
        Serial.println("Card failed, or not present");
        // Error just if enable
        if (this->isEnable()) { 
            // TODO: Add ERROR INTERFACE ex: SD led signal
            
            if (DEV_MODE) {
                Serial.println("DEV MODE: card initialized.");
            } else {
                Serial.println("Stoping till fix");
                while (1);
            }
        }
    } else {
        Serial.println("card initialized.");
    }
}

void SDSubsystem::onloop(){
    
    // check enable
    if (!this->isEnable()) { return; }

    // check if it is time
    if (!this->loop_timer.istime()) { return; }
}

// ----------------------------------------------------
// CMD INTERFACE
boolean SDSubsystem::execCmd(String& key, String& val){

    // get cmd
    String cmd = _parseCmdString(key, "SD-");
    if (cmd.equals("")) { return false; }

    // Call parent
    if (this->SubSystem::execCmd(cmd, val)) { return true; }

    if (cmd.equals("STATUS")) {
        // TODO: Print useful stuff here
        return true;
    }
    
    // args
    if (cmd.equals("SET-FILE")) {
        this->file=val;
        Serial.println(this->file);
        return true;
    }
    if (cmd.equals("SET-LINE")) {
        this->line=val;
        Serial.println(this->line);
        return true;
    }
    if (cmd.equals("GET-FILE")) {
        Serial.println(this->file);
        return true;
    }
    if (cmd.equals("GET-LINE")) {
        Serial.println(this->line);
        return true;
    }
    
    // file actions
    if (cmd.equals("WRITELINE")) {
        _sd_writeLineFile(this->file, this->line);
        return true;
    }
    if (cmd.equals("READLINE")) {
        this->line = _sd_readLineFile(this->file, "");
        Serial.println(this->line);
        return true;
    }
    if (cmd.equals("REMOVE")) {
        _sd_remove(this->file);
        return true;
    }
    if (cmd.equals("EXISTS")) {
        _sd_exists(this->file);
        return true;
    }
    if (cmd.equals("MKDIR")) {
        // re-open the file for reading:
        _sd_mkdir(this->file);
        return true;
    }
    return false;
}

// ----------------------------------------------------
// STOP INTERFACE
void SDSubsystem::onStop(){
    ;
}


// ----------------------------------------------------
// ERROR INTERFACE
// Blocking

byte SD_SETUP_FAILED_ERRCODE = 0;

void onError(byte errcode) {
    onStopI();
    if (errcode == SD_SETUP_FAILED_ERRCODE){
        // 
        
    } else {
        // unknow

    }
}

// ----------------------------------------------------
// SD INTERFACE

// ----------------------------------------------------
// Utils
boolean _sd_exists(String& file) {
    boolean e = SD.exists(file);
    Serial.print("SD.exists(");
    Serial.print(file);
    Serial.print(") = ");
    Serial.println(e);
    return e;
}

void _sd_remove(String& file) {
    if (_sd_exists(file)) {
        SD.rmdir(file);
        SD.remove(file);
        Serial.print("SD.remove(");
        Serial.print(file);
        Serial.println(")");
        _sd_exists(file); // check
    }
}

void _sd_mkdir(String& file) {
    if (!_sd_exists(file)) {
        Serial.print("SD.mkdir(");
        SD.mkdir(file);
        Serial.print(file);
        Serial.println(")");
        _sd_exists(file); // check
    }
}

// ----------------------------------------------------
// LINE FILE FORMAT

String _sd_readLineFile(String file, String onerr) {
    // reset
    _SD_BUFFER.reset();

    // open the file for reading:
    _sd_exists(file);
    File IO = SD.open(file, FILE_READ);
    char c = '0';
    if (IO) {
        while(IO.available()){
            if (_SD_BUFFER.isFull()) {
                Serial.print("File too long ");
                Serial.println(file);

                _SD_BUFFER.reset();
                IO.close();
                return onerr;
            }
            c = IO.read();
            if (c == '\n') { break; } // end of line
            _SD_BUFFER.push(c);
        }
    } else {
        Serial.print("Reading failed ");
        Serial.println(file);
        IO.close();
        return onerr;
    }
    String str = _SD_BUFFER.toString();
    str.trim();
    IO.close();
    return str;
}

// TODO: create a back up system, at leas for line files

// TRIM line
boolean _sd_writeLineFile(String file, String line) {
    line.trim();
    // open the file for reading:
     _sd_remove(file);
    // TODO: make this stable
    File IO = SD.open(file, FILE_WRITE);
    if (IO) {
        IO.print(line);
        IO.close();
        return true;
    } else {
        Serial.print("Writing failed ");
        Serial.println(file);
        IO.close();
        return false;
    };
}

boolean _sd_writeNewLine(String file, String line) {
    line.trim();
    File IO = SD.open(file, FILE_WRITE);
    if (IO) {
        IO.println(line);
        IO.close();
        return true;
    } else {
        Serial.print("Writing line failed ");
        Serial.println(file);
        IO.close();
        return false;
    };
}
