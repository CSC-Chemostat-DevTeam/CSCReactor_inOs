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