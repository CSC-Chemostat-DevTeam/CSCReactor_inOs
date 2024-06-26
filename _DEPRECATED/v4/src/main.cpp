// Global libs
#include <Arduino.h>
// #include <SPI.h>
// #include <SD.h>

// TODO: Stop using Arduino.hString class, use string or char[] (explore string.h, ctype.h)
// 

// Local libs
#include "Base/0_Base.h"

Chemostat* pCH;

void setup() {

  // // DEV
  // Serial.begin(115200);
  // while (!Serial) {
  //     ;  // wait for serial port to connect. Needed for native USB port only
  // }
  
  pCH = new Chemostat(); // TODO: [HEAP] Check proper free/delete
  pCH->onsetup();
}

void loop() {

  // float a1 = analogRead(A8) * (5.0 / 1023.0);
  // Serial.println(a1);
  // float a2 = analogRead(A12) * (5.0 / 1023.0);
  // Serial.println(a2);
  // delay(100);

  // Serial.print("a1 = ");
  // Serial.print(a1);
  // Serial.print(", a2 = ");
  // Serial.print(a2);
  // Serial.println();

  pCH->onloop();

}

