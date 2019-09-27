#include <stdio.h>
#include <stdlib.h>

void riempifta(char file[], int *fta){
        int curs = 0;
        int ncaratteri = 0;
        int num = 0;
        FILE *f;
        f=fopen (file,"r");
        if(f != NULL) {
                size_t lung = 0;
                char *s = NULL;
                int init = 0;
                ncaratteri = getline(&s, &lung, f);
                while(ncaratteri >= 0) {
                        int i = 0;
                        char c = s[0];
                        while(c  != ';' || i < (int)lung) {
                                i++;
                                num *= 10;
                                num += (c - '0');
                                c = s[i];
                        }
                        if(init == 0) {
                                fta = (int *) malloc(sizeof(int) * num);
                                init = 1;
                        } else {
                                *(fta + curs) = num;
                                curs++;
                                ncaratteri = getline(&s, &lung, f);
                        }
                        printf("%d\n", num);
                }
        }
        fclose(f);
}
