/* Teste Branch(c) com alocação Estática(e) e técnica Unrolling(u) */
#include<stdio.h>
#include "tecnicas.h"

int main(void)
{
    double *mat_a[SIZE][SIZE];
    double *mat_b[SIZE][SIZE];
    double *mat_c[SIZE][SIZE] = {{0}};

    // Inicializar valores
    inicializar_matrizes(mat_a);
    inicializar_matrizes(mat_b);

    // Multiplica matriz sem otimização
    multiplicar_matrizes_unrolling(mat_a, mat_b, mat_c);

    return 0;
}