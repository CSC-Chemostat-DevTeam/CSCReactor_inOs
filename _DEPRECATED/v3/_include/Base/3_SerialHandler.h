#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

#include "Base/3_AbsHandler.h"

#include <Arduino.h>
#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/3_Chemostat.h"

#define LOG_ERROR_LEVEL 0
#define LOG_WARN_LEVEL 1
#define LOG_INFO_LEVEL 2
#define LOG_DEV_LEVEL 3

// All Chemostat serial printing must use this Handler
class SerialHandler : 
    public AbsHandler
{
    private:
        byte vlevel;
        unsigned long baud_rate;

    public:
        // ----------------------------------------------------
        // CONSTRUCTOR
		SerialHandler(Chemostat* Ch);

        // ----------------------------------------------------
        // SKETCH INTERFACE
        void onsetup();
        void onloop();

        // ----------------------------------------------------
        // SERIAL INTERFACE
        void setBaudRate(unsigned long brate);
        unsigned long getBaudRate();

        template <typename T0, typename... Ts>
        void print(T0 arg0, Ts... args) {
            _print(arg0, args...);
        }

        template <typename T0, typename... Ts>
        void println(T0 arg0, Ts... args) {
            _println(arg0, args...);
        }

        int available() { return Serial.available(); }
        int read() { return Serial.read(); }
        

        // ----------------------------------------------------
        // SERIAL LOG INTERFACE
        
        byte getVLevel();
        void setVLevel(byte vlv);

        template <typename T0, typename... Ts>
        void _log(T0 tag, Ts... args) {
            _println(">>> ", tag, ":"); 
            _println(args...);
            _println("<<<"); 
        }
        
        template <typename T0, typename... Ts>
        void error(T0 arg0, Ts... args) {
            if (this->vlevel < LOG_ERROR_LEVEL) { return; }
            _log("ERROR", arg0, args...);
        }

        template <typename T0, typename... Ts>
        void info(T0 arg0, Ts... args) {
            if (this->vlevel < LOG_INFO_LEVEL) { return; }
            _log("INFO", arg0, args...);
        }

        template <typename T0, typename... Ts>
        void warn(T0 arg0, Ts... args) {
            if (this->vlevel < LOG_WARN_LEVEL) { return; }
            _log("WARN", arg0, args...);
        }

        template <typename T0, typename... Ts>
        void dev(T0 arg0, Ts... args) {
            if (this->vlevel < LOG_DEV_LEVEL) { return; }
            _log("DEV", arg0, args...);
        }
        
};




#endif // SERIAL_HANDLER_H