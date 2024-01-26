# Effet d'un passe-bande du premier ordre sur un signal créneau

# On importe les bibliothèques numpy (pour faire des tableaux de valeurs) et pyplot (pour les graphes).
import numpy as np
import matplotlib.pyplot as plt
from math import pi

# On définit la fonction de transfert passe-bas du premier ordre:
H0 = 3
f0 = 1000
Q = 5

def H(f) :
    return (H0*1j*f/(f0 *Q))/(1 + 1j*f/(f0 * Q) - (f/f0)**2)

# La phase du filtre
def phase(f):
    return np.angle (H(f))

# Le gain du filtre
def gain(f):
    return np.abs(H(f))

# On définit la fonction de sortie u(t) :
def u(t, f):
    s = 0
    for i in range(1000):
        nv_f = (2*i+1) * f
        s += gain(nv_f)*(4/pi * 1/(2*i+1) * np.sin(2*pi*nv_f*t + phase(nv_f)))
    return s


# Tracés des 3 courbes demandées les unes en dessous des autres

plt.subplot(311) 		# pour la 1ère courbe (5 graphes en tout, 1 colonne, 1ère ligne)
f = 10
tmax = 3/f			 # J'ai choisi de tracer e(t) sur 3 périodes.
t = np.linspace(0, tmax, 100) 	# J'ai pris n=100 points
plt.plot (t, u(t,f), 'b')	# u(t) sera en bleu
plt.legend ()			# ligne obligatoire quand on écrit label dans l’instruction plot
plt.title ("Effet d'un filtre passe bas du 1er ordre")
plt.xlabel ("temps en s")
plt.ylabel ("e(t) en V pour f = 10")
plt.grid (True)

plt.subplot (312) 		# pour la 2nde courbe (5 graphes en tout, 1 colonne, 2nde ligne)
f = 1000
tmax = 3/f 
t = np.linspace (0, tmax,100) 
plt.plot (t, u(t,f), 'b')
plt.legend ()
plt.xlabel ("temps en s")
plt.ylabel("e(t) en V pour f = 1000")
plt.grid (True)

plt.subplot (313) 		# pour la 3ème courbe (5 graphes en tout, 1 colonne, 3ème ligne)
f = 10000
tmax = 3/f 
t = np.linspace (0, tmax,100) 
plt.plot (t, u(t,f), 'b')
plt.legend ()
plt.xlabel ("temps en s")
plt.ylabel ("e(t) en V pour f = 10000")
plt.grid (True)

plt.show()