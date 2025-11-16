#include "Base/1_config.h"
#include "Base/2_Utils.h"
#include "Base/4_CSCReactor.h"
#include "Base/3_CSVLineReader.h"
#include "Base/5_SerialDriver.h"
#include "Base/6_SerialCSVDriver.h"
#include "Base/7_InoDriver.h"

/// -------------------------
/// HANDLE MSG INTERFACE
boolean InoDriver::handleMsg()
{

    // Check target code
    if (!SerialCSVDriver::hasValString(0, "INO"))
    {
        return false;
    }

    //// ------------
    // MARK: SAY-HI
    // Example: $INO:SAY-HI%
    if (SerialCSVDriver::hasValString(1, "SAY-HI"))
    {
        InoDriver::sayHi();
        return true;
    }

    //// ------------
    // MARK: PIN-MODE
    // $INO:PIN-MODE:PIN1:MODE1:...%
    if (SerialCSVDriver::hasValString(1, "PIN-MODE"))
    {
        if (CSCReactor::devmode)
        {
            _serial_pin_mode(DRY_OP_TYPE);
        }
        else
        {
            _serial_pin_mode(NONDRY_OP_TYPE);
        }
        // run
        return true;
    }

    //// ------------
    // MARK: WRITE

    // DIGITAL-WRITE
    // $INO:DIGITAL-WRITE:PIN1:VAL1:...%
    if (SerialCSVDriver::hasValString(1, "DIGITAL-WRITE"))
    {
        if (CSCReactor::devmode)
        {
            _serial_write(DRY_OP_TYPE);
        }
        else
        {
            _serial_write(DIGITAL_OP_TYPE);
        }
        return true;
    }

    // ANALOG-WRITE
    // $INO:ANALOG-WRITE:PIN1:VAL1:...%
    if (SerialCSVDriver::hasValString(1, "ANALOG-WRITE"))
    {
        if (CSCReactor::devmode)
        {
            _serial_write(DRY_OP_TYPE);
        }
        else
        {
            _serial_write(ANALOG_OP_TYPE);
        }
        return true;
    }

    //// ------------
    // MARK: READ

    // DIGITAL-READ
    // $INO:DIGITAL-READ:PIN1:...%
    if (SerialCSVDriver::hasValString(1, "DIGITAL-READ"))
    {
        if (CSCReactor::devmode)
        {
            _serial_read(DRY_OP_TYPE);
        }
        else
        {
            _serial_read(DIGITAL_OP_TYPE);
        }
        return true;
    }

    // ANALOG-READ
    // $INO:ANALOG-READ:PIN1:...%
    if (SerialCSVDriver::hasValString(1, "ANALOG-READ"))
    {
        if (CSCReactor::devmode)
        {
            _serial_read(DRY_OP_TYPE);
        }
        else
        {
            _serial_read(ANALOG_OP_TYPE);
        }
        return true;
    }

    //// ------------
    // MARK: S-PULSE

    // DIGITAL-S-PULSE
    // $INO:DIGITAL-S-PULSE:PIN1:VAL01:TIME1:VAL11...%
    // precise/fast pulse
    if (SerialCSVDriver::hasValString(1, "DIGITAL-S-PULSE"))
    {
        if (CSCReactor::devmode)
        {
            _serial_pulse_out(DRY_OP_TYPE);
        }
        else
        {
            _serial_pulse_out(DIGITAL_OP_TYPE);
        }
        return true;
    }

    // ANALOG-S-PULSE
    // $INO:ANALOG-S-PULSE:PIN1:VAL01:TIME1:VAL11...%
    // precise/fast pulse
    if (SerialCSVDriver::hasValString(1, "ANALOG-S-PULSE"))
    {
        if (CSCReactor::devmode)
        {
            _serial_pulse_out(DRY_OP_TYPE);
        }
        else
        {
            _serial_pulse_out(ANALOG_OP_TYPE);
        }
        return true;
    }

    //// ------------
    // MARK: C-PULSE

    // DIGITAL-C-PULSE
    // $INO:DIGITAL-C-PULSE:PIN1:VAL10:TIME1:VAL11:...%
    // Concurrent
    if (SerialCSVDriver::hasValString(1, "DIGITAL-C-PULSE"))
    {
        if (CSCReactor::devmode)
        {
            _concurrent_pulse_out(DRY_OP_TYPE);
        }
        else
        {
            _concurrent_pulse_out(DIGITAL_OP_TYPE);
        }
        return true;
    }

    // ANALOG-C-PULSE
    // $INO:ANALOG-C-PULSE:PIN1:VAL10:TIME1:VAL11:...%
    // Concurrent
    if (SerialCSVDriver::hasValString(1, "ANALOG-C-PULSE"))
    {
        if (CSCReactor::devmode)
        {
            _concurrent_pulse_out(DRY_OP_TYPE);
        }
        else
        {
            _concurrent_pulse_out(ANALOG_OP_TYPE);
        }
        return true;
    }

    //// ------------
    // DOING: CREATE A CONCURRENT (NON-BLOCKING) _count_pulses2
    // use mean(time_on)/(mean(time_on) + mean(time_off))
    // each mean can be computed concurrently (there is not need to capture all pulses)

    // MARK: PULSE-IN
    // $INO:PULSE-IN:PIN:TIME%
    // TODO: 
    // - Add irradiance using 
    // -- `https://github.com/RobTillaart/TSL235R`
    // -- float irr_uW_cm2 = tsl.irradiance(pulses, (uint32_t)time);
    if (SerialCSVDriver::hasValString(1, "PULSE-IN"))
    {
        int pin = SerialCSVDriver::getValString(2).toInt();
        int time = SerialCSVDriver::getValString(3).toInt(); // sampling time ms
        unsigned long n;                                     // default
        if (CSCReactor::devmode)
        {
            n = random();
        }
        else
        {
            // n = InoDriver::_count_pulses2(pin, time);
            n = InoDriver::_count_pulses3(pin, time);
            // n = InoDriver::_count_pulses4(pin, time);
        }
        SerialCSVDriver::sendMsgResponse("read", n);
        return true;
    }

    return false;
}
