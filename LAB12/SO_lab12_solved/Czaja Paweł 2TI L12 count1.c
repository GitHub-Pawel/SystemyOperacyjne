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

   mbuf.mtype = 1;              /* proces pierwszy będzie
                                generował wyłącznie
                                komunikaty typu 1 */
   int i;
   int j;
   for(i=1;i<200;i=i+2){
      if(i != 1){               /* dla i=1 program nie będzie
                                oczekiwał na komunikat,
                                ponieważ musi zainicjować
                                proces wyświetlania */

         if(msgrcv(mqId, &mbufNull, 0, 2, 0)==-1){
                                /* proces pierwszy nasłuchuje
                                komunikatu typu 2 */

            perror("blad odczytu");
			            return 2;
         }
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
                                /* proces pierwszy
                                generuje komunikat typu 1 */
   }

   return(msgctl(mqId, IPC_RMID, 0));
                                /* proces pierwszy jako
                                ostatni wchodzi do sekcji
                                krytycznej, więc to on musi
                                na końcu usunąć kolejkę */
}