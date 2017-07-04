#include <stdio.h>
#include <stdlib.h>

#include "tache_a.h"
#include "tache_b.h"

#include "tache_ap.h"
#include "tache_bp.h"

#include "rcv_mdd.h"
#include "env_mdd.h"

#include "com.h"

int main()
{
        pthread_t ta, tb, tap, tbp;
    /*
    mav_msg mdd;
    init_mdd(&mdd);
    */
    // #1. creation de la BaL qui va contenir les msg normal et critique
    //com();
    printf("fdglobal avant %d \n", fdGlobal);

int fd=com();

printf("fd %d \n", fd);
printf("fdglobal %d \n", fdGlobal);

    mav_mdd mdd;
    init_mdde(&mdd);

    pthread_create(&tb, NULL, tache_b, (void*)&mdd);
    pthread_create(&ta, NULL, tache_a, (void*)&mdd);

    mav_msg mddapbp; // Module de données utilisé par les deux threads pour s'échanger les messages mavlink

    init_mdd(&mddapbp); // Initialisation du module de données

    pthread_create(&tbp, NULL, tache_b_prime, (void*)&mddapbp); // Création du thread de la tache B'
    pthread_create(&tap, NULL, tache_a_prime, (void*)&mddapbp); // Création du thread de la tache A'


    getchar();

    pthread_cancel(tb); //TODO add cancel ta
	
    pthread_cancel(tbp); // On arrête le thread de la tâche B'
    pthread_cancel(tap); // On arrête le thread de la tâche A'

    free_mdde(&mdd);
    free_mdd(&mddapbp); // On libère le module de données

    return EXIT_SUCCESS;
}
