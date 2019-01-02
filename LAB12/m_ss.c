#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msgbuff
{
   long		mtype;	/* typ wiadomosci */
   char		cos[20];
   int		num;
   char		mtext[300];  /* tekst wiadomosci */
}  mbuf;

main(){

   char buf[300];
   char cos[20];
   int	nn;

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
		bzero(cos,sizeof(cos));
		nn=0;
		printf("\nPodaj typ komunikatu: ");
		scanf("%ld",&mbuf.mtype);
		printf("\nPodaj tresc: ");
		scanf("%s",buf);
		printf("\nPodaj cos: ");
		scanf("%s",cos);
		printf("\nPodaj liczbe: ");
		scanf("%d",&nn);
		if(buf[0]=='q') 
			return(msgctl(mqId, IPC_RMID, 0));
		strcpy(mbuf.mtext,buf);
		strcpy(mbuf.cos,cos);
		mbuf.num=nn;
		msgsnd(mqId, &mbuf, sizeof(mbuf)-sizeof(long), 0);
	}
}

