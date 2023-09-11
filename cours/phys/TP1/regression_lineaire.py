import matplotlib.pyplot as plt
n = [5e-3, 6.6e-3, 1e-2, 1.3e-2,1.7e-2,2.5e-2,3.3e-2] # pour les n extinctions mesurées à partir du centre
theta = [3.1e-3,4.1e-3,6.1e-3,8.2e-3,1.1e-2,1.6e-2,2.2e-2] # pour les n valeurs de q mesurées
plt.plot(n, theta, 'ro') # Trace theta en fonction de n, les points sont marqués par des ronds rouges.
plt.title("Angle theta en fonction de 1/a") #Pour avoir un titre
plt.xlabel('1/a') #indique ce que l’on a en abscisses
plt.ylabel('theta') #indique ce que l’on a en ordonnées
plt.grid() #met un quadrillage sur la figure
plt.show()
#On vérifie alors que les points sont à peu près alignés, signe que la relation donnée est validée – et que
#les mesures sont correctes.
#Pour la régression linéaire avec Python, sur l’exemple ci-dessus :
# On importe la bibliothèque matplotlib.pyplot pour tracer les courbes.
# On importe la bibliothèque numpy pour pouvoir utiliser la fonction polyfit, qui permet de trouver le polynôme qui colle le mieux à la courbe expérimentale.
import matplotlib.pyplot as plt
import numpy as np
n = np.array([5e-3, 6.6e-3, 1e-2, 1.3e-2,1.7e-2,2.5e-2,3.3e-2]) #pour pouvoir utiliser polyfit, on ne peut pas utiliser un simple ensemble de valeurs, comme on a fait ci-dessus, mais on crée une ligne de tableau.
theta = np.array([3.1e-3,4.1e-3,6.1e-3,8.2e-3,1.1e-2,1.6e-2,2.2e-2])

model = np.polyfit(n, theta, 1) #on crée le polynôme de degré 1 qui colle le plus à la courbe theta en fonction de n, donc theta = a * n +b
print(model) #Cela affiche les coefficients du polynôme précédent
#On peut aussi tracer la courbe, mais nous cherchons uniquement les coeficients, donc cela a peu d'importance.
plt.plot(n, theta, 'ro') # Trace theta en fonction de n, les points sont marqués par des ronds rouges.
plt.title("Angle theta en fonction de 1/a") #Pour avoir un titre
plt.xlabel('1/a') #indique ce que l’on a en abscisses
plt.ylabel('theta') #indique ce que l’on a en ordonnées
thetamodel =model[0]*n #On crée le tableau de valeurs associées au modèle, ici le polynôme theta = a * n
plt.plot(n, thetamodel, 'b:') #On trace la droite associée au polynôme.
plt.show()