#ifndef TACHE_BP_H
#define TACHE_BP_H

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/time.h>
#include <time.h>
#include <arpa/inet.h>

#include "../../../../simulation/mavlink/C/common/mavlink.h"

#define BUFFER_LENGTH 2048
#define TARGET_IP "127.0.0.1"
#define UDP_PORT 14551
#define TCP_PORT 5763

void* tache_b_prime(void* p_data);

#endif // TACHE_BP_H
