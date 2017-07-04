#include <stdio.h>
#include <stdlib.h>
#include "tache_a.h"
#include "tache_b.h"
#include "env_mdd.h"

int main(void)
{
    pthread_t ta, tb;
    /*
    mav_msg mdd;
    init_mdd(&mdd);
    */
    // #1. creation de la BaL qui va contenir les msg normal et critique
    mav_mdd mdd;
    init_mdd(&mdd);
    mdd.gardefou = 1;


    pthread_create(&tb, NULL, tache_b, (void*)&mdd);
    pthread_create(&ta, NULL, tache_a, (void*)&mdd);

    getchar();

    pthread_cancel(tb);

    free_mdd(&mdd);

    return EXIT_SUCCESS;
}
