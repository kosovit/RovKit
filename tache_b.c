#include "env_mdd.h"
#include "tache_b.h"

void* tache_b(void *p_data)
{
    int sock;
	struct sockaddr_in locAddr;
	uint8_t buf[BUFFER_LENGTH];
	int bytes_sent;
	uint16_t len;
	mavlink_message_t msg;
	//mav_msg* mdd = (mav_msg*)p_data;
	mav_mdd* mdd = (mav_mdd*)p_data;

	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    if((sock = socket(PF_INET, SOCK_STREAM, PF_UNSPEC)) == -1)
    {
        perror("socket()");
	    exit(EXIT_FAILURE);
    }

	memset(&locAddr, 0, sizeof(locAddr));
	locAddr.sin_family = AF_INET;
	locAddr.sin_addr.s_addr = inet_addr(TARGET_IP);
	locAddr.sin_port = htons(TCP_PORT);

    if(connect(sock, (struct sockaddr *)&locAddr, sizeof(locAddr)) == -1)
    {
        printf("Error MAVLink socket connection \n");
        close(sock);
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        memset(&msg, 0, sizeof(mavlink_message_t));

        if(lire_msge(mdd, &msg))
               // if(0)

        {
            len = mavlink_msg_to_send_buffer(buf, &msg);
            bytes_sent = sendto(sock, buf, len, 0, (struct sockaddr *)&locAddr, sizeof(struct sockaddr_in));
            //printf("Bytes sent : %d, checksum : %d\n", bytes_sent, msg.checksum);

            if(bytes_sent == -1)
                perror("sendto()");
        }

        usleep(50000);
    }

    close(sock);

    return NULL;
}

