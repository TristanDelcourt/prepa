import matplotlib.pyplot as plt
import numpy as np

'''
# R = 4.7k Ohm
i_court_derivation = [0.644, 0.970, 1.296, 1.615, 1.941, 2.587, -0.647, -0.974, -1.299, -1.618, -1.945, -2.590]
i_longue_derivation = [0.644, 0.970, 1.296, 1.615, 1.941, 2.587, -0.647, -0.974, -1.299, -1.618, -1.945, -2.590]
u_court_derivation = [2.998, 4.401, 6.011, 7.492, 9.007, 11.95, -2.990, -4.503, -6.013, -7.494, -9.010, -11.97]
u_longue_derivation = [2.996, 4.512, 6.026, 7.510, 9.029, 11.98, -2.998, -4.514, -6.028, -7.512, -9.031, -12.00]

# R = 900k Ohm
i_court_derivation = [3.72, 7.45, 11.13, -3.65, -7.37, -11.05]
u_court_derivation = [2.992, 6.020, 9.020, -2.994, -6.022, -9.022]

i_longue_derivation = [3.39, 6.79, 10.14, -3.32, -6.72, -10.07]
u_longue_derivation = [2.996, 6.027, 9.003, -2.998, -6.029, -9.003]


# 50 Ohm
i_court_derivation = [0.058, 0.119, 0.179, -0.061, -0.123, -0.183]
u_court_derivation = [2.998, 6.013, 9.012, -2.991, -6.018, -9.018]

i_longue_derivation = [0.180, 0.120, 0.059, -0.061, -0.123, -0.183]
u_longue_derivation = [9.031, 6.026, 2.995, -2.992, -6.028, -9.033]
'''

plt.plot(u_court_derivation, i_court_derivation, 'bo')
plt.plot(u_longue_derivation, i_longue_derivation, 'r+')

plt.grid(True)
plt.xlabel("i")
plt.ylabel("u")
plt.show()