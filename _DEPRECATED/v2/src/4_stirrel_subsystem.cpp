#include "Base/1_config.h"
#include "4_cmd_subsystem.h"
#include "4_stirrel_subsystem.h"

// ----------------------------------------------------
// CONSTRUCTOR

StirrelSubsystem::StirrelSubsystem() :
    SubSystem(
        /* enable */ true, 
        /* enable0 */ STIRREL_INCLUDE_FLAG_DFLT_VAL
    ){
    this->pulse_high_time = STIRREL_PULSE_HIGH_TIME_DFLT_VAL;
    this->pulse_low_time = STIRREL_PULSE_LOW_TIME_DFLT_VAL;
    this->timer = Timer(pulse_low_time, TIMER_ROLLING_MODE);
    this->state = LOW;
}

// ----------------------------------------------------
// SKETCH INTERFACE

void StirrelSubsystem::onsetup() {
    pinMode(STIRREL_PIN, OUTPUT);
    digitalWrite(STIRREL_PIN, LOW);
}


void StirrelSubsystem::onloop() {

    // check enable
    if (!this->isEnable()) { 
        if (this->state == HIGH) { // deactivate if unable
            this->state = LOW;
            digitalWrite(STIRREL_PIN, LOW);
            this->timer.set_period(this->pulse_low_time);
        }
        return; 
    }

    // check if it is state change time
    if (this->timer.istime()) { 
        if (this->state == HIGH) {
            this->state = LOW;
            this->timer.set_period(this->pulse_low_time);
        } else {
            this->state = HIGH;
            this->timer.set_period(this->pulse_high_time);
        }
        digitalWrite(STIRREL_PIN, this->state);
    }
}

// ----------------------------------------------------
// BLOCKING INTERFACE
void StirrelSubsystem::beforeBlock() {
    // avoid stock on high
    digitalWrite(STIRREL_PIN, LOW); 
    this->Enable(false);
}

void StirrelSubsystem::afterBlock() {
    this->Enable(true);
}

// ----------------------------------------------------
// CMD INTERFACE
boolean StirrelSubsystem::execCmd(String& key, String& val){
    
    // get cmd
    String cmd = _parseCmdString(key, "STRR-");
    if (cmd.equals("")) { return false; }

    // Call parent
    if (this->SubSystem::execCmd(cmd, val)) { return true; }
    
    // pulse_high_time
    if (cmd.equals("SET-HT")) {
        this->pulse_high_time = val.toInt();
        Serial.print("pulse_high_time: ");
        Serial.println(this->pulse_high_time);
        return false;
    }
    if (cmd.equals("GET-HT")) {
        Serial.print("pulse_high_time: ");
        Serial.println(this->pulse_high_time);
        return false;
    }
    // pulse_low_time
    if (cmd.equals("GET-LT")) {
        Serial.print("pulse_low_time: ");
        Serial.println(this->pulse_low_time);
        return false;
    }
    if (cmd.equals("SET-LT")) {
        this->pulse_low_time = val.toInt();
        Serial.print("pulse_low_time: ");
        Serial.println(this->pulse_low_time);
        return false;
    }
    return true;
}

// ----------------------------------------------------
// BOTTOM INTERFACE
void StirrelSubsystem::onBottomPressed(){
    this->onStop();
}

// ----------------------------------------------------
// STOP INTERFACE
void StirrelSubsystem::onStop(){
    this->Enable0(false);
    this->Enable(false);
    this->state = LOW;
    digitalWrite(STIRREL_PIN, LOW);
}