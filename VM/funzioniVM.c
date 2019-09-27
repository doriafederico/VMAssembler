#include <stdio.h>
#include <stdlib.h>
#include "variabili.h"
#include "stack.h"

/*Corò - funzione che stampa a video la stringa passata per copia, e termina il programma
   parametri: str[] -> stringa da stampare su console
 */
void error(char str[])
{
        printf("%s\n", str);
        exit(0); /* il programma termina */
}

/*Corò - Controllo del valore p1 (primo registro) e p2 (secondo registro). Se uno dei due non è valido, interruzione del programma
   parametri: p1, p2 -> numero dei registri da controllare
 */
void controllaregistri(int p1, int p2){
        if((p1 >= 32 || p1 < 0) || (p2 >= 32 || p2 < 0)) {
                error("Registro/i non validi");
        }
}

/*Doria - Stampa a video il valore contenunto nel registro P1
   parametri: p1 -> numero del registro da stampare
 */
void display(int p1){
        controllaregistri(p1, 0);
        printf("Value: %d\n",reg[p1]);
}

/*Doria - Inserisce nello stack la somma dei due valori contenuti nei rispettivi registri P1 e P2
   parametri: p1, p2 -> numero dei registri da sommare
 */
void add(int p1, int p2){
        controllaregistri(p1, p2);
        push(stack,(reg[p1]+reg[p2]));
}

/*Doria - Inserisce nello stack la sottrazione dei due valori contenuti nei rispettivi registri P1 e P2
   parametri: p1, p2 -> numero dei registri da sottrarre
 */
void sub(int p1,int p2){
        controllaregistri(p1, p2);
        push(stack,(reg[p1]-reg[p2]));
}

/*Doria - Inserisce nello stack la moltiplicazione dei due valori contenuti nei rispettivi registri P1 e P2
   parametri: p1, p2 -> numero dei registri da moltiplicare
 */
void mul(int p1, int p2){
        controllaregistri(p1, p2);
        push(stack,(reg[p1]*reg[p2]));
}

/*Doria - Inserisce nello stack la divisione dei due valori contenuti nei rispettivi registri P1 e P2
   parametri: p1, p2 -> numero dei registri da dividere
 */
void divi(int p1, int p2){ /* div esisteva già in libreria :'( */
        controllaregistri(p1, p2);
        if(reg[p2] != 0) {
                push(stack,((reg[p1])/(reg[p2])));
        } else {
                error("Divisione per 0");
        }
}

/*Corò - Copia il valore P2 nel registro indicato (corrispondente a p1)
   parametri: p1, p2 -> p1 registro, p2 valore da inserire in p1
 */
void mov(int p1, int p2){
        controllaregistri(p1, 0);
        reg[p1] = p2;
}

/*Doria - Stampa a video tutti gli elementi dello stack, partendo dall'indice SPCOPY (equivalente a sp -1)
   fino all'indice SPCOPY - P1
   La pop viene usata per prendere i valori da stampare da una copia dello stack */
void print_stack (int p1){
        int i; /* Indice dello stack */
        int spcopy  = (sp) - 1;
        int *cstack = stack; /* Copia dello stack su cui operare*/
        controllaregistri(p1, 0);
        for (i = spcopy; i >= spcopy - p1; i-- ) {
                printf("Indice: %d Value: %d\n",i,pop(cstack));
        }
}

/* Doria e Coro'
   parametri: file[]-> nome del file, **fta -> puntatore all'array dinamico contenente le istruzioni e i valori del file cvm, *numlinee -> indirizzo alla variabile che indica la lunghezza di fta
 */
void riempifta(char file[], int **fta, int *numlinee){
        int curs = 0; /* indice con cui scorrere nell'array fta */
        int ncaratteri = 0; /* variabile indicante il numero di caratteri per riga */
        int num = 0; /* numero da inserire in fta */
        FILE *f; /* file di input da processare */
        f=fopen (file,"r");
        if(f != NULL) {
                size_t lung = 0;
                char *s = NULL;
                int init = 0;
                ncaratteri = getline(&s, &lung, f); /* lunghezza stringa */
                if(ncaratteri > 0) {
                        while(ncaratteri > 0) {
                                int flag = 0; /* serve per capire se c è un numero o no */
                                int i = 0;
                                char c;
                                while(i<((int)lung) && (c=s[i])!=';' && c!=' ' && c <='9' && c>='0') {
                                        flag = 1;
                                        num *= 10;
                                        num += (c - '0');
                                        i++;
                                }
                                if(flag == 1) {
                                        flag = 0;
                                        if(init == 0) {
                                                *fta = (int *) malloc(sizeof(int) * num);         /* allochiamo fta */
                                                (*numlinee) = num;
                                                init = 1;
                                        } else {
                                                *((*fta)+curs) = num;
                                                curs++;
                                        }
                                        num = 0;
                                }
                                ncaratteri = getline(&s, &lung, f); /* passaggio alla riga successiva */
                        }
                        free(s);
                } else {
                        error("File vuoto");
                }
        }
        fclose(f);
}
