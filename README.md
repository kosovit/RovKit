# RovKit
Development of an embedded API for controlling commands and the messages between the autopilot of a rover and a ground station
## Compile: 
change #include "../../../../simulation/mavlink/C/common/mavlink.h" in env_mdd.h to the appropriate mavlink library 
compile with bash compile.sh

**C development (modular and multithread) which connects in the
autopilot via UDP / TCP and in the ground station via Telemetry**
** Development of an algorithm to control and synchronize cmds/msgs
(mailbox and semaphore)**
