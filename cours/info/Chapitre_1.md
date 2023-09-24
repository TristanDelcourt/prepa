# Chapitre 1: Premiers programmes en C

## Fonctions

<u>Exemple:</u> Programme qui calcule le max de 4 nombres a, b, c, d

```c
#include <stdio.h>

float max2(float a, float b){
    //renvoie le max entre a et b

    if (a>b){
    return a;
    }

    else{
    return b;
    }
}

int main(){
    float a, b, c, d;
    a = 3;
    b= 2;
    c = 0.5;
    d = 5;

    float mt = a;

    mt = max2(mt, b);
    mt = max2(mt, c);
    mt = max2(mt, d);

    printf("Le max est %f\n", mt);
    return 0;
}
```

Les fonctions améliores l'organisation et la lisibilité du code et le rendent modulaire.

### Syntaxe des fonctions

type_retour nom_fonction(type1 param1, type2 param2...){

    <FONCTION>

}

On spécifie le type de retour de la fonction ainsi que le type de chaque paramètre. le k+1-uplet (type_1,...type_k, type_retour) s'appelle la signature de la fonction

On note parfois type_1 X type_2 X ... type_k $\longrightarrow$ type_retour

<u>Exemple:</u>

```c
float bla(int a, int b, float c){
    ...
}
```

int X int X float $\longrightarrow$ float

Certaines fonctions de renvoient rien (procédures).

<u>Exemple:</u>

```c
void afficher_double(float a){
    printf("%f", 2*a)
}
```

NE PAS CONFONDRE AFFICHER ET RENVOYER

#### Commentaires

Il faut toujours commenter les fonctions qu'on écrit. Un commentaire de fonction doit faire apparaître le nom de tous les paramètres et expliquer ce que fait/renvoie la fonction.

### Appelles de fonction

Lorsqu'on utilise une fonction définie, on dit qu'on l'appelle

```c
#include <stdio.h>

float moyenne(float a, float b){
    float m = (a+b)/2;
    return m;
}

int main(){
    float x = 18.2;
    float y = 17.6;
    float c = moyenne(x, y);
    printf("%f\n", c);
    return 0;
}
```

## Portée des variables

<u>Définition:</u> La portée d'une variable est l'ensemble des lignes où cette variable existe.

### Variable locale

### Passage par valeur

Une fonction en C ne peut pas modifier ses arguments.

`&x` = adresse de x (passage par adresse)

### Variable globale

En C, si une variable est déclarée en dehors des fonctions, elle est <u>global</u>.

### Fonction vs fonction

fonction info $\neq$ fonction maths

impératif $\neq$ descriptif

## Boucles

### Boucle while

Une boucle while/tant que sert à exécuter des instruction tant qu'une condition est vérifiée.

<u>Exemple:</u> $\forall n\in\mathbb{N}, n! = \prod_{i=1}^n i$

Algorithme fonctionel.

```
Entrée: n entier
Sortie: n!

r <- 1
i <- 1
tant que i <= n
    r <- r*i
    i <- i + 1
renvoyer r
```

| ligne   | 1   | 2   | 4   | 5   | 4   | 5   | 4   | 5   |
| ------- | --- | --- | --- | --- | --- | --- | --- | --- |
| i       | ?   | 1   | 1   | 2   | 2   | 3   | 3   | 4   |
| r       | 1   | 1   | 1   | 1   | 2   | 2   | 6   | 6   |
| i$\le$n | ?   | oui | oui | oui | oui | oui | oui | non |

```c
//renvoie n factorielle
int factoriel(int n){
    int r = 1;
    int i = 1;
    while(i<=n){
        r = r*i;
        i = i+1;
    }
}
```

<u>Exemple:</u>

Pour $n\in\mathbb{N}$, on appelle racine entière de $n$, c'est $\lfloor\sqrt{n}\rfloor$ , i.e le plus grand entier $k$ tel que $k^2\le n$

16 $\longrightarrow$ 4

21 $\longrightarrow$ 4

27$\longrightarrow$ 5

```
Entrée: n entier
Sortie: floor(sqrt(n)
k <- 0
while k^2<=n
    k = k +1
renvoyer k
```

`While` puissant mais peut ne peut pas finir. LEs boucles while sont utilisées pour programmes usuels:

```
tant que la fenetre est ouverte
    récupérer les saisis de l'utilisateur
    mettre à jour le programme
    afficher à l'écran
```

### Boucles for

<u>Exemple:</u> Algo compte_premiers

```
Entrée: a, b entiers avec a<=b
Sortie: nbr de nombres premiers dand [a, b]

r <- 0
k <- a
tant que k <= b
    si k est premier
        r <- r + 1
    k = k +1
renvoyer r
```

