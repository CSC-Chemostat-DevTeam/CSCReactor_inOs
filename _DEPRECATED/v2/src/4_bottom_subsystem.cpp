#include "Base/1_config.h"
#include "4_bottom_subsystem.h"
#include "4_cmd_subsystem.h"
#include "5_interfaces.h"

// ----------------------------------------------------
// CONSTRUCTOR
BottomSubsystem::BottomSubsystem() :
    SubSystem(
        /* enable */ true, 
        /* enable0 */ BOTT_INCLUDE_FLAG_DFLT_VAL
    ){
    this->state=LOW;
    this->timer = Timer(BOTTOM_SAFE_PERIOD, TIMER_FIXED_MODE);
}

// ----------------------------------------------------
// BOTTOM INTERFACE

void BottomSubsystem::onBottomPressed(){
    this->state = !this->state;
}

// ----------------------------------------------------
// SKETCH INTERFACE
// TODO: DO NOT USE Interrupts
void BottomSubsystem::onsetup(){
    pinMode(BOTTOM_INTERRUP_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BOTTOM_INTERRUP_PIN), onBottomPressedI, RISING);
}

void BottomSubsystem::onloop(){
    // check enable
    if (!this->isEnable()) { return; }
}

// ----------------------------------------------------
// STOP INTERFACE
void BottomSubsystem::onStop(){
    ;
}