#define MAXMEM 65536 /* Numero totale di byte (64KB) */
#define LUNGVET (MAXMEM / (sizeof(int)))

void push(int *stack, int elem);
int pop(int *stack);
