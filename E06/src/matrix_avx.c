#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>  
#include <immintrin.h> // Para intrínsecas AVX e FMA


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
        (*A)[i] = 1.0f; // Matriz A = 1.0
        (*B)[i] = 2.0f; // Matriz B = 2.0
        (*C)[i] = 0.0f; // Matriz C = 0.0
    }
}

/**
 * @brief Multiplicação de Matrizes Vetorizada (GEMM AVX)
 * C = A * B + C
 * * O loop 'j' mais interno é vetorizado para processar 8 floats por vez.
 */
void gemm_avx(float *A, float *B, float *C) {
    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < N; ++k) {
            
            __m256 vec_a = _mm256_broadcast_ss(&A[i*N + k]);

            //  Loop J processa em blocos de 8
            for (int j = 0; j < N; j += 8) {
                
                float* b_addr = &B[k*N + j];
                float* c_addr = &C[i*N + j];

                //  Carrega 8 floats de B (não alinhados)
                __m256 vec_b = _mm256_loadu_ps(b_addr);
                //  Carrega 8 floats de C (não alinhados)
                __m256 vec_c = _mm256_loadu_ps(c_addr);

                // OPERAÇÃO VETORIZADA: C = (A*B) + C
                vec_c = _mm256_fmadd_ps(vec_a, vec_b, vec_c);

                _mm256_storeu_ps(c_addr, vec_c);
            }
        }
    }
}


int main() {
    float *A, *B, *C;
    double t_inicio, t_fim, t_execucao;


    init_matrices(&A, &B, &C);


    t_inicio = get_time_sec();
    gemm_avx(A, B, C);
    t_fim = get_time_sec();
    t_execucao = t_fim - t_inicio;


    free(A);
    free(B);
    free(C);

    printf("%.6f\n", t_execucao);

    return 0;
}