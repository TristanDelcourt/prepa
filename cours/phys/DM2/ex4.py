# Recomposition en série de Fourier d'un signal créneau

# Bibliothèques

import numpy as np
import matplotlib.pyplot as plt
from math import pi

f= 100     # fréquence f en Hz du signal d'entrée, modifiable
tmax = 3/f            # J'ai choisi de tracer e(t) sur 3 périodes.

# On définit le signal d'entrée
def e(t, n):
    a = 0            # Correspond à la moyenne du signal d'entrée (ajustable)
    for i in range (n) :
        a += 4/pi * 1/(2*i+1) * np.sin((2*i+1) * 2 * pi * f * t)
        
    return a     # Il y a n termes dans la somme

t = np.linspace ( 0, tmax, 1000)     # J'ai pris n = 1000 points
plt.plot ( t, e(t, 50), 'r')          # Tracé pour n = 2 , modifiable
plt.xlabel ("temps t en s")
plt.ylabel ("e(t)")
plt.grid()
plt.show()