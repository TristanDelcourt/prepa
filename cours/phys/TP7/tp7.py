import matplotlib.pyplot as plt

u = [1.874, 3.081, 3.765, 4.021, 4.188, 4.310]
i = [0.062, 0.038, 0.025, 0.020, 0.016, 0.014]

plt.plot(u, i, 'b+')

plt.grid(True)
plt.xlabel("i")
plt.ylabel("u")
plt.show()