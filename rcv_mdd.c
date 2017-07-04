/*
Module de données utilisé pour transférer les messages mavlink (partie B') du simulateur vers la télémétrie (partie A').
*/
#include <stdio.h>
#include <stdlib.h>
#include "rcv_mdd.h"
/*
Procédure d'initialisation du module de données
*/
void init_mdd(mav_msg* mdd)
{
    pthread_mutex_init(&(mdd->mutex) ,NULL); // Initialisation du mutex
}
/*
Procédure d'écriture d'un nouveau message mavlink dans le module de données
*/
void ecrire_msg(mav_msg* mdd, mavlink_message_t msg)
{
    pthread_mutex_lock(&(mdd->mutex)); // Verrouillage du mutex
    mdd->msg = msg; // On écrit le message dans le module de données
    pthread_mutex_unlock(&(mdd->mutex)); // Libération du mutex
}
/*
Fonction de lecture du message mavlink contenu dans le module de données
*/
mavlink_message_t lire_msg(mav_msg* mdd)
{
    mavlink_message_t msg;

    pthread_mutex_lock(&(mdd->mutex)); // Verrouillage du mutex
    msg = mdd->msg; // On lit le message contenu dans le module de données
    pthread_mutex_unlock(&(mdd->mutex)); // Libération du mutex

    return msg;
}
/*
Procédure qui permet de libérer le module de données
*/
void free_mdd(mav_msg* mdd)
{
    pthread_mutex_destroy(&(mdd->mutex)); // Destruction du mutex
}
