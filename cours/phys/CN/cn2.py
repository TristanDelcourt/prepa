import numpy as np
import matplotlib.pyplot as plt

# 1

a = np.array([0.387, 0.723, 1.0, 1.524, 5.203, 9.555, 19.22, 30.10]) * 149.6e9  # en m
T = np.array([87.97, 224.7, 365.26, 365+322, 11*365+315, 29*365+167, 84*365+7, 164*365+280]) *24*3600  # en s

a_3 = a**3
T_2 = T**2

plt.plot(T_2, a_3, 'o')
plt.xlabel("$a^3$ (m$^3$)")
plt.ylabel("$T^2$ (s$^2$)")
# plt.show()

# END 1

# 2

c, d = np.polyfit(T_2, a_3, 1)
plt.plot(T_2, c*T_2 + d)
plt.show()

M = 4*np.pi**2*c / 6.67e-11
print(M)

# on trouve M = 2.00e30 kg

# END 2
