# Rapport de projet : Space Invaders

Auteur : *Corentin LEGEAY*

Année : *2019 - 2020*

Formation : *Ynov Robotique & Systèmes Embarqués*

Lien du dépôt Git : https://github.com/konan5d/spaceinvader

Licence : *BSD 3-Clause*

Carte de développement utilisée : *STM32 Nucleo F491ZI*

## 1. Présentation du projet

Dans le cadre de la formation, nous devons programmer le jeu Space Invaders, en langage C. 

Nous utilisons une carte de développement embarquée, afin de réaliser le traitement et le calcul des données.

Par la suite, elle renvoie à un ordinateur, via une liaison série, les caractères à afficher, sur une interface VT100.

L'utilisateur peut donc jouer à Space Invaders, en utilisant les touches de son clavier !

## 2. Space Invaders, le jeu !

### a. Un peu d'histoire... 

*(D'après Wikipédia.org)*

Space Invaders est un jeu vidéo crée en 1978, par la société japonaise *Taito*. Dévéloppé pour les bornes d'arcades, il fait partie des grands classiques de l'époque (comme Pac-Man).

### b. Les règles du jeu 

Une horde d'aliens a envahi notre monde.. il faut, à l'aide de notre vaisseau équipé d'un canon laser, les détruires, tout en se protègeant derrière 4 bâtiments destructibles. 

Le joueur peut se déplacer horizontalement, et tirer un missile pour tenter de détruire un vaisseau ennemi.

Les vaisseaux ennemis, se déplacent horizontalement et verticalement, jusqu'à atteindre le bas de l'écran. 

Si le joueur ne parvient pas, à atteindre son objectif, la partie est perdue. 
A contrario, s'il arrive à tous les éliminer, il gagne la partie.

Cependant, il ne dispose que de 3 vies pour atteindre son objectif !

Dès qu'une horde d'aliens est vaincue, une nouvelle apparaît de nouveau.. le jeu est donc sans fin (sauf quand le joueur perd, bien évidemment).

### c. Contrôle :

Le joueur dispose de 3 touches pour jouer :
* **Q** et **D** pour se déplacer horizontalement 
* **Z** pour tirer 

## 3. Les 3 plus grandes difficultées rencontrées dans le projet

### a. Gérer le déplacement horizontal des ennemis :

* Adapter l'intervale de déplacement en fonction des ennemis aux extrémitées : non résolu

### b. Gérer le tir des ennemis :

Tout d'abord, il faut générer un nombre, de façon aléatoire, pour générer un missile.

La libraire standard du C inclue une fonction random(), mais sur carte embarquée, nous n'y avons pas accès.

J'ai donc fabriqué une fonction random(), en me basant sur le générateur congruentiel linéaire.

D'après Wikipédia.org, il génère un nombre pseudo-aléatoires dont l'algorithme, crée par Derrick Lehmer, en 1948, produit des nombres aléatoires, basé sur des *congruences* (relation pouvant unir 2 entiers) et une fonction affine.

...

* position en y du tir : non résolu

### c. Affichage du score et du nombre de vie :

On ne peut pas afficher directement le score, contenu dans une variable, à l'écran. 

Ex :
```x
serial_putchar('0') != serial_putchar(0x00)

serial_putchar('0') //affiche 0

serial_putchar(0x00) //affiche rien du tout 
```
Pour pouvoir afficher le nombre 0, il faut prendre en considération sa valeur hexadécimale correspondant dans la table ASCII :  0x48. 

Dans la table ASCII, nous remarquons que les chiffres de 0 à 9 se succèdent. Il suffit juste d'incrémenter la valeur hexadécimale pour afficher un chiffre de 0 à 9. 

Un simple algorithme permet par la suite de traiter si c'est le chiffre des unités, des centaines, des milliers... (voir "ui.c" dans le projet)

## 4. Compétences acquises / découvertes / peaufinées 

## Conclusion
