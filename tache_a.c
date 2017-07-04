#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "env_mdd.h"
#include "tache_a.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <inttypes.h> // For fixed-width uint8_t type

#define BUFFER_LENGTH 2048
#include "com.h"

void* tache_a(void *p_data)
{


// tache responsable à recevoir des msg/cmd de la partie C

	//int fd ;
	mavlink_message_t msg;
	//mav_msg* mdd = (mav_msg*)p_data;
	mav_mdd* mdd = (mav_mdd*)p_data; // recuperation de la structure mdd du thread

   /**
    mavlink_msg_rc_channels_override_pack(255, MAV_COMP_ID_ALL, &msg, 1, MAV_COMP_ID_ALL, 1900.0, 0.0, 1900.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    ecrire_msg(mdd, msg);
    sleep(10);
    mavlink_msg_rc_channels_override_pack(255, MAV_COMP_ID_ALL, &msg, 1, MAV_COMP_ID_ALL, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    ecrire_msg(mdd, msg);
    */

     //fdGlobal = connectToTelemetry();

     int i = 0;
        //unsigned char buf[2041]="";
        int rdlen;
        //unsigned char buf[2048]="";
        uint8_t buf[BUFFER_LENGTH];
  int sizii = (sizeof(buf)) * sizeof(char) ;
        unsigned int temp = 0;
        static mavlink_status_t status;


int countir = 0;
	while(1)
    {
    memset(buf, 0, BUFFER_LENGTH);
	
        rdlen = read(getFdGlobal(), buf,  sizii);
		
        if (rdlen > 0)
      	{//mavlink_status_t status;
			//printf("Bytes Received: %d\nDatagram: ", (int)rdlen);
			for (i = 0; i < rdlen; ++i)
			{
				//temp = buf[i];
				//printf("%02x ", (unsigned char)temp);
				if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status))
				{

					// Packet received
					//printf("\nReceived packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n", msg.sysid, msg.compid, msg.len, msg.msgid);
//printf( "\n ============================================ \n ");

/*===================SANS GARDEFOU========================*/

 if (msg.sysid ==255  && msg.compid ==0 ){
 if (msg.msgid == 70){

 printf("count %d",++countir);
}

if (msg.msgid == 11){

            ecrire_msg_prior(mdd,msg);
        	printf(" msg critique id %d,   \n",msg.msgid);
	}
		else{
        	printf(" msg non critique id %d,   \n",msg.msgid);
            ecrire_msge(mdd,msg);

	}

}



/*===================AVEC GARDEFOU========================*/
/**
 if (msg.sysid ==255  && msg.compid ==0 ){

	if (msg.msgid == 11){
	mavlink_set_mode_t setmode;
		mavlink_message_t msg_aux;
		msg_aux = msg;

    mavlink_msg_set_mode_decode(&msg_aux,&setmode);
    print_mode( setmode.custom_mode);

    if (setmode.custom_mode ==4 && mdd->gardefou ==0){ //holde
        mdd->gardefou = 1;
        ecrire_msg_prior(mdd,msg);

        printf("Cmd Hold a été envoyée,  Garde-fou! leves toi ! \n");

        }else if (setmode.custom_mode ==15 ){
         mdd->gardefou = 0;
        printf("Cmd Guided a été envoyée,  Garde-fou desactive ! \n");
                ecrire_msg_prior(mdd,msg);

        }


        	printf(" msg critique id %d,   \n",msg.msgid);
	}
		else{
	if (!mdd->gardefou){
		ecrire_msg(mdd,msg);
	printf("Garde_fou desactivee, msg normal id %d est envoyee,  \n",msg.msgid);

	}else

		printf(" Garde_fou ACTIVE msg normal id %d ignore, \n",msg.msgid);

	}
	}
	
	*/
	/*===================FIN AVEC/SANS GARDEFOU========================*/




					//ecrire_msg(mdd, msg);
					//printf("msg has been written to mdd");
					//countir++;
					//printf("     msg.msgid %d \n",msg.msgid);

				}
			}


}


    }

    return NULL;
}
void print_mode (int id){
switch(id){
case 0: printf("manual");  break;
case 1: printf("learning");break;
case 2: printf("steering");break;
case 4: printf("hold");break;
case 10: printf("auto");break;
case 11: printf("rtl");break;
case 15: printf("guided");break;
default: printf("mode inconnu !");
break;
}
printf("\n");
}

