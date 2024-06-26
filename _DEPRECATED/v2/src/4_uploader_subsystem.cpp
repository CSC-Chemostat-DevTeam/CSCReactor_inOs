#include "Base/1_config.h"
#include "Base/3_StaticString.h"
#include "4_cmd_subsystem.h"
#include "4_uploader_subsystem.h"
#include "5_interfaces.h"

// ----------------------------------------------------
// CONSTRUCTOR

UploaderSubsystem::UploaderSubsystem() :
    SubSystem(
        /* enable */ true, 
        /* enable0 */ UPLOADER_INCLUDE_FLAG_DFLT_VAL
    ){
    this->file = "";
    this->busy = false; // Move to ConcurrentTask
    this->ctask = ConcurrentTask ();
}

// ----------------------------------------------------
// SKETCH INTERFACE

void UploaderSubsystem::onsetup(){
    ;
}

void UploaderSubsystem::onloop(){
    upload();
}

// ----------------------------------------------------
// UPLOADER INTERFACE

boolean UploaderSubsystem::isBusy(){
    return this->busy;
}

// ---------------------------------------------------------
// BLOCKING
StaticString _UPLOADER_BUFFER = StaticString();
boolean _upload_dev(){
    // ---------------------------------------------------------
    // START SIGNAL
    beforeBlockI();
    Serial.println();
    Serial.println(IO_PRINT_START_MARKER);
    delay(5);

    // ---------------------------------------------------------
    // Print garbage
    _UPLOADER_BUFFER.reset();
    long nlines = 45000; // nlines = log frec (10s) x days running (5 days)
    for (long l = 0; l < nlines; l++) {
        _UPLOADER_BUFFER.push(String(millis()));
        _UPLOADER_BUFFER.push(",");
        _UPLOADER_BUFFER.push(String(random()));
        _UPLOADER_BUFFER.push(",");
        _UPLOADER_BUFFER.push(String(random()));
        _UPLOADER_BUFFER.push(",");
        _UPLOADER_BUFFER.push(String(random()));
        Serial.println(_UPLOADER_BUFFER.c_string());
        _UPLOADER_BUFFER.reset();
    }

    // ---------------------------------------------------------
    // END SIGNAL
    Serial.println(IO_PRINT_END_MARKER);
    Serial.println();
    afterBlockI();

    return true;
}

boolean _upload(String& file){

    // ---------------------------------------------------------
    // Open file
    File IO = SD.open(file, FILE_READ); // open new
    if (!IO) {
        // ERROR
        Serial.print("File read failed ");
        Serial.println(file);
        IO.close();
        return false; 
    }

    // ---------------------------------------------------------
    // START SIGNAL
    beforeBlockI();
    Serial.println();
    Serial.println(IO_PRINT_START_MARKER);
    delay(5);

    // ---------------------------------------------------------
    // Print
    // read from the file until there's nothing else in it:
    while (IO.available()) 
    {
        Serial.print((char)IO.read());
    }                               
    
    // ---------------------------------------------------------
    // END SIGNAL
    Serial.println(IO_PRINT_END_MARKER);
    Serial.println();
    afterBlockI();
    
    // ---------------------------------------------------------
    // close the file:              
    IO.close();

    return true;
}

void UploaderSubsystem::upload(){
    
    if (!this->isBusy()) { return; }

    if (DEV_MODE) {
        _upload_dev();
    } else {
        _upload(this->file);
    }

    // Signal non busy
    this->busy = false;
}

// // CONCURRENT
// void UploaderSubsystem::upload(){

//     if (!this->isBusy()) { return; }

//     // update
//     this->ctask.at_init();

//     // ---------------------------------------------------------
//     // Open file
//     if (this->ctask.is_todo()) { 
//         this->fileio.close(); // close old
//         this->fileio = SD.open(this->file, FILE_READ); // open new
//         if (!this->fileio) {
//             // ERROR
//             Serial.print("File read failed ");
//             Serial.println(this->file);
//         }
//         return; 
//     }

//     // ---------------------------------------------------------
//     // START SIGNAL
//     if (this->ctask.is_todo()) { Serial.println(); return; }
//     if (this->ctask.is_todo()) { Serial.println(IO_PRINT_START_MARKER); return; }

//     // ---------------------------------------------------------
//     // read file


//     // ---------------------------------------------------------
//     // END SIGNAL
//     if (this->ctask.is_todo()) { Serial.println(IO_PRINT_END_MARKER); return; }
//     if (this->ctask.is_todo()) { Serial.println(); return; }
     
//     // ---------------------------------------------------------
//     this->ctask.at_exit();
// }

// ----------------------------------------------------
// CMD INTERFACE
boolean UploaderSubsystem::execCmd(String& key, String& val){

    // get cmd
    String cmd = _parseCmdString(key, "UPLOADER-");
    if (cmd.equals("")) { return false; }

    // Call parent
    if (this->SubSystem::execCmd(cmd, val)) { return true; }

    // abort
    if (cmd.equals("ABORT")) {
        this->busy = false;
        this->ctask.reset();
        return true;
    }

    if (this->isBusy()) { return true; } // ignore if busy
    
    if (cmd.equals("UPLOAD")) {
        this->busy = true;
        this->ctask.reset();
        return true;
    }
    // file
    if (cmd.equals("SET-FILE")) {
        this->file=val;
        Serial.println(this->file);
        return true;
    }
    return false;
}


// ----------------------------------------------------
// STOP INTERFACE
void UploaderSubsystem::onStop(){
    ;
}