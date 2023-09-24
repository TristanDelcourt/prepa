# Info

## _Algorithmes et programmes_

1. Définition:\
   Un algorithme est une suite d’opérations sur un ou plusieurs données, appelées des **entrées** afin de construire un résultat, appelé **sortie**

2. Exemple: Valeur absolue d’un réel\
   \
   Entrée : a réel\
   Sortie : |a|
   
   ```
   si a > 0 :
       renvoyer a
   sinon :
       renvoyer -a
   ```

3. Exemple: algorithme d’Euclide\
   \
   Entrée : a, b entiers positifs\
   Sortie PGCD de a et b
   
   ```
   tant que b != 0 :
       r <- reste de la division euclidienne de a par b
       a <- b
       b <- r
   renvoyer a
   ```

4. Caractéristique principale d’un algorithme :\
   Il est composé de petites instructions élémentaires.

5. Définitions: \
   La traduction d’un algorithme dans un langage de programmation s’appelle un programme. On dit que l’on implémente l’algorithme.\
   \
   Un langage haut niveau est plus proche du langage naturel
   Un langage bas niveau est plus proche du langage machine\
   C - bas niveau\
   Ocaml - haut niveau\
   \
   Certains langages sont traduits en langage machine à la volée pendant l’exécution, ont dit qu’ils sont interprétés.
   Certains langages sont compilés\
   \
   Interprétés: Python, Ocaml\
   Compilés: C, OCaml

## _Les éléments d’un langage de programmation_

1. Définition:\
   Un langage de programmation est défini par :
   
   - L’ensemble des symboles autorisés, l’alphabet
   - L’ensemble des mots/ groupes de symboles, le lexique
   - Les règles indiquant comment les du langage peuvent être assemblés, la syntaxe
   - La manière d’on on interprète une suite de mots c’est-à-dire le sens qu’on lui donne, la sémantique

2. Exemples:
   
   - Français :
     - Alphabet
     - Lexique : dictionnaire
     - Grammaire (Sujet – verbe – COD)
     - Sémantique : aussi le dictionnaire
   - Python:
     - Alphabet
     - Mots clés (def, while, if, return…) et noms de variable
     - Forme du code: `def fonction(bob):`
     - Interpréteur Python
