#include <stdio.h>
#include <stdlib.h>
#include "env_mdd.h"

void init_mdde(mav_mdd* mdd)
{
    if(mdd)
    {
        pthread_mutex_init(&(mdd->mutex) ,NULL);
        mdd->mdd_len = 0;
        mdd->debut = NULL;
        mdd->fin = NULL;
        mdd->gardefou = 0; //desactivee
    }
}

mav_msg_p new_msg(void)
{
    mav_msg_p msg = NULL;

    msg = (mav_msg_p)malloc(sizeof(struct mav_msg));

    if(msg)
    {
        msg->suiv = NULL;
        /*msg->prec = NULL;*/

        return msg;
    }
    else
        return NULL;
}

void ecrire_msge(mav_mdd* mdd, mavlink_message_t msg)
{
    mav_msg_p m = NULL;

    if(mdd)
    {
        m = new_msg();

        if(m)
        {
            pthread_mutex_lock(&(mdd->mutex));

            m->msg = msg;
            m->suiv = NULL;

            if(mdd->fin)
                mdd->fin->suiv = m;
            else
                mdd->debut = m;

            /*m->prec = mdd->fin;*/
            mdd->fin = m;
            mdd->mdd_len++;

            pthread_mutex_unlock(&(mdd->mutex));
        }
    }
}

void ecrire_msg_prior(mav_mdd* mdd, mavlink_message_t msg)
{
    mav_msg_p m = NULL, tmp = NULL, del = NULL;

    if(mdd)
    {
        m = (mav_msg_p)malloc(sizeof(struct mav_msg));

        if(m)
        {
            pthread_mutex_lock(&(mdd->mutex));

            m->msg = msg;
           //m->prec = NULL;

            if(mdd->debut);
                //mdd->debut->prec = m;
            else
                mdd->fin = m;

            m->suiv = mdd->debut;
            mdd->debut = m;

            //Suppression du reste de la file d'attente
            tmp = mdd->debut->suiv;
            tmp= NULL;

            /*while(tmp)
            {
                del = tmp;
                tmp = tmp->suiv;
                free(del);
                //del = NULL;
            }
            */

            mdd->mdd_len = 1;

            pthread_mutex_unlock(&(mdd->mutex));
        }/*
        free_mdd(mdd);
        init_mdd(mdd);
        ecrire_msg(mdd,msg);
        }*/
}
}
int lire_msge(mav_mdd* mdd, mavlink_message_t* msg)
{
    int retour = 0;
    mav_msg_p m = NULL;
pk
    if(mdd)
    {
        pthread_mutex_lock(&(mdd->mutex));

        if(mdd->mdd_len > 0)
        {
            *msg = mdd->debut->msg;

            mdd->mdd_len--;
            retour = 1;

            m = mdd->debut;

            /*if(mdd->debut->suiv)
                mdd->debut->suiv->prec = NULL;*/

            mdd->debut = mdd->debut->suiv;
            free(m);

            if(!mdd->mdd_len)
                mdd->fin = NULL;
        }

        pthread_mutex_unlock(&(mdd->mutex));
    }

    return retour;
}

void free_mdde(mav_mdd* mdd)
{
    mav_msg_p tmp = NULL, del = NULL;

    if(mdd)
    {
        tmp = mdd->debut;

        while(tmp)
        {
            del = tmp;
            tmp = tmp->suiv;
            free(del);
            del = NULL;
        }

        mdd->debut = NULL;
        mdd->fin = NULL;
        mdd->mdd_len = 0;

        pthread_mutex_destroy(&(mdd->mutex));
    }
}