```
r <- 0
pour k allant de a à b
    si k est premier
        r <- r+1
renvoyer r
```

Syntaxe générale:

`pour i=début à fin par incrément``

Attention: fin et incrément ne sont jamais modifié par la boucle.

Une boucle `for` est moins puissante qu'une boucle `while`.

<u>Exercice:</u> remplacer les `while` par des `for` dans l'algo suivant

```
Entrée n entier != 0
Sortie: n-ième nombre premier

c <- 0
p <- 0
tant que c<=n
    si p est premier
        c <- c+1
        si c = n
            renvoyer p
    p <- p+1
```

### Boucles for en C

En C, le mot clé `for` sert a faire des boucles.

Syntaxe:

```
for (init, condition, incrément){
    corps...
}
```

1. Initialisation: C'est une instruction exécuté une fois au début de la boucle.

2. Condition: elle est évalué au début de chaque passage. Si elle est fausse, on sort de la boucle.

3. Incrément: C'est l'instruction qui va être exécuté à chaque passage après le corps.

4. Le corps...

En C, les boucles for sont égales aux boucles while

```
while (condition){
    corps
}


====


for(;condition;{corps}){
    ;
}
```

En pratique:

```
for(int INDICE=DEBUT; INDICE<FIN, INDICE=INDICE+INCREMENT){
    corps
}
```

<u>Exemple:</u>

```c
for( int i =1, i<=n, i++){
    //corps
}
```

## Fonctions récursives

Une fonction récursive est une fonction qui s'appelle elle-même.

<u>Exemple:</u> Soit $n\in\mathbb{N}$

La suite de Syracuse de x est la suite $(u_n)_{n\in\mathbb{N}}$ tel que 

$$
\begin{cases}
u_0 = x\\
u_{n+1} = \begin{cases}
          \dfrac{u_n}{2} \space if\space u_n \space even\\
          3u_n+1 \space if\space u_n \space odd
            \end{cases}
\end{cases}
$$

Faire attention a ne pas recalculer les même valeurs (caching)

```c
int syraccuse(int x, int n){
    if (n==0){
        return x;
    }
    if (syraccuse(x, n-1)%2==0){
    return syraccuse(x, n-1)/2;
    }
    else{
    return 3*syraccuse(x, n-1)+1
    }
}
```

<u>Exemple:</u> factorielle

```c
int factorielle(int n){
    if (n==0)
        return 1;
    else
        return factorielle(n-1);
}
```

## Etude de programmes

### Terminaison

<u>Définition:</u> On dit qu'un algorithme termine si son temps d'exécution est fini pour toutes entrées.

<u>Exemple:</u>

```c
int main(){
    while(1){
    
    }
    return 0;
}
```

C'est algorithme ne se termine pas.

<u>Exemple:</u> Différence

```
Entrée a, b entiers
Sortie: b-a

diff <- 0
tant que b!=a
    b <- b-1
    diff <- diff + 1
renvoyer diff
```

Exécution avec a= 3, b=5:

| ligne | 1   | 3   | 4   | 3   | 4   |
| ----- | --- | --- | --- | --- | --- |
| diff  | 0   | 0   | 1   | 1   | 2   |
| a     | 3   | 3   | 3   | 3   | 3   |
| b     | 5   | 4   | 4   | 3   | 3   |

Or si $b<a$, l'algorithme ne se termine pas

<u>Définition:</u> Un variant de boucle est une quantité obtenue a partir des variable dans l'algorithme qui est:

- Entière

- =>0

- Strictement décroissante à chaque passage de boucle.

<u>Théorème:</u> Si l'on peut éxhiler un variant pour une boucle, cette boucle se termine.

Pour montrer la terminaison d'un algorithme/programme, on cherche des VdB.

### Exponentiation rapide

On considère le problème suivant:

Etant donné $x\in\mathbb{R}, n\in\mathbb{N}$, comment calculer $x^n$

```
Entrée x réel, n entier
Sortie x^n


r <-1
tant que n>0
    r <- r*x
    n <- n-1
renvoyer x
```

Exponentiation rapide:

Pour $x\in\mathbb{N}, x\in\mathbb{R}$, on a:

$$
x^n = \begin{cases}
1 \space si \space n=0\\
(x ^2)^{\dfrac{n}{2}}\space si \space n \space est \space pair\\
(x ^2)^{\dfrac{n-1}{2}}\space si \space n \space est \space impair
\end{cases}
$$

```
Entrée; x rel, n entier
Sortie: x^n


r <- 1
X <- x
Tant que n>0:
    si n%2==1
        r <- r*X
    n = floor(n/2)
    X <- X*X
