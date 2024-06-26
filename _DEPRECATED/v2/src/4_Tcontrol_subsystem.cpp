#include "Base/1_config.h"
#include "Base/1_constants.h"
#include "4_cmd_subsystem.h"
#include "4_Tcontrol_subsystem.h"
#include "4_datalogger_subsystem.h"


// ----------------------------------------------------
// CONSTRUCTOR
// TODO: split into Tsensor and Heater
TControlSubsystem::TControlSubsystem() :
    SubSystem(
        /* enable */ true, 
        /* enable0 */ TSENSOR_INCLUDE_FLAG_DFLT_VAL
    ){
    this->_one_wire = OneWire(HEATER_T_SENSOR_PIN);
    this->_T_sensor = DallasTemperature(&_one_wire);
    this->sensor_timer = Timer(TSENSOR_MEASUREMENT_PERIOD_DFLT_VAL, TIMER_FIXED_MODE);
    this->heater_timer = Timer(INFTY_LONG, TIMER_FIXED_MODE); // TODO: finish heater code
    this->temp = 0;
}

// ----------------------------------------------------
// SKETCH INTERFACE
void TControlSubsystem::onsetup(){
    // INIT INTERNALS
    this->_T_sensor.begin();
    delay(3);

    // PINS
    pinMode(HEATER_PIN, OUTPUT);
    digitalWrite(HEATER_PIN, LOW);
}

void TControlSubsystem::onloop(){

    if (this->sensor_timer.istime()) { 
        measureTemp();
    }

    if (this->heater_timer.istime()) { 
        // TODO: finish heater code
        digitalWrite(HEATER_PIN, LOW);
    }
}

// ----------------------------------------------------------------------------
// T SENSOR API
void TControlSubsystem::measureTemp(){
    this->_T_sensor.requestTemperatures();
    delay(3); // Stability?
    this->temp = _T_sensor.getTempCByIndex(0);
}

float TControlSubsystem::getTemp(){
    return this->temp;
}

// ----------------------------------------------------
// CMD INTERFACE
boolean TControlSubsystem::execCmd(String& key, String& val){
    // get cmd
    String cmd = _parseCmdString(key, "TCONTROL-");
    if (cmd.equals("")) { return false; }

    // Call parent
    if (this->SubSystem::execCmd(cmd, val)) { return true; }

    // get temperature
    if (cmd.equals("GET-TEMP")) {
        Serial.print("temp: ");
        Serial.println(this->getTemp());
        return true;
    }
    return false;
}

// ----------------------------------------------------
// BOTTOM INTERFACE
void TControlSubsystem::onBottomPressed(){
    this->Enable(false);
    digitalWrite(HEATER_PIN, LOW);
}

// ----------------------------------------------------
// LOGGER INTERFACE
// Concurrent
void TControlSubsystem::onLogWrite(DataLoggerSubsystem& logger){
    // Temperature
    logger.appendHeader("Temp");
    logger.appendValue(String(this->getTemp()));
    return;
}

// ----------------------------------------------------
// STOP INTERFACE
void TControlSubsystem::onStop(){
    ;
}