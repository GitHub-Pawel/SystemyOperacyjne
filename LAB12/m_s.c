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

   key_t klucz; 
   int mqId;    
   klucz = ftok(".",'Q');
   if ((mqId = msgget((key_t) klucz, 0600 | IPC_CREAT)) == -1)
   {
      perror("msgget_tworz");
      return -1;
   }
	for(;;){
		bzero(buf,sizeof(buf));
		printf("\nPodaj typ komunikatu: ");
		scanf("%ld",&mbuf.mtype);
		printf("\nPodaj tresc: ");
		scanf("%s",buf);
		if(buf[0]=='q') 
			return(msgctl(mqId, IPC_RMID, 0));
		strcpy(mbuf.mtext,buf);
		msgsnd(mqId, &mbuf, strlen(buf), 0);
	}
}

