#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>


#define MAX 1024
int A[MAX][MAX], B[MAX][MAX+16], C[MAX][MAX];
int num_thread=0;
double start=0.0, end=0.0, t=0.0;


//vector i,k,j
void RellenarMatriz_i_k_j(){
    omp_set_num_threads(num_thread);
    #pragma omp parallel
    {        
        #pragma omp for schedule(static) nowait
        for(int i=0; i<MAX; i++){
            //#pragma omp schedule(static) nowait
            for(int k=0; k<MAX; k++){
                //#pragma omp schedule(static) nowait
                for(int j=0; j<MAX; j++){
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }
}


void main (){
    printf("Introduce el numero de hilos que desee (2,4,8,16,32,64)\n");
    scanf("%d", &num_thread);
    srand(time(NULL));
    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX;j++){
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
            C[i][j] = 0;
        }
    }

        start = omp_get_wtime();
        RellenarMatriz_i_k_j();
        end = omp_get_wtime();
        t =(end - start);
        printf("%d\n", C[10][10]);
        printf("El tiempo de ejecución es: %f\n", t);
    
}

