## NOTE: TSL235R frequency measurement scaling issue

- The TSL235R outputs a light-dependent frequency that can exceed 100–300 kHz
- at high irradiance. An Arduino (even a Mega2560) cannot reliably measure
- this range on multiple channels using pulseIn(), digitalRead() loops, or
- interrupt-based counting. CPU latency and the limited number of hardware
- interrupts make accurate multi-sensor acquisition impossible.

- For systems with many TSL235R sensors (e.g., 10-channel OD/biomass
- measurements), pulse counting must be offloaded to external hardware.
- Typical solutions are: dedicated frequency-counter ICs, ripple counters
- such as 74HC4040/74HC393, or small auxiliary microcontrollers that perform
- high-speed edge counting and periodically report results to the Arduino.

- The Arduino should only *read* the accumulated counts (or prescaled
- frequency) from these external modules. This ensures full-range operation,
- minimal pulse loss, and accurate high-frequency measurement across all
- channels.


***
## ExternalCommands and ConstantCommands
- the Arduino must be both reactive to external commands
    - called `ExternalCommands`
- and, the arduino must have an set of repeatitive tasks
    - the `ConstantCommands`

### ExternalCommands
- the current system
- they function like interrupts
- the system will try to be as real time as possible
- the Arduino is listenning for commands
- read -> parse -> exec -> response
- once executed, the command is forgotted

### ConstantCommands
- It should use the same engine than `ExternalCommands`
- but the commands are self sended
- maybe we can config also the minimal rerun frequency
- the Arduino will loop forever trying to exec those commmands
- but `ExternalCommands` will always have priorities