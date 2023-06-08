#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define M_SIZE 1024

void Rellenar_Matrices(float A[M_SIZE][M_SIZE], float B[M_SIZE][M_SIZE], float C[M_SIZE][M_SIZE]) {
    int i, j;
    for (i = 0; i < M_SIZE; i++) {
        for (j = 0; j < M_SIZE; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
            C[i][j] = 0;
        }
    }
}
    float A[M_SIZE][M_SIZE];
    float B[M_SIZE][M_SIZE];
    float C[M_SIZE][M_SIZE];
    float global_C[M_SIZE][M_SIZE];

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int rank, size;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int local_size = M_SIZE / size;
    float local_C[local_size][M_SIZE];

    if (rank == 0) {
        Rellenar_Matrices(A, B, C);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(B, M_SIZE * M_SIZE, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Scatter(A, local_size * M_SIZE, MPI_FLOAT, local_C, local_size * M_SIZE, MPI_FLOAT, 0, MPI_COMM_WORLD);
    
    double start_time = MPI_Wtime();

    for (int i = 0; i < M_SIZE / size; i++) {
        for (int j = 0; j < M_SIZE; j++) {
            for (int k = 0; k < M_SIZE; k++) {
                local_C[i][j] += local_C[i][k] * B[k][j];
            }
        }
    }

    MPI_Gather(local_C, local_size * M_SIZE, MPI_FLOAT, global_C, local_size * M_SIZE, MPI_FLOAT, 0, MPI_COMM_WORLD);
    
    double end_time = MPI_Wtime();

    if (rank == 0) {
        double elapsed_time = end_time - start_time;
        printf("\nTiempo de ejecución: %f segundos\n", elapsed_time);
        printf("C_global[10][10] = %f\n", global_C[10][10]);
    }

    MPI_Finalize();
    return 0;
}
