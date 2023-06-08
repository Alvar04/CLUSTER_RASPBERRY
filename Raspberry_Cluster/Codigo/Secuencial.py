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

Rellenar_Matrices(global_A, global_B, global_C)

start_time = time.time()

global_C = np.dot(global_A, global_B)

end_time = time.time()

elapsed_time = end_time - start_time
print("\nTiempo de ejecución: %f segundos" % elapsed_time)
print("C_global[10][10] =", global_C[10][10])