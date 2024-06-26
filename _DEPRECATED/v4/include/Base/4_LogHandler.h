#ifndef LOG_HANDLER_H
#define LOG_HANDLER_H

#include <Arduino.h>

#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/4_Chemostat.h"
#include "Base/4_AbsHandler.h"
#include "Base/4_SerialHandler.h"

//  --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// Handler for logging dev/info/error information
//  --- --- --- --- --- --- --- --- --- --- --- --- --- ---

class LogHandler : 
    public AbsHandler
{
    private:
        byte serial_vlevel;
        byte sd_vlevel;

    public:
        // ----------------------------------------------------
        // CONSTRUCTOR
        LogHandler(Chemostat* Ch);

        // ----------------------------------------------------
        // SKETCH INTERFACE
        void onsetup();
        void onloop();

        // ----------------------------------------------------
        // SERIAL LOG INTERFACE
        // From python doc (https://docs.python.org/3/howto/logging.html)
        // If the logger’s level is higher than the method call’s, 
        // no logging message is actually generated. This is the basic mechanism 
        // controlling the verbosity of logging output.
        // TODO: Use msg interface?
        
        byte getSerialVLevel();
        void setSerialVLevel(byte vlv);

        template <typename T0, typename... Ts>
        void _log_serial(T0 tag, Ts... args) { 
            // One liner
            this->Ch->pSERIAL->println(
                LOG_INIT_TOKEN, " ", tag, " [", this->Ch->nowTimeTag(), "]: ", 
                args..., 
                " ", LOG_END_TOKEN
            );
        }

        // ----------------------------------------------------
        // SERIAL LOG INTERFACE
        
        byte getSDVLevel();
        void setSDVLevel(byte vlv);

        template <typename T0, typename T1>
        void _log_sd(T0 tag, T1 line) { // One liner
            ; 
        }
        template <typename T0, typename... Ts>
        void _log_sd(T0 tag, Ts... args) { // Multi liner
            ;
        }

        // ----------------------------------------------------
        // LOG INTERFACE
        
        template <typename T0, typename... Ts>
        void error(T0 arg0, Ts... args) {
            if (this->serial_vlevel <= LOG_ERROR_LEVEL) { 
                _log_serial(LOG_ERR_TAG, arg0, args...);
            }
            if (this->sd_vlevel <= LOG_ERROR_LEVEL) {
                _log_sd(LOG_ERR_TAG, arg0, args...);
            }
        }

        template <typename T0, typename... Ts>
        void warn(T0 arg0, Ts... args) {
            if (this->serial_vlevel <= LOG_WARN_LEVEL) { 
                _log_serial(LOG_WARN_TAG, arg0, args...);
            }
            if (this->sd_vlevel <= LOG_WARN_LEVEL) { 
                _log_sd(LOG_WARN_TAG, arg0, args...);
            }
        }

        template <typename T0, typename... Ts>
        void info(T0 arg0, Ts... args) {
            if (this->serial_vlevel <= LOG_INFO_LEVEL) { 
                _log_serial(LOG_INFO_TAG, arg0, args...);
            }
            if (this->sd_vlevel <= LOG_INFO_LEVEL) {
                _log_sd(LOG_INFO_TAG, arg0, args...);
            }
        }

        template <typename T0, typename... Ts>
        void dev(T0 arg0, Ts... args) {
            if (this->serial_vlevel <= LOG_DEV_LEVEL) { 
                _log_serial(LOG_DEV_TAG, arg0, args...);
            }
            if (this->sd_vlevel <= LOG_DEV_LEVEL) {
                _log_sd(LOG_DEV_TAG, arg0, args...);
            }
        }

        // -------------------------
        // HANDLE MSG INTERFACE
        boolean handleMsg();

        // ----------------------------------------------------
        // _DEV INTERFACE
        String getClassName();
        void sayHi();
};


#endif // LOG_HANDLER_H