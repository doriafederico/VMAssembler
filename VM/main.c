#include "esegui.h"
#include "stampa.h"
#include "funzioniVM.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
   VMAssembler - Coro' Riccardo 875550, Doria Federico 873999
   Programmazione e Laboratorio - 9/6/19
   Università Ca' Foscari
 */

/*Corò - primo pezzo di codice della macchina virtuale che viene eseguito.
   argc: dimensione dell'array argv
   argv: array di puntatori a stringhe []"./vm", "esegui/stampa", "fileInput.cvm"]
   Entrambi i parametri vengono passati dal prompt dei comandi al momento dell'esecuzione della V.M. */
int main(int argc, char **argv){
        if(argc <= 3) { /* controllo che il numero di stringhe sia giusto */
                /*Controllo della validità dei comandi digitati dall'utente*/
                if(!strcmp(argv[1], "esegui")) {
                        esegui(argv[2]);
                } else if(!strcmp(argv[1], "stampa")) {
                        stampa(argv[2]);
                } else { /*Se il comando digitato non è valido, terminazione del programma*/
                        error("Comando non valido");
                }
        } else { /* terminazione del programma nel caso l'utente abbia digitato erroneamente */
                error("Inserire solo il comando di esecuziozione della V.M., il comando da eseguire (esegui/stampa) e il file in input da processare (mioFile.cvm)");
        }
        return 0;
}
