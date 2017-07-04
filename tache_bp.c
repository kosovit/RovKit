/*
Tache B' qui se connecte au simulateur, récupère les messages mavlink et les places dans le module de données
*/
#include "rcv_mdd.h"
#include "tache_bp.h"
/*
La tache B' est capable de se connecter au simulateur via TCP ou UDP. Par défaut elle utilise le protocole UDP (variable tcp = 0). Pour passer sur du TCP, modifiez tcp = 1.
*/
void* tache_b_prime(void *p_data)
{
    int sock, i = 0, tcp = 0;
	struct sockaddr_in locAddr;
	uint8_t buf[BUFFER_LENGTH];
	ssize_t recsize;
	mavlink_message_t msg;
    mavlink_status_t status;
    mav_msg* mdd = (mav_msg*)p_data; // Récupération du module de données envoyé lors de la création du thread

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); // On autoriste l'arrêt du thread depuis le programme principal

    if((sock = socket(PF_INET, (tcp) ? SOCK_STREAM : SOCK_DGRAM, (tcp) ? PF_UNSPEC : IPPROTO_UDP)) == -1) // Création de la socket pour se connecter au serveur
    {
        perror("socket()");
	    exit(EXIT_FAILURE);
    }

	memset(&locAddr, 0, sizeof(locAddr));
	locAddr.sin_family = AF_INET; // Création de l'adresse où la socket doit se connecter
	locAddr.sin_addr.s_addr = inet_addr(TARGET_IP);
	locAddr.sin_port = htons((tcp) ? TCP_PORT : UDP_PORT);

    if(tcp) // Si mode TCP
    {
        if(connect(sock, (struct sockaddr *)&locAddr, sizeof(locAddr)) == -1) // Connexion au simulateur
        {
            printf("Error MAVLink socket connection \n");
            close(sock);
            exit(EXIT_FAILURE);
        }
    }
    else // Si mode UDP
    {
        if(bind(sock, (struct sockaddr *)&locAddr, sizeof(struct sockaddr)) == -1) // Écoute du simulateur
        {
            perror("error bind failed");
            close(sock);
            exit(EXIT_FAILURE);
        }

        if(fcntl(sock, F_SETFL, O_NONBLOCK | FASYNC) < 0) // Socket configurée comme non-bloquante
        {
            fprintf(stderr, "error setting nonblocking: %s\n", strerror(errno));
            close(sock);
            exit(EXIT_FAILURE);
        }
    }

	while(1) // Boucle principale (infinie) de la tache
    {
		memset(buf, 0, BUFFER_LENGTH);
		recsize = recv(sock, (void*)buf, BUFFER_LENGTH, 0); // Réception d'un message dans un buffer

		if(recsize > 0) // Si le buffer est non vide
			for(i = 0 ; i < recsize ; ++i)
				if(mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status)) // On décode le buffer et on récupère le message s'il est complet
				    ecrire_msg(mdd, msg); // On écrit le message mavlink dans le module de données


        usleep(50000); // Pause de la boucle de 50ms
    }

    close(sock); // Fermeture de la socket (jamais atteint)

    return NULL;
}
