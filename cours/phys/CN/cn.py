# 1
import numpy as np
import matplotlib.pyplot as plt

r = np.array([1.381, 1.430, 1.535, 1.629,
              1.666, 1.636, 1.548, 1.441, 1.382]) * 149.6e6  # en km
theta = np.array([0, 53, 100, 141, 178, 215, 255, 301, 354])  # en degres

x, y = r * np.cos(np.radians(theta)), r * np.sin(np.radians(theta))

plt.plot(x, y, 'o-')
plt.show()

# On a bien une ellipse
# END 1

# 2
A = np.array([1/2 * r[i] * r[i+1] * np.sin(np.radians(theta[i+1] - theta[i])/2) for i in range(len(r)-1)])
print(A)

# On a bien une aire constante

# END 2

# 3

vitesse_aero = np.mean(A)/(84*24*60*60)
C = 2*vitesse_aero
print(C)

# END 3