renvoyer r
```

Exécution avec $x=2$ et $n=11$

| ligne | 2   | 7   | 7   | 7   | 7     | 8             |
| ----- | --- | --- | --- | --- | ----- | ------------- |
| r     | 1   | 2   | 8   | 8   | 2048  |               |
| X     | 2   | 4   | 16  | 256 | 256^2 |               |
| n     | 11  | 5   | 2   | 1   | 0     |               |
| x     | 2   | 2   | 2   | 2   | 2     | renvoyer 2048 |

Terminaison de l'algorithme naïf

Montrons que n est un variant de boucle pour le `while`.

- n est entier car $n\in\mathbb{N}$ au début de l'algorithme et on applique a $n$ que des opérations entières

- $n\geq0$ car au départ $n\in\mathbb{N}$ donc $n\geq0$ et si l'on effectue un passage de boucle, alors au à cet instant $n\geq1$ donc $n\geq0$ à la fin du passage.

- n décroit d'exactement 1 à chaque passage de boucle

Terminaison de l'algorithme rapide

Montrons que n est un variant de boucle pour le `while`.

- n est entier car $n\in\mathbb{N}$ au début de l'algorithme et on applique a $n$ que des opérations qui retourne une valeur entières

- $n\geq0$ au début de l'algorithme et si l'on rentre dans le corps de la boucle, alors n est strictement positif, donc $\lfloor\dfrac{n}{2}\rfloor\geq0$ donc $n\geq0$ à la fin du passage.

- $n$ décroit strictement donc il suffit de montrer que $\lfloor\dfrac{n}{2}\rfloor\leq n$ 

<u>Théorème:</u> Il est impossible d'écrire un programme qui prend en entrée le code source d'un programme P, détermine si P termine.

### Préconditions, assertions

```c
//Renvoie n! pour n>=0
int factorielle(int n){
    assert(n>=0);
}
```

<u>Définition:</u> Une précondition est une hypothèse qui doit être vérifiée pour qu'un fonction/algorithme marche correctement.

Pour implémenter les préconditions, on peut utiliser des *assertions*.

<u>Définition:</u> La spécification d'un algorithme, d'une fonction ou d'un programme est la description de ses sorties en fonction de ses entrées.

<u>Remarque:</u> Préconditions $\subset$ spécifications

<u>Définition:</u> On dit qu'un algorithme est partiellement correct s'il correspond à sa spécification. On dit qu'il est totalement correct si, de plus, il termine.

<u>Exemple:</u> factorielle (encore)

```
Entrée: n entier
Sortie: n!

r <- 1
pour i=1 à n
    r <- r*i
renvoyer r
```

| ligne | 1   | 3   | 3   | 3   | 3   |
| ----- | --- | --- | --- | --- | --- |
| r     | 1   | 1   | 2   | 6   | 24  |
| n     | 6   | 6   | 6   | 6   | 6   |
| i     | x   | 1   | 2   | 3   | 4   |

On remarque qu'à chaque fois qu'on se trouve en bas du corps de boucle, on a: $r=i!$

Montrons le par récurrence sur l'indice de boucle $i$.

- $i=1$: on a $r=1=1!$

- Supposons $r=i!$ à la fin d'un passage de boucle
  
  Le passage suivant correspond a l'indice $i+1$ donc après ce passage: $r$ vaut $i! \times (i+1) = (i+1)!$.
  
  En particulier, après le dernier passage, $i=n$, $r=n!$.

L'algorithme est strictement correct.

<u>Définition:</u> Un invariant de boucle est une propriété P exprimer sur les variables du programme telle que:

- P est vrai à l'initialisation de la boucle (avant le premier passage).

- Si P est vrai au début d'une passage, alors elle est vrai à la fin du passage.

Correction d'un `for` vs `while`

Pour montrer la correction d'une boucle `for`, on l'a transforme en boucle `while`.

<u>Propriété:</u> Si P est un invariant d'une boucle `while`, alors P est vrai en sortit de boucle.

```
Entrée: n entier
Sortie: n!

r <- 1
i <- 1
tant que i <= n
    r <- r*i
    i <- i + 1
renvoyer r
```

Montrons la correction, i.e. que $r=n!$, à la fin de l'algorithme.

P: $r=(i-1)!$ est un IdB.

- En entrée de boucle, $i=1$, $r=1$, donc $r= 1!,=1=0!=(i-1)!$. P est vrai
  
  Supposons P vraie au début d'un passage de boucle $r=(i-1)!$.
  
  On note $r'$, $i'$ les valeur de $r$ et $i$ à la fin du passage.
  
  $r' = ri$, $i' = i+1$
  
  $r'=ri=(i-1)!$
