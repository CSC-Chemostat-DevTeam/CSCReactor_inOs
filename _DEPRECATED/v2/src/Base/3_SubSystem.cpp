#include "Base/3_SubSystem.h"

// ----------------------------------------------------
// CONSTRUCTORS
SubSystem::SubSystem(boolean enable, boolean enable0){
    Serial.println("At SubSystem::SubSystem");
    this->enable = enable;
    this->enable0 = enable0;
}
SubSystem::SubSystem() { SubSystem(false, false); }

// ----------------------------------------------------
// ENABLE INTERFACE
void SubSystem::Enable(boolean flag){
    // Serial.println("At SubSystem::Enable");
    this->enable = flag;
}
void SubSystem::Enable0(boolean flag){
    // Serial.println("At SubSystem::Enable");
    this->enable0 = flag;
}
// "privates"
boolean SubSystem::_enable(){
    return this->enable;
}
boolean SubSystem::_enable0(){
    return this->enable0;
}

boolean SubSystem::isEnable(){
    // Serial.println("At SubSystem::isEnable");
    if (!this->enable) { return false; }
    if (!this->enable0) { return false; }
    return true;
}

// ----------------------------------------------------
// CMD INTERFACE
boolean SubSystem::execCmd(String& cmd, String& val){

    // --------------------
    // ENABLE INTERFACE
    if (cmd.equals("GET-EN")) {
        Serial.print("enable: ");
        Serial.println(this->_enable());
        return true;
    }
    if (cmd.equals("SET-EN")) {
        this->Enable(val.toInt() != 0);
        Serial.print("enable: ");
        Serial.println(this->_enable());
        return true;
    }
    // enable0
    if (cmd.equals("GET-EN0")) {
        Serial.print("enable0: ");
        Serial.println(this->_enable0());
        return true;
    }
    if (cmd.equals("SET-EN0")) {
        this->Enable0(val.toInt() != 0);
        Serial.print("enable0: ");
        Serial.println(this->_enable0());
        return true;
    }
    return false;
}