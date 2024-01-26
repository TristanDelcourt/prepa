# Diagramme de Bode d'un passe-bas du premier ordre

# On importe les bibliothèques numpy (pour faire des tableaux de valeurs) et pyplot (pour les graphes).
import numpy as np
import matplotlib.pyplot as plt

# On introduit la valeur de H0 et f0:
H0 = float ( input ("Valeur du gain statique: "))
f0 = float ( input ("Fréquence propre (en Hz): "))
Q = float ( input ("Facteur de qualité: "))

# On définit la fonction de transfert passe-bas du premier ordre:
def H(f, Q) :
    return H0*1j*f/(f0 *Q)/(1 + 1j*f/(f0 * Q) - (f/f0)**2)

# Découpage régulier des puissances en base 10 de la fréquence ici de 10^0 à 10^5
puissance_n = np.arange ( 0, 5, 0.01 )
f = 10**puissance_n

# La phase en degré
phase = np.angle ( H(f, Q) , 'deg' )

# Le gain en dB
GdB = 20 * np.log10 ( abs( H(f, Q) ) )

#Tracé du diagramme de Bode
plt.subplot ( 211 ) 		# Permet d’afficher plusieurs graphes (nombre de graphes (2), colonne (1), ligne (1))
plt.semilogx ( f , GdB )  		# Tracé en semilog de GdB
plt.xlabel ( "fréquence en échelle log" )
plt.ylabel ( "GdB" ) 
plt.title ( "Diagramme de Bode du gain pour le passe-bande du 2nd ordre " )
plt.grid ( True , which = "both" , linestyle = '--' ) 		  # Activation de la grille

plt.subplot(212)
plt.semilogx ( f , phase ) 		 # Tracé en semilog de la phase
plt.xlabel ( "fréquence en échelle log" )
plt.ylabel ( "Phase en degrés" )
plt.title ( "Diagramme de Bode de la phase pour le passe-bande du 2nd ordre " )
plt.grid ( True , which = "both" , linestyle = '--' )      	#Activation de la grille

#On montre le graphique
plt.show () 
