# DM2

# On importe les bibliothèques nécessaires.
import numpy as np

# Formule: a = 2D(lambda)/d

# On entre les valeurs numériques.
LAMBDA = 650.0e-9

D = np.array([1.00, 1.20, 1.40, 1.60, 1.80, 2.00])  # D(m)

d = [1.6, 1.9, 2.3, 2.6, 3.0, 3.2]  # d(cm)
d = np.array([dist/100 for dist in d])  # d(m)

s1 = 1e-3  # Précision D
s2 = 0.7e-2  # Précision d

N = 10000

# Calcul de a à partir des valeurs calculées de D et d
tot_moy = []
tot_it = []
for Dk, dk in zip(D, d):
    
    DMC = Dk + s1 * np.random.uniform(-1, 1, N)
    dMC = dk + s2 * np.random.uniform(-1, 1, N)
    
    lMC = []
    for k in range(N):
        a = 2*DMC[k]*LAMBDA/dMC[k]
        lMC.append(a)
    
    lmoy = np.average(lMC)
    it = np.std(lMC)
    tot_moy.append(lmoy)
    tot_it.append(it)


#  Calcul de la moyenne et de l'incertitude-type
moy = np.average(tot_moy)
it = np.std(tot_it)

print(f"La largeur de la fente est {moy:.3e} m, avec un incertitude-type de {it:.2e} m")