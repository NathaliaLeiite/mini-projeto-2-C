#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poli.h"

int main(int argc, char* argv[]){

    if(argc!=3) return 0;
    char *pol = argv[1];
    char *nome = argv[2];
    FILE *sla = fopen(nome,"wb");
    fwrite(pol, sizeof(char),strlen(pol)+1, sla );
    fclose(sla);

    return 0;
}