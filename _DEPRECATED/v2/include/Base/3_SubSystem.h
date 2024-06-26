#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H

#include <Arduino.h>

// ----------------------------------------------------
// TODO: Add an 'info' 'warn' 'error' function to print stuff

// ----------------------------------------------------
class SubSystem{
  private:
    boolean enable0;
    boolean enable;

  public:

    SubSystem(boolean enable, boolean enable0);
    SubSystem();
      

    // ----------------------------------------------------
    // ENABLE INTERFACE
    virtual boolean _enable();
    virtual boolean _enable0();
    virtual void Enable(boolean flag);
    virtual void Enable0(boolean flag);
    virtual boolean isEnable();

    // ----------------------------------------------------
    // CMD INTERFACE
    virtual boolean execCmd(String& key, String& val);

};

#endif // SUBSYSTEM_H