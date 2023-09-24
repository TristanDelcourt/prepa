'''
i = np.array([0,10,20,30,40,50,60,70,80])
i_prime = np.array([0,-10,-20,-30,-40,-50,-60,-70,-80])

plt.plot(i, i_prime, 'ro')
plt.show()

'''

import matplotlib.pyplot as plt
import numpy as np

sin_i = [0, 0.174, 0.342, 1/2, 0.643, 0.766, 0.866, 0.940,0.985]
sin_r = [0, 0.105, 0.216, 0.326, 0.423, 1/2, 0.574, 0.616, 0.643]

indices = []
for si, sr in zip(sin_i, sin_r):
    if sr!=0:
        indices.append(si/sr)
moyenne = np.average(indices)
ecart_type = np.std(indices)
print(moyenne)
print(ecart_type)


'''
[a, b] = np.polyfit(sin_r, sin_i, 1)
print(a, b)

'''