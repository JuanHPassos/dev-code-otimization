/* Teste Cache(c) com alocação Dinámica(d) e técnica Normal(n) */
#include<stdio.h>
#include "tecnicas.h"

int main(void)
{
    double *mat_a = (double*) malloc(SIZE*SIZE*sizeof(double));
    double *mat_b = (double*) malloc(SIZE*SIZE*sizeof(double));
    double *mat_c = (double*) calloc(SIZE*SIZE, sizeof(double));

    // Inicializar valores
    inicializar_matrizes(mat_a);
    inicializar_matrizes(mat_b);

    // Multiplica matriz sem otimização
    multiplicar_matrizes_normal(mat_a, mat_b, mat_c);

    return 0;
}