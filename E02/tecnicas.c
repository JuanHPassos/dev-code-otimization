#include "tecnicas.h"

#include<stdio.h>

void inicializar_matrizes(double *matriz)
{
    for(int i = 0; i < SIZE; i++) 
        for(int j = 0; j < SIZE; j++)
            matriz[i*SIZE + j] = drand48();
}

void multiplicar_matrizes_normal(double *mat_a,
                                double *mat_b, 
                                double *mat_c)
{
    for(int i = 0; i < SIZE; i++) 
        for(int j = 0; j < SIZE; j++) 
            for(int k = 0; k < SIZE; k++) 
                mat_c[i*SIZE + j] += mat_a[i*SIZE + k]*mat_b[k*SIZE + j];
}

void multiplicar_matrizes_interchange(double *mat_a,
                                    double *mat_b, 
                                    double *mat_c)
{
    for(int i = 0; i < SIZE; i++) 
        for(int k = 0; k < SIZE; k++) 
            for(int j = 0; j < SIZE; j++) 
                mat_c[i*SIZE + j] += mat_a[i*SIZE + k]*mat_b[k*SIZE + j];
}

void multiplicar_matrizes_unrolling(double *mat_a,
                                    double *mat_b, 
                                    double *mat_c)
{
    for(int i = 0; i < SIZE; i++) 
    {
        for(int j = 0; j < SIZE; j++) 
        {            
            for(int k = 0; k < SIZE; k += 2)
            {
                mat_c[i*SIZE + j] += mat_a[i*SIZE + k]*mat_b[k*SIZE + j];
                mat_c[i*SIZE + j] += mat_a[i*SIZE + (k + 1)] *
                                    mat_b[(k + 1)*SIZE + j];
            }
        }
    }
}

void multiplicar_matrizes_tiling(double *mat_a,
                                double *mat_b, 
                                double *mat_c)
{
    int TILE_SIZE = 32;

    for(int ii = 0; ii < SIZE; ii += TILE_SIZE)
        for(int jj = 0; jj < SIZE; jj += TILE_SIZE)
            for(int kk = 0; kk < SIZE; kk += TILE_SIZE)
                for(int i = 0; i < TILE_SIZE; i++)
                    for(int j = 0; j < TILE_SIZE; j++)
                        for(int k = 0; k < TILE_SIZE; k++)
                            mat_c[i*j + j] += mat_a[i*k + k] * mat_b[k*j + j];
}