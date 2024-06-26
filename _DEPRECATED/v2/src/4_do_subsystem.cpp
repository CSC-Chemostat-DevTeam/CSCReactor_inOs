#include "Base/1_config.h"
#include "Base/3_Timer.h"
#include "4_do_subsystem.h"
#include "4_datalogger_subsystem.h"
#include "4_cmd_subsystem.h"
#include "5_interfaces.h"

// ----------------------------------------------------
// CONSTRUCTOR
DOSubsystem::DOSubsystem() :
    SubSystem(
        /* enable */ true, 
        /* enable0 */ DO_INCLUDE_FLAG_DFLT_VAL
    ){
    this->samp_time = DO_LEDS_SAMPLING_TIME_DFLT_VAL;
    this->laser_pwd = DO_LASER_PWD_VAL_DFLT_VAL;
    this->led1_count = 0;
    this->led2_count = 0;
    this->timer = Timer(DO_ACTION_PERIOD_DFLT_VAL, TIMER_ROLLING_MODE);
}

// ----------------------------------------------------
// DO UTILS
// BLOCKING
long _count_pulses(int pin, unsigned long sampling_time) {
    
    sampling_time = sampling_time * 1000; // to micro

    // reset
    long n = 0;

    long t0 = micros();
    while (true) {

        // wait till a HIGH pulse happends and ends
        pulseIn(pin, HIGH, 10);

        n++;

        // Time out
        if (micros() - t0 > sampling_time) { break; }
    }
    return n;
}

// ----------------------------------------------------
// SKETCH INTERFACE
void DOSubsystem::onsetup(){
    pinMode(DO_LED1_PIN, INPUT_PULLUP);
    pinMode(DO_LED2_PIN, INPUT_PULLUP);
    pinMode(DO_LASER_PWD_PIN, OUTPUT);
}

void DOSubsystem::onloop(){
    
    // check enable
    if (!this->isEnable()) { return; }

    // check if it is time
    if (!this->timer.istime()) { return; }

    beforeBlockI();
    
    // On laser
    analogWrite(DO_LASER_PWD_PIN, this->laser_pwd);
    
    delay(DO_BUFFER_TIME_DFLT_VAL); // settle time

    // read leds
    this->led1_count = _count_pulses(DO_LED1_PIN, this->samp_time);
    this->led2_count = _count_pulses(DO_LED2_PIN, this->samp_time);

    // Off laser
    analogWrite(DO_LASER_PWD_PIN, 0);

    afterBlockI();
}


// ----------------------------------------------------
// BLOCKING INTERFACE
void DOSubsystem::beforeBlock() {
    ;
}

void DOSubsystem::afterBlock() {
    ;
}

// ----------------------------------------------------
// CMD INTERFACE
boolean DOSubsystem::execCmd(String& key, String& val) {

    // get cmd
    String cmd = _parseCmdString(key, "DO-");
    if (cmd.equals("")) {return false; }

    // Call parent
    if (this->SubSystem::execCmd(cmd, val)) { return true; }

    // laser pwd
    if (cmd.equals("SET-LPWD")) {
        this->laser_pwd = val.toInt();
        Serial.print("laser_pwd: ");
        Serial.println(this->laser_pwd);
        return true;
    }

    if (cmd.equals("GET-LPWD")) {
        Serial.print("laser_pwd: ");
        Serial.println(this->laser_pwd);
        return true;
    }

    // leds
    if (cmd.equals("GET-LED1")) {
        Serial.print("led1_count: ");
        Serial.println(this->led1_count);
        return true;
    }
    if (cmd.equals("GET-LED2")) {
        Serial.print("led1_count: ");
        Serial.println(this->led2_count);
        return true;
    }
    if (cmd.equals("GET-LEDS")) {
        Serial.print("led1_count: ");
        Serial.println(this->led1_count);
        Serial.print("led2_count: ");
        Serial.println(this->led2_count);
        return true;
    }

    // sample time
    if (cmd.equals("SET-STIME")) {
        this->samp_time = val.toInt();
        Serial.print("samp_time: ");
        Serial.println(this->samp_time);
        return true;
    }
    // sample time
    if (cmd.equals("GET-STIME")) {
        Serial.print("samp_time: ");
        Serial.println(this->samp_time);
        return true;
    }
    
    return false;
}

// ----------------------------------------------------
// BOTTOM INTERFACE
void DOSubsystem::onBottomPressed(){
    this->Enable(false);
    analogWrite(DO_LASER_PWD_PIN, 0);
}

// ----------------------------------------------------
// LOGGER INTERFACE
void DOSubsystem::onLogWrite(DataLoggerSubsystem& logger){
    // Leds
    logger.appendHeader("Led1");
    logger.appendValue(String(this->led1_count));
    logger.appendHeader("Led2");
    logger.appendValue(String(this->led2_count));
    return;
}

// ----------------------------------------------------
// STOP INTERFACE
void DOSubsystem::onStop(){
    ;
}