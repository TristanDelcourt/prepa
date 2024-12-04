import matplotlib.pyplot as plt
import numpy as np
from math import sqrt

L = 100
N = 200
MAX_ITERATION = 100000
V0 = 1000.

def condensateur(V0, N):
    v = [[0. for _ in range(N)] for _ in range(N)]
    allowed = [[True for _ in range(N)] for _ in range(N)]

    for i in range(N):
        for j in range(N):
            if i == 0 or j == 0 or i == N-1 or j == N-1:
                v[i][j] = V0
                allowed[i][j] = False
            elif i == N//3:
                if N//3 <= j <= int(N*2/3):
                    v[i][j] = V0
                    allowed[i][j] = False
            elif i == int(N*2/3):
                if N//3 <= j <= int(N*2/3):
                    v[i][j] = -V0
                    allowed[i][j] = False
            else:
                continue
            
    return v, allowed

v, allowed = condensateur(V0, N)

k = 0
e = 0
while k < MAX_ITERATION and e > 0.01:
    e = 0
    v_prev = np.copy(v)
    for i in range(N):
        for j in range(N):
            if allowed[i][j]:
                v[i][j] = (v_prev[i-1][j] + v_prev[i][j-1] + v_prev[i][j+1] + v_prev[i+1][j])/4
            e += (v[i][j] - v_prev[i][j])**2

    e = sqrt(e/N**2)
    k+=1
                

x = np.linspace(0, L, N)
y = np.linspace(0, L, N)

plt.contour(y, x, v, 10)
plt.show()