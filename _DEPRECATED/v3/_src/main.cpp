  // Global libs
  #include <Arduino.h>
  #include <SPI.h>
  #include <SD.h>

  // Local libs
  #include "Base/0_Base.h"

  Chemostat* pCH; // TODO: [POINTER] Check proper free/delete

  void setup() {

    // DEV
    pCH = new Chemostat(); // TODO: [HEAP] Check proper free/delete
    pCH->onsetup();

  }

  void loop() {
    pCH->onloop();
    // DEV
    pCH->pCMD->request("KAKA");
  }

  // RAM:   [=         ]   8.4% (used 692 bytes from 8192 bytes)
  // Flash: [          ]   3.7% (used 9354 bytes from 253952 bytes)









  // // DEV //
  // class _Chemostat;
  // class _SubSystem;

  // class _SubSystem{
  //   public:
  //     _Chemostat* Ch;
  //     String id;

  //     _SubSystem(_Chemostat* Ch, String id);

  //     void hiSub1();
  //     void hiSub2();

  //     void hi();
  //     void from();
  // };

  // class _Chemostat {
  //   public:
  //     _SubSystem* _sub1;
  //     _SubSystem* _sub2;
  //     _Chemostat();

  // };


  // _Chemostat::_Chemostat() {
  //   this->_sub1 = new _SubSystem(this, "sub1");
  //   this->_sub2 = new _SubSystem(this, "sub2");
  // }

  // _SubSystem::_SubSystem(_Chemostat* Ch, String id) {
  //     this->Ch = Ch;
  //     this->id = id;
  //   }

  // void _SubSystem::hiSub1(){ this->from(); this->Ch->_sub1->hi(); }
  // void _SubSystem::hiSub2(){ this->from(); this->Ch->_sub2->hi(); }
  // void _SubSystem::hi() {
  //   Serial.print("Hi, I'm ");
  //   Serial.println(this->id);
  // }
  // void _SubSystem::from() {
  //   Serial.print("from ");
  //   Serial.println(this->id);
  // }



  // void setup() {
  //   // Create a Serial System?
  //   // Serial.begin(IO_BAUDRATE); // TODO: move rate to config
  //   Serial.begin(115200); // TODO: move rate to config
  //   while (!Serial) {
  //       ;  // wait for serial port to connect. Needed for native USB port only
  //   }
  //   Serial.println("Hello");

  //   // DEV
  //   _Chemostat _ch = _Chemostat();
  //   _ch._sub1->hiSub1();
  //   _ch._sub1->hiSub2();
  //   _ch._sub2->hiSub1();
  //   _ch._sub2->hiSub2();

  //   while(1);

  // }

  // void loop(){
  //   ;
  // }


