#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>


struct msgbuff
{
   long            mtype;	/* typ wiadomosci */
   char            mtext[300];  /* tekst wiadomosci */
}  mbuf;

main(){

   char buf[300];
   long type;

   key_t klucz; 
   int mqId;    
   klucz = ftok(".",'Q');
   if ((mqId = msgget((key_t) klucz, 0600 | IPC_CREAT)) == -1)
   {
      perror("msgget_tworz");
      return -1;
   }
	for(;;){
		bzero(mbuf.mtext,sizeof(mbuf.mtext));
		printf("\nPodaj typ komunikatu jaki chcesz odebrac: ");
		scanf("%ld",&type);
		if(msgrcv(mqId, &mbuf, sizeof(mbuf.mtext), type, 0)==-1){ 
			perror("blad odczytu");
			return 2;
		}
		else {
			printf("Odebralem komunikat typu %d : %s\n",mbuf.mtype, mbuf.mtext);
		}
	}
}

