#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "variabili.h"
#include "funzioniVM.h"
#include "bootstrap.h"

/*Corò e Doria - la funzione viene richiamata quando l'utente chiede l'esecuzione di un file input.cvm
   parametri: *str -> stringa contenente nome del file
 */
int esegui(char *str)
{

        FILE *fin;
        int flag = 0; /* nel caso di HALT viene portato a 1 e il programma termina */
        int *fta=NULL; /*File To Array, sarà l'array in cui in ogni cella troveremo un numero, che corrisponderà a un'istruzione da eseguire, al numero di un determinato
                          registro, o a un valore che dovrà essere usato nel corso del programma */
        fin = fopen(str, "r"); /* apertura del file in modalità sola lettura */
        if(fin == NULL) { /* controllo dell'esistenza del file */
                error("File non esistente");
        } else {
                int numlinee; /*Numero di linee contenenti un intero da processare, viene utitlizzata anche per la dimensione di fta */
                int p1, p2; /* parametri a cui verranno assegnati i valori da processare di fta (numero registri o valori) */
                int callP; /* Memorizzazione nella call della posizione successiva, in ret ip vene portato a callP */
                bootstrap(&ip);
                riempifta(str, &fta, &numlinee);

                while (((int)(ip)) < numlinee && !flag) { /* ciclo che controlla che ip non superi la dimensione massima di fta e che non sia stato chiamato HALT*/

                        int *curs; /* Cursore utilizzato per non perdere il puntatore di stack */
                        /*operazioni sui registri*/

                        switch (fta[ip])
                        {
                        case HALT:
                                flag = 1; /* fa terminare il programma */
                                (ip)++;
                                break;

                        case DISPLAY:
                                (ip)++; /* Per prendere il numero del registro */
                                display(fta[(ip)]);
                                (ip)++; /* per passare all'istruzione successiva */
                                break;

                        case PRINT_STACK:
                                (ip)++;
                                print_stack(*(fta + (ip))); /* stampo il contenuto di stack dall'ultima posizione fino a sp - n */
                                (ip)++; /* per passare all'istruzione successiva */
                                break;

                        case PUSH:
                                (ip)++;
                                controllaregistri(*(fta + (ip)), 0); /* Controllo dell'esistenza del registro (se il numero nell'array è < 0 o >= 32 il programma termina)*/
                                push(stack, reg[*(fta + (ip))]); /* push in stack del valore contenuto nel registro specificato */
                                (ip)++; /* per passare all'istruzione successiva */
                                break;

                        case POP:
                                (ip)++;
                                controllaregistri(*(fta + (ip)), 0); /* Controllo dell'esistenza del registro (se il numero nell'array è < 0 o >= 32 il programma termina)*/
                                reg[*(fta + (ip))] = pop(stack); /* pop dell'ultimo elemento nello stack, che verrà inserito nel registro indicato */
                                (ip)++; /* per passare all'istruzione successiva */
                                break;

                        case MOV:
                                (ip)++;
                                controllaregistri(*(fta + (ip)), 0); /* Controllo dell'esistenza del registro (se il numero nell'array è < 0 o >= 32 il programma termina)*/
                                p1 = *(fta + (ip)); /* numero del registro da utilizzare */
                                (ip)++;
                                p2 = *(fta + (ip)); /* valore da copiare nel registro */
                                (ip)++; /* per passare all'istruzione successiva */
                                mov(p1, p2); /* esecuzione istruzione */
                                break;

                        case CALL:
                                callP = ip + 2; /* memorizzazione dell'istruzione successiva a cui ret dovra' tornare */
                                ip = fta[ip+1]; /* indirizzo della subroutine */
                                break;

                        case RET:
                                ip = callP; /* instruction pointer portato all'istruzione dopo la call */
                                break;

                        case JMP:
                                (ip)++;
                                (ip) = *(fta + (ip)); /* assegnazione a ip dell'indirizzo a cui saltare */
                                break;

                        case JZ:
                                curs = stack; /* puntatore allo stack */
                                (ip)++;
                                p1 = *(fta + (ip)); /* assegnazione a p1 dell'indirizzo a cui saltare */
                                (ip)++;
                                if (curs[sp - 1]==0) { /* controllo che l'ultimo elemento contenuto in stack sia uguale a 0 */
                                        (ip) = p1; /* assegnazione a ip dell'indirizzo a cui saltare */
                                        pop(stack); /* rimozione dell'elemento da stack */
                                }
                                break;

                        case JPOS:
                                curs = stack; /* puntatore allo stack */
                                (ip)++;
                                p1 = *(fta + (ip));
                                (ip)++;
                                if (curs[sp - 1] > 0) { /* controllo che l'ultimo elemento contenuto in stack sia maggiore di 0 */
                                        (ip) = p1; /* assegnazione a ip dell'indirizzo a cui saltare */
                                        pop(stack); /* rimozione dell'elemento da stack */
                                }
                                break;

                        case JNEG:
                                curs = stack;  /* puntatore allo stack */
                                (ip)++;
                                p1 = *(fta + (ip));
                                (ip)++;
                                if (curs[sp - 1] < 0) { /* controllo che l'ultimo elemento contenuto in stack sia minore di 0 */
                                        (ip) = p1; /* assegnazione a ip dell'indirizzo a cui saltare */
                                        pop(stack); /* rimozione dell'elemento da stack */
                                }
                                break;

                        case ADD:
                                (ip)++;
                                p1 = *(fta + (ip)); /* assegnazione del primo registro con cui effettuare la somma */
                                (ip)++;
                                p2 = *(fta + (ip)); /* assegnazione del secondo registro con cui effettuare la somma */
                                (ip)++;
                                add(p1, p2); /* esecuzione della somma */
                                break;

                        case SUB:
                                (ip)++;
                                p1 = *(fta + (ip)); /* assegnazione del primo registro con cui effettuare la sottrazione */
                                (ip)++;
                                p2 = *(fta + (ip)); /* assegnazione del secondo registro con cui effettuare la sottrazione */
                                (ip)++;
                                sub(p1, p2); /* esecuzione della sottrazione */
                                break;

                        case MUL:
                                (ip)++;
                                p1 = *(fta + (ip)); /* assegnazione del primo registro con cui effettuare la moltiplicazione */
                                (ip)++;
                                p2 = *(fta + (ip)); /* assegnazione del secondo registro con cui effettuare la msommaoltiplicazione */
                                (ip)++;
                                mul(p1, p2); /* esecuzione della moltiplicazione */
                                break;

                        case DIV:
                                (ip)++;
                                p1 = *(fta + (ip)); /* assegnazione del primo registro con cui effettuare la divisione */
                                (ip)++;
                                p2 = *(fta + (ip)); /* assegnazione del secondo registro con cui effettuare la divisione */
                                (ip)++;
                                divi(p1, p2); /* esecuzione della divisione */
                                break;

                        default:
                                break;
                        }


                        if((int)(ip) >= numlinee) error("Indirizzo inesistente"); /* Controllo che un possibile salto a un indirizzo sia possibile,
                                                                                     in caso contrario, il programma viene interrotto con un messaggio di errore*/
                }
        }
        free(fta); /* deallocazione di fta */
        free(stack); /* deallocazione dello stack */
        fclose(fin); /* chiusura file */
        return 0;
}
