#include "Base/5_SerialDriver.h"
#include "Base/8_DHT11Driver.h"

// ----------------------------------------------------
// Variables
DHT DHT11Driver::dht(0, DHT11);
uint8_t DHT11Driver::curr_pin = 0;

// ----------------------------------------------------
// DHT INTERFACE
// TODO/ Add a flag to know if this was already previouly called...
void DHT11Driver::begin(uint8_t pin) { 

    if (pin == 0) { return; }
    if (DHT11Driver::curr_pin == pin) { return; }
    DHT11Driver::curr_pin = pin;
    
    DHT11Driver::dht = DHT(pin, DHT11);
    dht.begin();
    
    delay(500); 
}

float DHT11Driver::getTemperature() {
    return dht.readTemperature();
}

float DHT11Driver::getHumidity() {
    return dht.readHumidity();
}

// ----------------------------------------------------
// _DEV INTERFACE
void DHT11Driver::sayHi() { 
    SerialDriver::println("Hi from DHT11Driver");
    SerialDriver::println(TAB, "pin: ", DHT11Driver::curr_pin);
}

// ----------------------------------------------------
// SKETCH INTERFACE
void DHT11Driver::onsetup(){
    // Set all pins to INPUT_PULLUP
    DHT11Driver::sayHi();
}
void DHT11Driver::onloop(){
    ;
}
