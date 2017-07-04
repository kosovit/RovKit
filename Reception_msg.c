/*
Programme principal qui permet de récupérer les messages mavlink du simulateur pour les envoyer par la télémétrie en passant par un module de données
*/
#include <stdio.h>
#include <stdlib.h>
#include "tache_ap.h"
#include "tache_bp.h"
#include "rcv_mdd.h"

int main(void)
{
    pthread_t ta, tb; // Thread de la tache A' (télémétrie) et de la tache B' (message du simulateur)
    mav_msg mdd; // Module de données utilisé par les deux threads pour s'échanger les messages mavlink

    init_mdd(&mdd); // Initialisation du module de données

    pthread_create(&tb, NULL, tache_b_prime, (void*)&mdd); // Création du thread de la tache B'
    pthread_create(&ta, NULL, tache_a_prime, (void*)&mdd); // Création du thread de la tache A'

    getchar(); // Le programme principal est en pause tant qu'on appuie pas sur la touche Entrée

    pthread_cancel(tb); // On arrête le thread de la tâche B'
    pthread_cancel(ta); // On arrête le thread de la tâche A'

    free_mdd(&mdd); // On libère le module de données

    return EXIT_SUCCESS;
}
