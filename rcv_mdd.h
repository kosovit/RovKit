#ifndef RCV_MDD_H
#define RCD_MDD_H

#include <pthread.h>
#include "../../../../simulation/mavlink/C/common/mavlink.h"
/*
Structure du module de données
*/
typedef struct
{
    mavlink_message_t msg; // Message mavlink à transférer
    pthread_mutex_t mutex; // Mutex pour synchroniser l'accès au module de données
} mav_msg;

void init_mdd(mav_msg* mdd);
void ecrire_msg(mav_msg* mdd, mavlink_message_t msg);
mavlink_message_t lire_msg(mav_msg* mdd);
void free_mdd(mav_msg* mdd);

#endif // RCV_MDD_H
