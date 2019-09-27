#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "variabili.h"


/*gestione overflow: stampa un messaggio di errore e interrompe l'esecuzione del programma */
int overflow(){
        printf("Stack overflow, esecuzione interrotta:\n");
        printf("La memoria stack non è sufficiente per arrivare al termine dell'esecuzione del programma\n");
        exit(0);
}

/*gestione underflow: stampa un messaggio di errore e interrompe l'esecuzione del programma */
void underflow(){
        printf("Stack underflow:\n lo stack è vuoto, non ci sono elementi da prelevare. Esecuzione interrotta\n");
        exit(0);
}

/* INSERISCE UN ELEMENTO IN CODA ALLA LISTA. QUANDO VERRA' ESEGUITA UNA pop,
   VERRA' PRELEVATO L'ULTIMO elem INSERITO */
void push(int *stack, int elem){
        if((stack) != NULL ) {
                if(sp < ((int)LUNGVET)) { /* Controllo che sia possibile scrivere nello stack */
                        *(stack+sp) = elem; /* Inserisco l'elemento nello stack */
                        sp++; /* Incremento il puntatore alla prossima posizione su cui scrivere */
                } else {
                        overflow();
                }
        }
}

/* Preleva un elemento dallo stack (decrementando SP). L'elemento non verrà eliminato, poichè dal decremento di sp,
   verrà sovrascritto */
int pop(int *stack){
        int res; /* Risultato che pop restituirà */
        res = 0;
        if(stack != NULL) {
                if(sp > 0) { /* Controllo che sia possibile effettuare la pop, in caso contrario, si ha underflow */
                        sp--; /* Decremento il puntatore della prossima posizione su cui scrivere */
                        res = *(stack+sp); /*Copiamo il valore nella variabile da restituire*/
                } else {
                        underflow();
                }
        }
        return res;
}
