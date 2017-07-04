#ifndef ENV_MDD_H
#define END_MDD_H

#include <pthread.h>
//#include "../../mavlink/C/common/mavlink.h"
#include "../../../../simulation/mavlink/C/common/mavlink.h"



struct mav_msg
{
    mavlink_message_t msg; // Le message mavlink
    //struct mav_msg* prec; // l'élément précédent dans la liste
    struct mav_msg* suiv; // l'élément suivant dans la liste
};

typedef struct mav_msg* mav_msg_p; // Pointeur sur un élément de la liste

typedef struct
{
    int mdd_len; // Taille de la liste doublement chainée
    mav_msg_p debut; // Début de la liste chainée
    mav_msg_p fin; // Fin de la liste chainée
    pthread_mutex_t mutex; // Mutex pour protéger les accès en lecture et écriture
    int gardefou  ; //en mode critique(valeur egale à 0) empeche de mettre dans le mdd (la BaL) des messages, mode non  critique 1
} mav_mdd;

void init_mdde(mav_mdd* mdd); // Initialisation du module de données
mav_msg_p new_msg(void); // Créer un nouvel élément qui va contenir un message mavlink
void ecrire_msge(mav_mdd* mdd, mavlink_message_t msg); // Ajouter un message mavlink au module de données
void ecrire_msg_prior(mav_mdd* mdd, mavlink_message_t msg); // Ajouter un message mavlink prioritaire au module de données
int lire_msge(mav_mdd* mdd, mavlink_message_t* msg); // Lire le plus vieux message mavlink du module de données
void free_mdde(mav_mdd* mdd); // Libérer le module de données

#endif // ENV_MDD_H
