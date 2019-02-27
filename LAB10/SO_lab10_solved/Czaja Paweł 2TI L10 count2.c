#include <stdio.h>
#include <unistd.h>
#include "sem.h"

int main(){
	int semid;              /* Unikalny identyfikator zbioru semaforów */
        int pid=getpid();       /* Pobranie ID procesu */
        semid=Tworz(2);         /* Utworzenie nowego zbioru semaforów (w tym
                                   przypadku dwuelementowego) na podstawie
                                   klucza lub dołączenie się do istniejącego
                                   zbioru semaforów. Uwaga: plik sem.h zostal
                                   zmodyfikowany w taki sposob, ze
                                   wszystkie nowo utworzone semafory
                                   maja ustawiony stan poczatkowy
                                   na opuszczony. */

	int i;
	int j;
	for(i=2;i<200;i=i+2){	
		
		P(semid, 1);	/* Opuszczenie drugiej semafory */

	/* poczatek sekcji krytycznej */
        	for(j=0;j<i;j++){
                	printf("%d ",i);
                	fflush(stdout);
        	}
		sleep(1);
        	printf("\n");
	/* koniec sekcji krytycznej */

		V(semid, 0);	/* Podniesienie pierwszej semafory */
	}
	
	return 0;
}

