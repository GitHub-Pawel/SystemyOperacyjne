#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <string.h>

struct msgbuff
{
   long            mtype;       /* typ wiadomosci */
                                /* wiadomość nie zawiera
 *                              żadnego tesktu. O pozwoleniu
 *                              na dostęp do sekcji krytycznej
 *                              decyduje samo wystąpienie
 *                              komunikatu w kolejce. */
}  mbuf, mbufNull;

int main(){
   key_t klucz;
   int mqId;
   klucz = ftok(".",'Q');
   if ((mqId = msgget((key_t) klucz, 0600 | IPC_CREAT)) == -1)
   {
      perror("msgget_tworz");
      return -1;
   }

   mbuf.mtype = 2;              /* proces drugi będzie
                                generował wyłącznie
                                komunikaty typu 2 */

   int i;
   int j;
   for(i=2;i<200;i=i+2){
      if(msgrcv(mqId, &mbufNull, 0, 1, 0)==-1){
                                /* proces drugi nasłuchuje
                                kumunikatu typu 1 */
         perror("blad odczytu");
         return 2;
      }

/* poczatek sekcji krytycznej */
      for(j=0;j<i;j++){
	           printf("%d ",i);
         fflush(stdout);
      }
      sleep(1);
      printf("\n");
/* koniec sekcji krytycznej */
      msgsnd(mqId, &mbuf, 0, 0);
                                /* proces drugi
                                generuje komunikat typu 2 */
   }

   return 0;
}