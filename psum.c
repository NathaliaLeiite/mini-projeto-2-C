#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poli.h"

int main(int argc, char* argv[]){

    if(argc!=4) return 0;

    FILE *f1 = fopen(argv[1], "rb");
    FILE *f2 = fopen(argv[2], "rb");
    if (f1 == NULL || f2 == NULL) return 0;

    char pol1[257], pol2[257];
    memset(pol1, 0, sizeof(pol1));
    memset(pol2, 0, sizeof(pol2));

    fread(pol1, sizeof(char), 256, f1);
    fread(pol2, sizeof(char), 256, f2);
    fclose(f1);
    fclose(f2);

    pol1[256] = '\0';
    pol2[256] = '\0';

    Poly lista[2];
    lista[0] = ler(pol1);
    strcpy(lista[0].code, "A");

    lista[1] = ler(pol2);
    strcpy(lista[1].code, "B");

    char op[10] = "A+B";

    FILE *saida = fopen(argv[3], "w");
    if (saida == NULL) return 0;

    soma(op, lista, 2, saida);

    fclose(saida);

    free(lista[0].coef);
    free(lista[1].coef);

    return 0;
}