#include <stdio.h>
#include <stdlib.h>
#include "poli.h"

int main(int argc, char* argv[]){

    if(argc!=2) return 0;

    char *nome = argv[1];

    FILE *sla = fopen(nome,"rb");

    char c;
    while (fread(&c, sizeof(char), 1, sla) == 1) {
        putchar(c);
    }

    fclose(sla);
    return 0;
}