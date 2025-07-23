#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poli.h"
#include <math.h>

Poly ler(char* pol){
    int i, j=0, k, s=0, sinal=1;
    double c=0.0;
    int grau=0, Grau=0;
    Poly a;
    strcpy(a.code, "poly");
    a.coef=NULL;
    for(i=0; pol[i]!='\0'; i++){
        if(pol[i] == 'x'){
            if (pol[i+1] == '^') {
                i += 2;
                grau = 0;
                while (pol[i] >= '0' && pol[i] <= '9') {
                    grau = grau * 10 + (pol[i] - '0');
                    i++;
                }
                i--;
            } else {
                grau = 1;
            }
        } else if ((pol[i] >= '0' && pol[i] <= '9') && (pol[i+1] != 'x' && pol[i+1] != '\0' && pol[i+1] != '+' && pol[i+1] != '-')) {
            int temp_i = i;
            while (pol[temp_i] >= '0' && pol[temp_i] <= '9') temp_i++;
            if (pol[temp_i] != 'x') {
                grau = 0;
            }
        } else if (pol[i] >= '0' && pol[i] <= '9' && (pol[i+1] == '+' || pol[i+1] == '-' || pol[i+1] == '\0')) {
             grau = 0;
        }

        if (grau > Grau) {
            Grau = grau;
        }
    }

    a.p=Grau;

    a.coef=(double*)calloc( Grau+1, sizeof(double));

    i = 0;
    while(pol[i]!='\0'){
        sinal =1;
        if (i == 0 && pol[i] == '-') {
            sinal = -1;
            i++;
        } else if (pol[i] == '+') {
            sinal = 1;
            i++;
        } else if (pol[i] == '-') {
            sinal = -1;
            i++;
        }

        c=0.0;
        int u=0;
        while (pol[i]>='0' && pol[i]<='9'){
            c = (c * 10) + (pol[i]-'0');
            i++;
            u=1;
        }

        if(!u) c=1.0;

        if (pol[i] == 'x'){
            i++;
            if(pol[i]=='^'){
                i++;
                grau =0;
                while(pol[i]<='9' && pol[i]>='0'){
                    grau= grau *10+ (pol[i]-'0');
                    i++;
                }
            }else{
                grau=1;
            }
        }else{
            grau=0;
        }

        a.coef[grau] += sinal*c;
    }
    return a;
}


int iden(char *eq){
    int i;
    for(i=0; eq[i]!='\0'; i++){
        if(eq[i]=='+'){
            return 1;
        }
        if(eq[i]=='-'){
            return 0;
        }
    }
    return 1;
}


void soma(char *eq, Poly *lista, int a, FILE *out){
    int i, b=-1, c=-1, pri=1; 

    char id1[100], id2[100];

    sscanf(eq, "%[^+-]%*c%[^\n]", id1, id2);

    for(i = 0; i < a; i++){
        if(strcmp(lista[i].code, id1) == 0){
            c = i;
        }
        if(strcmp(lista[i].code, id2) == 0){
            b = i;
        }
    }

    if(b == -1 || c == -1) return;

    int grau;
    if(lista[c].p > lista[b].p){
        grau = lista[c].p;
    }else{
        grau = lista[b].p;
    }
        for(i = 0; i <= grau; i++){
        double cc_val = 0.0;
        double bb_val = 0.0;

        if(i <= lista[c].p){
            cc_val = lista[c].coef[i];
        }
        if(i <= lista[b].p){
            bb_val = lista[b].coef[i];
        }

        double result_coef = cc_val + bb_val;

        if (fabs(result_coef) < 1e-9) {
            continue;
        }

        if (pri) { 
            if (result_coef < 0) {
                fprintf(out, "-");
            }
            if (fabs(result_coef) != 1.0 || i == 0) { 
                if (result_coef == (int)result_coef) {
                    fprintf(out, "%d", (int)fabs(result_coef));
                } else {
                    fprintf(out, "%.2lf", fabs(result_coef)); 
                }
            }
            if (i > 0) {
                fprintf(out, "x");
                if (i > 1) {
                    fprintf(out, "^%d", i);
                }
            }
            pri = 0; 
        } else {
            if (result_coef > 0) {
                fprintf(out, "+");
            } else {
                fprintf(out, "-");
            }
            if (fabs(result_coef) != 1.0 || i == 0) { 
                if (result_coef == (int)result_coef) { 
                    fprintf(out, "%d", (int)fabs(result_coef));
                } else {
                    fprintf(out, "%.2lf", fabs(result_coef));
                }
            }
            if (i > 0) { 
                fprintf(out, "x");
                if (i > 1) { 
                    fprintf(out, "^%d", i);
                }
            }
        }
    }

    if (pri) { 
        fprintf(out, "0");
    }

    fprintf(out, "\n");
}


void subtracao(char *eq, Poly *lista, int aa, FILE *out){ 
    int i, a_idx=-1, b_idx=-1, pri=1;

    char id1[100], id2[100];

    sscanf(eq, "%[^+-]%*c%[^\n]", id1, id2);

    for(i = 0; i < aa; i++){
        if(strcmp(lista[i].code, id1) == 0){
            a_idx = i; 
        }
        if(strcmp(lista[i].code, id2) == 0){
            b_idx = i; 
        }
    }

    if(b_idx == -1 || a_idx == -1) return;

    int grau;
    if(lista[a_idx].p > lista[b_idx].p){
        grau = lista[a_idx].p;
    }else{
        grau = lista[b_idx].p;
    }
    
    for(i = 0; i <= grau; i++){
        double aa_val = 0.0;
        double bb_val = 0.0;

        if(i <= lista[a_idx].p){
            aa_val = lista[a_idx].coef[i];
        }
        if(i <= lista[b_idx].p){
            bb_val = lista[b_idx].coef[i];
        }

        double result_coef = aa_val - bb_val;

        if (fabs(result_coef) < 1e-9) {
            continue;
        }

        if (pri) {
            if (result_coef < 0) {
                fprintf(out, "-");
            }
            if (fabs(result_coef) != 1.0 || i == 0) { 
                if (result_coef == (int)result_coef) { 
                    fprintf(out, "%d", (int)fabs(result_coef));
                } else { 
                    fprintf(out, "%.2lf", fabs(result_coef)); 
                }
            }
            if (i > 0) {
                fprintf(out, "x");
                if (i > 1) {
                    fprintf(out, "^%d", i);
                }
            }
            pri = 0; 
        } else {
            if (result_coef > 0) {
                fprintf(out, "+");
            } else {
                fprintf(out, "-");
            }
            if (fabs(result_coef) != 1.0 || i == 0) { 
                if (result_coef == (int)result_coef) {
                    fprintf(out, "%d", (int)fabs(result_coef));
                } else { 
                    fprintf(out, "%.2lf", fabs(result_coef));
                }
            }
            if (i > 0) {
                fprintf(out, "x");
                if (i > 1) {
                    fprintf(out, "^%d", i);
                }
            }
        }
    }

    if (pri) {
        fprintf(out, "0");
    }
    
    fprintf(out, "\n");
}