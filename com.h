
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include <inttypes.h> // For fixed-width uint8_t type

extern int fdGlobal;

int com();
int connectToTelemetry();
void set_mincount(int fd, int mcount);
int set_interface_attribs(int fd, int speed);
int getFdGlobal();
