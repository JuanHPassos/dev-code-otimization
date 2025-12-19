#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 


// Deve ser um múltiplo de 8 para o AVX (ex: 1024, 2048)
#define N 256

/**
 * @brief Mede o tempo de execução (em segundos).
 */
double get_time_sec() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (double)tv.tv_usec * 1e-6;
}

/**
 * @brief Inicializa as matrizes A, B e C.
 * Usamos matrizes 1D para alocação contígua de memória.
 */
void init_matrices(float **A, float **B, float **C) {
    *A = (float *)malloc(N * N * sizeof(float));
    *B = (float *)malloc(N * N * sizeof(float));
    *C = (float *)malloc(N * N * sizeof(float));

    if (!*A || !*B || !*C) {
        printf("Falha na alocação de memória!\n");
        exit(1);
    }

    for (int i = 0; i < N * N; ++i) {
        (*A)[i] = 1.0f; 
        (*B)[i] = 2.0f; 
        (*C)[i] = 0.0f; 
    }
}

/**
 * @brief Multiplicação de Matrizes Escalar (GEMM)
 * C = A * B + C
 * * Implementação "ikj" para melhor localidade de cache:
 * - A[i][k] (A[i*N + k]) é acessado sequencialmente.
 * - B[k][j] (B[k*N + j]) é acessado sequencialmente (no loop j).
 * - C[i][j] (C[i*N + j]) é acessado sequencialmente (no loop j).
 */
void gemm_scalar(float *A, float *B, float *C) {
    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < N; ++k) {
            
            float r = A[i*N + k];
            for (int j = 0; j < N; ++j) {
                
                C[i*N + j] += r * B[k*N + j];
            }
        }
    }
}

int main() {
    float *A, *B, *C;
    double t_inicio, t_fim, t_execucao;


    init_matrices(&A, &B, &C);


    t_inicio = get_time_sec();
    gemm_scalar(A, B, C);
    t_fim = get_time_sec();
    t_execucao = t_fim - t_inicio;

    free(A);
    free(B);
    free(C);

    printf("%.6f\n", t_execucao);

    return 0;
}