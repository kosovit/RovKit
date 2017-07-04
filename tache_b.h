#ifndef TACHE_B_H
#define TACHE_B_H

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
#include <arpa/inet.h>

#define BUFFER_LENGTH 2048
#define TARGET_IP "127.0.0.1"
#define TCP_PORT 5763

void* tache_b(void* p_data);

#endif // TACHE_B_H
