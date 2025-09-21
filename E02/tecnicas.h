#ifndef TECNICAS_H_
#define TECNICAS_H_
    
    #include<stdlib.h>
    
    #define SIZE 128

void inicializar_matrizes(double *matriz);
void multiplicar_matrizes_normal(double *mat_a,
                                double *mat_b, 
                                double *mat_c);
void multiplicar_matrizes_interchange(double *mat_a,
                                    double *mat_b, 
                                    double *mat_c);
void multiplicar_matrizes_unrolling(double *mat_a,
                                    double *mat_b, 
                                    double *mat_c);
void multiplicar_matrizes_tiling(double *mat_a,
                                double *mat_b, 
                                double *mat_c);

#endif