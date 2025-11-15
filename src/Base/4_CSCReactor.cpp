#include "Base/1_config.h"
#include "Base/2_Utils.h"
#include "Base/4_CSCReactor.h"
#include "Base/5_SerialDriver.h"

// ----------------------------------------------------
bool CSCReactor::devmode = false; // Define and initialize it

// ----------------------------------------------------
// MARK: SCKETCH INTERFACE
void CSCReactor::onsetup()
{
    CSCReactor::sayHi();
}
void CSCReactor::onloop() { ; }

// ----------------------------------------------------
// MARK: _DEV INTERFACE
void CSCReactor::sayHi()
{
    SerialDriver::println("Hi from CSCReactor");
    SerialDriver::println(TAB, "devmode: ", CSCReactor::devmode);
}
