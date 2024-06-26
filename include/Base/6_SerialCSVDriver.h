#ifndef SERIAL_CSV_DRIVER_H
#define SERIAL_CSV_DRIVER_H

#include "Base/2_Utils.h"
#include "Base/3_CSVLineReader.h"
#include "Base/3_CSVLineReader.h"
#include "Base/5_SerialDriver.h"

// ----------------------------------------------------
// All parseble msgs between the PC and the board must be 
// handle by this class
// ----------------------------------------------------

namespace SerialCSVDriver
{
    extern CSVLineReader csvline;

    // Response
    extern unsigned long respcount;

    // ----------------------------------------------------
    // SKETCH INTERFACE
    void onsetup();
    void onloop();

    // -------------------------
    // HANDLE MSG INTERFACE
    boolean handleMsg();

    // ----------------------------------------------------
    // MSG INTERFACE
    /**
        Will try to read a key pair from serial.
        [BLOKING] This will block till tout or msg is received.

        \param[in] tout Waiting time in millisecunds

        \return void
    */
    void tryReadMsg(unsigned long tout);
    void tryReadMsg(const String& msg); // read from String (dev stuff)
    void reset();

    // place for registering MdgHandlers
    void handleAllMsgs();

    String getValString(byte i);

    boolean msgAvailable();
    String msgCsvLineString();

    // ----------------------------------------------------
    // HASHES
    unsigned int linehash(); // class hash (msg1 and msg2 if equal will have equal hash)
    unsigned long timetag(); // msg hash (per msg even if are equal)
    // unsigned long timetag(){
    //     return (unsigned int)(millis());
    // }

    // ----------------------------------------------------
    // MSG VAL STRING QUERIES
    boolean hasValString(byte i, const String& str);
    boolean hasValStringPrefix(byte i, const String& prefix);
    boolean hasValStringSuffix(byte i, const String& suffix);

    // ----------------------------------------------------
    // SEND MSG
    
    // utils
    template <typename Arg>
    inline void _printCSVVals(Arg arg) { SerialDriver::print(arg);  }
    // variadic template with one or more arguments.
    template <typename First, typename... Args>
    inline void _printCSVVals(First first, Args... args) {
        SerialDriver::print(first); 
        SerialDriver::print(CSV_LINE_SEP_CHAR); 
        SerialCSVDriver::_printCSVVals(args...);
    }

    template <typename Arg>
    inline void sendMsg(Arg arg0) {
        SerialDriver::println(CSV_LINE_INIT_CHAR, arg0, CSV_LINE_END_CHAR);
    }
    template <typename T0, typename... Ts>
    inline void sendMsg(T0 arg0, Ts... args) {
        SerialDriver::print(CSV_LINE_INIT_CHAR);
        SerialCSVDriver::_printCSVVals(arg0, args...);
        SerialDriver::println(CSV_LINE_END_CHAR);
    };

    // ----------------------------------------------------
    // RESPONSE INTERFACE
    // Example $AKW:MSG-HASH:TIMETAG:CLASS-HASH:RECIEVED%
    template <typename T0, typename... Ts>
    inline void sendMsgResponse(T0 arg0, Ts... args) {
        SerialCSVDriver::sendMsg("RES", 
            SerialCSVDriver::respcount,
            SerialCSVDriver::linehash(),
            SerialCSVDriver::timetag(),
            arg0, args...
        );
        SerialCSVDriver::respcount++;
    };
    inline void sendMsgResponse() { SerialCSVDriver::respcount++; } // empty response

    void openMsgResponse();
    void closeMsgResponse();

    // ----------------------------------------------------
    template <typename T0, typename... Ts>
    inline void sendMsgAcknowladge(T0 arg0, Ts... args) {
        SerialCSVDriver::sendMsg(
            MSG_ACKNOWLADGE_TOKEN,
            SerialCSVDriver::linehash(),
            SerialCSVDriver::timetag(),
            arg0, args...
        );
    }

    // ----------------------------------------------------
    // _DEV INTERFACE
    void sayHi();
}

#endif // SERIAL_CSV_DRIVER_H