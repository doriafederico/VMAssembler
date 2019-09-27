#include "stack.h"
#include "variabili.h"
#include <stdlib.h>
#include <stdio.h>

/*Coro' Doria - inizializzazione dei registri speciali ip ed sp, e dello stack
   parametri: *ip -> instructin pointer inizializzato
 */
void bootstrap(unsigned int *ip){
        (*ip) = 0; /* istruction pointer - registro speciale */
        stack = (int *) malloc(MAXMEM / (sizeof(int))); /*allocazione di stack - UTILIZZO DELLA REGOLA LIFO*/
        sp = 0; /*STACK POINTER - REGISTRO*/
}
