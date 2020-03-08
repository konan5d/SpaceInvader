# Rapport de projet : Space Invaders

Auteur : *Corentin LEGEAY*

Année : *2019 - 2020*

Formation : *Ynov Robotique & Systèmes Embarqués*

Lien du dépôt Git : https://github.com/konan5d/spaceinvader

Licence : *BSD 3-Clause*

Carte de développement utilisée : *STM32 Nucleo F491ZI*

## 1. Présentation du projet

Dans le cadre de la formation, nous devons programmer le jeu Space Invader, en langage C. 

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

## 4. Compétences acquises / découvertes / peaufinées 

## Conclusion
