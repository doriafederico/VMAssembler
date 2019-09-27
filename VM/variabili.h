#define HALT 0
#define DISPLAY 1
#define PRINT_STACK 2
#define PUSH 10
#define POP 11
#define MOV 12
#define CALL 20
#define RET 21
#define JMP 22
#define JZ 23
#define JPOS 24
#define JNEG 25
#define ADD 30
#define SUB 31
#define MUL 32
#define DIV 33

int *stack;

int sp;

unsigned int ip; /* Registro istruction pointer */

int reg[32]; /*Sono i 32 registri su cui effettuare le operazioni*/
