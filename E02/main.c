#include<stdio.h>
#include<stdlib.h>
#include<time.h>

const int SIZE = 100;

// Prototipagem
void inicializar_matrizes(double ***matriz);
void multiplicar_matrizes_normal(double ***mat_a,
                                double ***mat_b, 
                                double ***mat_c);
void multiplicar_matrizes_interchange(double ***mat_a,
                                    double ***mat_b, 
                                    double ***mat_c);
void multiplicar_matrizes_unrolling(double ***mat_a,
                                    double ***mat_b, 
                                    double ***mat_c);  
void multiplicar_matrizes_tiling(double ***mat_a,
                                double ***mat_b, 
                                double ***mat_c);                                     
                                 
int main(void)
{
    srand48(42L);
    double mat_a[SIZE][SIZE];
    double mat_b[SIZE][SIZE];
    double mat_c[SIZE][SIZE];

    // double **mat_a_din = alocar_matriz();
    // double **mat_b_din = alocar_matriz();
    // double **mat_c_din = alocar_matriz();
   
    inicializar_matrizes(&mat_a);
    inicializar_matrizes(&mat_b);
    // inicializar_matrizes(&mat_a_din);
    // inicializar_matrizes(&mat_b_din);

    // Experimentos:
    
    // 1) Sem otimização (nem de compilação) com alocação estática
    multiplicar_matrizes_normal(mat_a, mat_b, mat_c);
    
    // 2) Sem otimização (nem de compilação) com alocação dinâmica
    // multiplicar_matrizes_normal(mat_a_din, mat_b_din, mat_c_din);
    
    // 3) Loop Interchange com alocação estática
    // multiplicar_matrizes_interchange(mat_a, mat_b, mat_c);
    
    // 4) Loop Interchange com alocação dinâmica
    // multiplicar_matrizes_interchange(mat_a_din, mat_b_din, mat_c_din);

    // 5) Loop Unrolling com alocação estática
    // multiplicar_matrizes_unrolling(mat_a, mat_b, mat_c);

    // 6) Loop Unrolling com alocação dinâmica
    // multiplicar_matrizes_unrolling(mat_a_din, mat_b_din, mat_c_din);

    // 7) Loop Tiling com alocação estática
    // multiplicar_matrizes_tiling(mat_a, mat_b, mat_c);

    // 8) Loop Tiling com alocação dinâmica
    // multiplicar_matrizes_tiling(mat_a_din, mat_b_din, mat_c_din);

    return 0;
}

double **alocar_matriz()
{
    double **matriz = (**double) malloc(SIZE*sizeof(double*));
    double *aux = (*double) malloc(SIZE*SIZE*sizeof(double));

    for(int i = 0; i < SIZE; i++) matriz[i] = aux[i*SIZE];
    
    return matriz;
}

void inicializar_matrizes(double ***matriz)
{
    for(int i = 0; i < SIZE; i++) for(int j = 0; j < SIZE; j++)
    {
        (*matriz)[i][j] = drand48();
    }
}

void multiplicar_matrizes_normal(double ***mat_a,
                                double ***mat_b, 
                                double ***mat_c)
{
    for(int i = 0; i < SIZE; i++) 
        for(int j = 0; j < SIZE; j++)
            for(int k = 0; k < SIZE; k++)
            {
                (*mat_c)[i][j] = (*mat_a)[i][k]*(*mat_b)[k][j];
            }
}

void multiplicar_matrizes_interchange(double ***mat_a,
                                double ***mat_b, 
                                double ***mat_c)
{
    for(int i = 0; i < SIZE; i++) 
        for(int k = 0; k < SIZE; k++)
            for(int j = 0; j < SIZE; j++)
            {
                (*mat_c)[i][j] = (*mat_a)[i][k]*(*mat_b)[k][j];
            }
}

void multiplicar_matrizes_unrolling(double ***mat_a,
                                double ***mat_b, 
                                double ***mat_c)
{
    for(int i = 0; i < SIZE; i++) 
        for(int j = 0; j < SIZE; j++)
            for(int k = 0; k < SIZE; k+=2)
            {
                (*mat_c)[i][j] = (*mat_a)[i][k]*(*mat_b)[k][j];
                (*mat_c)[i][j] = (*mat_a)[i][k + 1]*(*mat_b)[k + 1][j];
            }
}

void multiplicar_matrizes_tiling(double ***mat_a,
                                double ***mat_b, 
                                double ***mat_c)
{
    int TILE_SIZE = 32;
    for(int x = 0; x < SIZE; x += TILE_SIZE) 
        for(int y = 0; y < SIZE; y += TILE_SIZE)
            for(int z = 0; z < SIZE; z += TILE_SIZE)
                for(int i = 0; i < SIZE; i += TILE_SIZE)
                    for(int j = 0; j < SIZE; j += TILE_SIZE)
                        for(int k = 0; k < SIZE; k += TILE_SIZE)
                        {
                            (*mat_c)[i][j] = (*mat_a)[i][k]*(*mat_b)[k][j];
                        }
}
