#On peut aussi tracer la courbe, mais nous cherchons uniquement les coeficients, donc cela a peu d'importance.
plt.plot(n, theta, 'ro') # Trace theta en fonction de n, les points sont marqués par des ronds rouges.
plt.title("Angle theta en fonction de n") #Pour avoir un titre
plt.xlabel('n') #indique ce que l’on a en abscisses
plt.ylabel('theta') #indique ce que l’on a en ordonnées
thetamodel =model[0]*n #On crée le tableau de valeurs associées au modèle, ici le polynôme theta = a * n
plt.plot(n, thetamodel, 'b:') #On trace la droite associée au polynôme.
plt.show()