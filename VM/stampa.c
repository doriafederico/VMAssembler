#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "variabili.h"
#include "funzioniVM.h"
#include "bootstrap.h"


/*Coro' e Doria*/
void stampa(char *str)
{
        FILE *fin;
        int *fta = NULL; /*File To Array, sarà l'array in cui in ogni cella troveremo un numero, che corrisponderà a un'istruzione da eseguire, al numero di un determinato
                            registro, o a un valore che dovrà essere usato nel corso del programma */
        fin = fopen(str, "r"); /* apertura del file in modalità sola lettura */

        if(fin == NULL) {/* controllo dell'esistenza del file */
                error("File non esistente");
        } else {
                int numlinee; /*Numero di linee contenenti un intero da processare, viene utitlizzata anche per la dimensione di fta */
                int p1, p2; /* parametri a cui verranno assegnati i valori da processare di fta (numero registri o valori) */
                int pos; /* indice di fta */
                bootstrap(&ip);
                riempifta(str, &fta, &numlinee);

                while (((int)ip) < numlinee) { /* ciclo che controlla che ip non superi la dimensione massima di fta */
                        /*operazioni sui registri*/

                        switch (fta[ip])
                        {
                        case HALT: /* fa terminare il programma */
                                pos = ip;
                                printf("[%d] HALT\n", pos);
                                ip++;
                                break;

                        case DISPLAY:
                                pos = ip;
                                ip++; /* Per prendere il numero del registro */
                                printf("[%d] DISPLAY R%d\n", pos, fta[ip]);
                                ip++; /* per passare all'istruzione successiva */
                                break;

                        case PRINT_STACK:
                                pos = ip;
                                ip++;
                                printf("[%d] PRINT_STACK %d\n", pos, *(fta + ip));
                                ip++;
                                break;

                        case PUSH:
                                pos = ip;
                                ip++; /* sposto il cursore di fta alla posizione successiva, per prendere il numero del registro / dato */
                                printf("[%d] PUSH R%d\n", pos, *(fta + ip));
                                controllaregistri(*(fta + (ip)), 0); /* Controllo dell'esistenza del registro (se il numero nell'array è < 0 o >= 32 il programma termina)*/
                                ip++;
                                break;

                        case POP:
                                pos = ip;
                                ip++;
                                printf("[%d] POP R%d\n", pos, *(fta + ip));
                                controllaregistri(*(fta + (ip)), 0);/* Controllo dell'esistenza del registro (se il numero nell'array è < 0 o >= 32 il programma termina)*/
                                ip++;
                                break;

                        case MOV:
                                pos = ip;
                                ip++;
                                p1 = *(fta + ip); /* numero del registro */
                                ip++;
                                p2 = *(fta + ip); /* valore da spostare nel registro */
                                ip++;
                                printf("[%d] MOV R%d %d\n", pos, p1, p2);
                                break;

                        case CALL:
                                pos = ip;
                                ip++;
                                printf("[%d] CALL %d\n", pos, fta[ip]);
                                ip++;
                                break;

                        case RET:
                                printf("[%d] RET\n", ip);
                                ip++;
                                break;

                        case JMP:
                                pos = ip;
                                ip++;
                                printf("[%d] JMP %d\n", pos, *(fta + ip));
                                ip++;
                                break;

                        case JZ:
                                pos = ip;
                                ip++;
                                printf("[%d] JZ %d\n", pos, *(fta + ip));
                                ip++;
                                break;

                        case JPOS:
                                pos = ip;
                                ip++;
                                printf("[%d] JPOS %d\n", pos, *(fta + ip));
                                ip++;
                                break;

                        case JNEG:
                                pos = ip;
                                ip++;
                                printf("[%d] JNEG %d\n", pos, *(fta + ip));
                                ip++;
                                break;

                        case ADD:
                                pos = ip;
                                ip++;
                                p1 = *(fta + ip); /* numero del primo registro */
                                ip++;
                                p2 = *(fta + ip); /* numero del secondo registro */
                                ip++;
                                printf("[%d] ADD R%d R%d\n", pos, p1, p2);
                                break;

                        case SUB:
                                pos = ip;
                                ip++;
                                p1 = *(fta + ip); /* numero del primo registro */
                                ip++;
                                p2 = *(fta + ip); /* numero del secondo registro */
                                ip++;
                                printf("[%d] SUB R%d R%d\n", pos, p1, p2);
                                break;

                        case MUL:
                                pos = ip;
                                ip++;
                                p1 = *(fta + ip); /* numero del primo registro */
                                ip++;
                                p2 = *(fta + ip); /* numero del seocondo registro */
                                ip++;
                                printf("[%d] MUL R%d R%d\n", pos, p1, p2);
                                break;

                        case DIV:
                                pos = ip;
                                ip++;
                                p1 = *(fta + ip); /* numero del primo registro */
                                ip++;
                                p2 = *(fta + ip); /* numero del secondo registro */
                                ip++;
                                printf("[%d] DIV R%d R%d\n", pos, p1, p2);
                                break;

                        default:
                                break;
                        }
                }
        }
        free(fta);
        free(stack);
        fclose(fin);
}
