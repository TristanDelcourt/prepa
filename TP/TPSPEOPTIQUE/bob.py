import numpy as np
xA = 14
xAp = 120
xO1 = 53
xO2 = 76

D = xAp - xA
d = xO2 - xO1

uxA = 1.5/np.sqrt(3)
uxAp = 0.5/np.sqrt(3)
uxO1 = uxO2 = np.sqrt((0.5/np.sqrt(3))**2 + (20/np.sqrt(3))**2)

uD = np.sqrt(uxAp**2 + uxA**2) #  D = xAp - Xa
ud = np.sqrt(uxO1**2 + uxO2**2) # d = xO2 - xO1

listeD = D*10 + np.random.uniform(-np.sqrt(3) * uD, np.sqrt(3) * uD, 10000)
listed = d*10 + np.random.uniform(-np.sqrt(3) * ud, np.sqrt(3) * ud, 10000)

listefp = (listeD**2 - listed**2)/(4*listeD)

print(listefp.std())
print(listefp.mean())

Zscore = abs(listefp.mean() - 250)/listefp.std()
print(Zscore)