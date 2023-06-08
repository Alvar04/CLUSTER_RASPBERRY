#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define MAX 1024
int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

int main (){

    double start = omp_get_wtime();

    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX;j++){
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
            C[i][j] = 0;
        }
    }

    for(int i=0; i<MAX; i++){
        for(int k=0; k<MAX; k++){
            for(int j=0; j<MAX; j++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    double end = omp_get_wtime();

    double time = (double) (end - start);

    printf("%d\n", C[10][10]);
    printf("El tiempo de ejecución es: %f\n", time);
    return 0;
}
