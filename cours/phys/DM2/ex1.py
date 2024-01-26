# 4ème expérience: détermination de lambda inconnue avec le minimum de déviation

import numpy as np
import numpy.random as rd
from math import pi, sqrt

# On entre les valeurs numériques.
n = 614e-6       # pas du réseau avec son incertitude
un = 6e-6
alpha1 = 159.91  # angles
alpha2 = 179.33
palpha = 3/30  # précision sur la mesure des angles de 3 min
N = 10000

# On crée la liste des valeurs de lambda
alpha1MC = alpha1 + palpha * rd.uniform(-1, 1, N)
alpha2MC = alpha2 + palpha * rd.uniform(-1, 1, N)
DMC = alpha2MC - alpha1MC
D_radMC = DMC * pi / 180  # donne Dmin en radian

nMC = n + un * sqrt(3) * rd.uniform(-1, 1, N)

lMC = []
for k in range(N):
    l = np.sin(D_radMC [k] / 2) * (2 / nMC[k])
    lMC.append(l)

lmoy = np.average(lMC)
ul = np.std(lMC)

print("La longueur d'onde vaut ", round(lmoy, 3), "nm.")
print("Incertitude-type sur la longueur d'onde: ", round(ul, 2), "nm.")