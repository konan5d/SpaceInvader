# Space Invader 

## Tâches en cours :


## Tâches terminées :
- Déplacement du joueur
- Déplacement des ennemis
- Le joueur peut tirer
- Affichage du score (statique)
- Affichage du nombre de vies (statique)
- Les ennemis peuvent tirer :
    - Génération aléatoire des missiles 
- Affichage du score (dynamique)

## Tâches à faire (vitales):
- Le joueur peut perdre une vie quand il est touché
- Le joueur peut perdre la partie s'il n'a plus de vie

- Affichage du nombre de vies (dynamique)
- Affichage du menu
- Affichage de game win / over
- Creation d'une fonction wait_player()


- **Optional** : Génération d'un ennemi aléatoire 
- **Refact** : Utiliser la fonction timer du µC
- **Refact** : Déplacement des vaisseaux enemis

# Génération d'un nombre aléatoire : Congruential generator:

Xn+1 = (aXn +c)%m

m, 0 < m
a, 0 < a < m
c, 0 <= c < m
X0, 0 <= X0 < m

m = 23

m, 0 < 23
a, 0 < 5 < 23
c, 0 <= 1 < 23
X0, 0 <= 1 < 23
