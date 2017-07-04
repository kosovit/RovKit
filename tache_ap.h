#ifndef TACHE_AP_H
#define TACHE_AP_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <inttypes.h>

#include "../../../../simulation/mavlink/C/common/mavlink.h"
extern int fdGlobal;

void* tache_a_prime(void *p_data);
void sendMavlinkMsgViaTelem(int fd, mavlink_message_t msg);

#endif // TACHE_AP_H
