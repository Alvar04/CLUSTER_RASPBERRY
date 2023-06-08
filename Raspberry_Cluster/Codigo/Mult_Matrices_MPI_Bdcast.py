from mpi4py import MPI
import numpy as np
import time
import random

M_SIZE = 1024

def Rellenar_Matrices(A, B, C):
    for i in range(M_SIZE):
        for j in range(M_SIZE):
            global_A[i][j] = random.randint(0, 9)
            global_B[i][j] = random.randint(0, 9)
            global_C[i][j] = 0

global_A = np.zeros((M_SIZE, M_SIZE), dtype=np.float32)
global_B = np.zeros((M_SIZE, M_SIZE), dtype=np.float32)
#C = np.zeros((M_SIZE, M_SIZE), dtype=np.float32)
global_C = np.zeros((M_SIZE, M_SIZE), dtype=np.float32)

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

local_size = M_SIZE // size
local_C = np.zeros((local_size, M_SIZE), dtype=np.float32)

start_time = MPI.Wtime()
if rank == 0:
    Rellenar_Matrices(global_A, global_B, global_C)

comm.Barrier()
comm.Bcast(global_B, root=0)
comm.Scatter(global_A, local_C, root=0)

local_C = np.dot(global_A, global_B)

comm.Gather(local_C, global_C, root=0)

end_time = MPI.Wtime()

if rank == 0:
    elapsed_time = end_time - start_time
    print("\nTiempo de ejecución: %f segundos" % elapsed_time)
    print("C_global[10][10] =", global_C[10][10])

MPI.Finalize()

