/*
Tache A' qui lit un message mavlink contenue dans le module de données puis l'envoie via la télémétrie
*/
#include "rcv_mdd.h"
#include "tache_ap.h"
#include "com.h"


void* tache_a_prime(void *p_data)
{
	mavlink_message_t msg;
	//int fd;
	//int fdGlobal;

    mav_msg* mdd = (mav_msg*)p_data; // On récupère le module de données envoyé lors de la création du thread

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); // On autorise le thread a être arrêté dans le programme principal

    //fdGlobal = connectToTelemetry(); // Connexion à la télémétrie

	while(1) // Boucle principale de la tache (infinie)
    {
        msg = lire_msg(mdd); // On lit le message contenu dans le module de donnée

      printf("                                           msgid : %d\n", msg.msgid);

        sendMavlinkMsgViaTelem(getFdGlobal(), msg); // On envoie le message à la télémétrie

        usleep(50000); // Pause de 20ms
    }

    return NULL;
}


void sendMavlinkMsgViaTelem(int fd, mavlink_message_t msg)
{
    uint16_t len;
    int wlen;
    uint8_t buf[2041];

    len = mavlink_msg_to_send_buffer(buf, &msg);

    wlen = write(fd, buf, len);
    //printf("Bytes send : %d\n", wlen);

    if(wlen == -1)
        printf("Error from write: %d, %d\n", wlen, errno);
}
