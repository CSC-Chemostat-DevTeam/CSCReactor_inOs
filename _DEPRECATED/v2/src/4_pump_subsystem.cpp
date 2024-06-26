#include "Base/1_config.h"
#include "Base/3_Timer.h"
#include "4_cmd_subsystem.h"
#include "4_pump_subsystem.h"
#include "5_interfaces.h"

// ----------------------------------------------------
// CONSTRUCTOR

PumpSubsystem::PumpSubsystem() :
    SubSystem(
        /* enable */ true, 
        /* enable0 */ PUMP_INCLUDE_FLAG_DFLT_VAL
    ){
    this->timer = Timer(PUMP_PULSE_PERIOD_DFLT_VAL, TIMER_FIXED_MODE);
    this->pulse_duration = PUMP_PULSE_DURATION_DFLT_VAL;
    this->pulse_period = PUMP_PULSE_PERIOD_DFLT_VAL;
}

// ----------------------------------------------------
// SKETCH INTERFACE

void PumpSubsystem::onsetup() {
    pinMode(PUMP_PIN, OUTPUT);
    digitalWrite(PUMP_PIN, LOW);
}

// blocking
void PumpSubsystem::onloop() {

    // check enable
    if (!this->isEnable()) { 
        digitalWrite(PUMP_PIN, LOW);
        return; 
    }

    // check if it is state change time
    if (this->timer.istime()) { 
        this->timer.set_period(this->pulse_period);
        beforeBlockI();
        delay(PUMP_BUFFER_TIME_DFLT_VAL);
        digitalWrite(PUMP_PIN, HIGH);
        delay(this->pulse_duration);
        digitalWrite(PUMP_PIN, LOW);
        afterBlockI();
    }
}


// ----------------------------------------------------
// BLOCKING INTERFACE
void PumpSubsystem::beforeBlock() {
    ;
}

void PumpSubsystem::afterBlock() {
    ;
}

// ----------------------------------------------------
// CMD INTERFACE
boolean PumpSubsystem::execCmd(String& key, String& val){

    // get cmd
    String cmd = _parseCmdString(key, "PUMP-");
    if (cmd.equals("")) { return false; }

    // Call parent
    if (this->SubSystem::execCmd(cmd, val)) { return true; }

    // pulse_duration
    if (cmd.equals("SET-PD")) {
        this->pulse_duration = val.toInt();
        Serial.print("pulse_duration: ");
        Serial.println(this->pulse_duration);
        return true;
    }
    if (cmd.equals("GET-PDUR")) {
        Serial.print("pulse_duration: ");
        Serial.println(this->pulse_duration);
        return true;
    }

    // pulse_period
    if (cmd.equals("SET-PPER")) {
        this->pulse_period = val.toInt();
        Serial.print("pulse_period: ");
        Serial.println(this->pulse_period);
        return true;
    }
    if (cmd.equals("GET-PPER")) {
        Serial.print("pulse_period: ");
        Serial.println(this->pulse_period);
        return true;
    }

    if (cmd.equals("HIGH")) {
        Serial.print("pump_on: ");
        digitalWrite(PUMP_PIN, HIGH);
        return true;
    }
    if (cmd.equals("LOW")) {
        Serial.print("pump_off");
        digitalWrite(PUMP_PIN, LOW);
        return true;
    }
    return false;
}

// ----------------------------------------------------
// BOTTOM INTERFACE
void PumpSubsystem::onBottomPressed(){
    this->onStop();
}

// ----------------------------------------------------
// STOP INTERFACE
void PumpSubsystem::onStop(){
    this->Enable0(false); // permanent
    this->Enable(false); // permanent
    digitalWrite(PUMP_PIN, LOW);
}