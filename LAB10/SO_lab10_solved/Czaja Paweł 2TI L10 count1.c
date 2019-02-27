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
	for(i=1;i<200;i=i+2){
		if(i!=1){
			P(semid, 0);
		}		/* Opuszczenie pierwszej semafory.
				   Dla i=1 semafora nie jest opuszczana,
				   poniewaz jej stan poczatkowy, ustawiony przez
				   funkcje Tworz(), to opuszczony.
				   Dzieki temu nie istnieje ryzyko,
                                   ze drugi proces jako pierwszy wejdzie
                                   do sekcj krytycznej. */

	/* poczatek sekcji krytycznej */
        	for(j=0;j<i;j++){
                	printf("%d ",i);
                	fflush(stdout);
        	}
		sleep(1);
        	printf("\n");
	/* koniec sekcji krytycznej */

		V(semid, 1);	/* Podniesienie drugiej semafory */
	}
	
	Usun(semid);		/* Proces pierwszy jako ostatni wchodzi 
				do sekcji krytycznej, wiec to on musi
                                usunac zbior semaforow */
	
	return 0;
}

