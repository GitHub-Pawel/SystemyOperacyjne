#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

main(){

   key_t klucz; 
   int mqId;    
   struct msqid_ds stat;

   klucz = ftok(".",'Q');
   if ((mqId = msgget((key_t) klucz, 0600 | IPC_CREAT)) == -1)
   {
      perror("msgget_tworz");
      return -1;
   }
   msgctl(mqId,IPC_STAT,&stat);
   stat.msg_qbytes=10;
   msgctl(mqId,IPC_SET,&stat);
}

