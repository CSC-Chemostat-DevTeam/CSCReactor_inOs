// ----------------------------------------------------------------------------
// LOOP

long _loop_init_time = 0.0;
long _loop_counter = 0;

// ----------------------------------------------------------------------------
// DO SUBSYSTEM

long _led1_acc = 0;
long _led2_acc = 0;
Timer _do_timer;
bool _do_enable_flag = true;

// ----------------------------------------------------------------------------
// HEATER SUBSYSTEM

OneWire _one_wire(HEATER_T_SENSOR_PIN);
DallasTemperature _T_sensor(&_one_wire);
float _heater_temp_val = 0.0; // celsius
Timer _heater_timer;
bool _heater_enable_flag = true;

// ----------------------------------------------------------------------------
// PUMP SUBSYSTEM

long _pump_pulse_counter = 0;
Timer _pump_timer;
bool _pump_enable_flag = true;

// ----------------------------------------------------------------------------
// STIRREL SUBSYSTEM

Timer _stirrel_timer;
bool _stirrel_enable_flag = true;

// ----------------------------------------------------------------------------
// IO SUBSYSTEM

bool _io_print_force_flag = true;
Timer _io_print_timer;
Concurrent _io_ctask;

// Input reading
const byte _IO_INPUT_KEY_BUFF_LENGTH = 5;
const byte _IO_INPUT_VALUE_BUFF_LENGTH = 24;
char _io_input_key_buff[_IO_INPUT_KEY_BUFF_LENGTH];
char _io_input_val_buff[_IO_INPUT_VALUE_BUFF_LENGTH];
bool _io_input_isvalid = false;
