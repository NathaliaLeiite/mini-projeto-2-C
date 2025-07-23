#define ID_SIZE 4

typedef struct {
    char code[ID_SIZE];
    int p;
    double* coef;
} Poly;

Poly ler(char* pol);

int iden(char *eq);

void soma(char *eq, Poly *lista, int a, FILE *out);
void subtracao(char *eq, Poly *lista, int a, FILE *out);