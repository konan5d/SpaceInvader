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

### a. Gérer le tir des ennemis :

Tout d'abord, il faut générer un nombre, de façon aléatoire, pour générer un missile.

La libraire standard du C inclue une fonction random(), mais sur carte embarquée, nous n'y avons pas accès.

J'ai donc fabriqué une fonction random(), en me basant sur le générateur congruentiel linéaire.

D'après Wikipédia.org, il génère un nombre pseudo-aléatoires dont l'algorithme, crée par Derrick Lehmer, en 1948, produit des nombres aléatoires, basé sur des *congruences* (relation pouvant unir 2 entiers) et une fonction affine.

La fonction qui génère les nombres aléatoires est la suivante :

```c
unsigned char random(uint8_t value, uint8_t a, uint8_t b, uint8_t m) {
	value = (a * value + b) % m;
	return value;
}
```

Notre générateur doit avoir une période maximale pour être le plus aléatoire possible. La période correspond (d'après openclassroom.com) "à la longueur d'une séquence générée".

Elle est donc maximale si :
- *m* doit être le plus grand possible
- *b* doit ếtre très inférieur à *a* et *m*
- *a* doit être proche de la racine carrée de *m*

Dans mon cas, *m* correspond à l'intervale en X dans lequel se trouve mes ennemis.
 
La position du missile étant générée, il faut maintenant l'afficher.

Sur l'axe horizontal (x), vu que les vaisseaux ennemis se déplacent, il suffit de prendre en compte le delta entre le bord du terrain, et le premier vaisseau (si on va de gauche à droite), et de l'ajouter à la position du missile :

```c
enemy_rocket.pos_x = rand_pos_x + enemies[1].pos_x;
```

Sur l'axe vertical (y), il faut prendre en compte la position des vaisseaux ennemis qui sont au front. Le missile ne doit pas être généré par un ennemi qui se trouve derrière un autre vaisseau.

On va donc chercher l'ennemi le premiere ennemi disponible. 

**N.B**: Pendant le développement de cette phase, je me suis rendu compte que je n'avais pas utilisé pour terrain de jeu :

```c
/* Initialisation du terrain de jeu */
	t_character playground[VT100_SCREEN_WIDTH][VT100_SCREEN_HEIGHT]={ 0 }; /* 80 x 24 */
```

J'ai donc utilisé le tableau contenant mes ennemis :
```c
t_ship enemies[ENEMIES] = { 0 };
```

Pour pouvoir accéder à un ennemi N, je prend comme référence le début de chaque ligne :

Ligne | N | N+1 | N + rand_pos_x 
--------|----|--|---
1|1|2| ennemi_N
2|23 = 23 * 1|24 = 23 * **1** + 1 |ennemi_N = 23 * (ligne - 1) + rand_pos_x
3|46 = 23 * 2|47 = 23 * **2** + 1 |ennemi_N = 23 * (ligne - 1) + rand_pos_x
4|69 = 23 * 3|70 = 23 * **3** + 1 |ennemi_N = 23 * (ligne - 1) + rand_pos_x
5|92 = 23 * 4|93 = 23 * **4** + 1 |ennemi_N = 23 * (ligne - 1) + rand_pos_x
L||93 = 23 * **4** + (N+1) |**ennemi_N = 23 * (L - 1) + rand_pos_x**
Avec cette méthode, on accède donc aux données de l'ennemi N. 

```c
for (j = ENEMIES_PER_COL; j > 0; j--)
{

    if (j == 1)
	{
        //Pour ligne = 1
		enemy_N = j + rand_pos_x;
	}
	else
	{
        //Pour ligne > 1
		enemy_N = (j - 1) * ENEMIES_PER_LINE + rand_pos_x;
	}

	if (enemies[enemy_N].life == 1)
	{
        //Si l'ennemi est en vie, je récupère sa positon en y
	    enemy_rocket.pos_y = enemies[enemy_N].pos_y;
		break;
	}
	else
	{  
        //S'il est mort
		enemy_rocket.pos_y = 0;
	}
}

	if (enemy_rocket.pos_y != 0)
	{
        //On autorise le tir, s'il y un ennemi en vie sur la colonne  
    	rocket_enemy = TRUE;
	}

```

Si l'ennemi est en vie, on peut donc tirer le missile, sinon on passe au suivant. 

Mais, si sur un colonne, on a plus d'ennemis en vie, on annule donc le tir.

### b. Gérer le déplacement horizontal des ennemis :

Lors du déplacement horizontal, j'ai pris comme réference mes ennemis qui se situent sur les bords (gauche et droite).

Lors de l'appel de la fonction ***displayEnemies()***, je vérifie la présence des ennemis sur la colonne :
- de droite si on va vers la droite
```c
if (*directionX == RIGHT)
	{
		for (j = ENEMIES_PER_COL; j > 0; j--)
		{
			if (j == 1)
			{
				enemy_N = 22 - N_max;
			}
			else
			{
				enemy_N = (j * ENEMIES_PER_LINE - N_max) - 1;
			}

			if (enemy[enemy_N].life == 0)
			{
				enemy_counter -= 1;
			}
		}

		if (enemy_counter == 0)
		{
			N_max += 1;
			enemy_counter = 5;
		}
	}
```
- de gauche si on va vers la gauche 
```c
if (*directionX == LEFT)
	{
		for (j = ENEMIES_PER_COL; j > 0; j--)
		{
			if (j == 1)
			{
				enemy_N = j + N_min;
			}
			else
			{
				enemy_N = (j - 1) * ENEMIES_PER_LINE + N_min;
			}

			if (enemy[enemy_N].life == 0)
			{
				enemy_counter -= 1;
			}
		}

		if (enemy_counter == 1)
		{
			N_min += 1;
			enemy_counter = 5;
		}
	}
```

N_min et N_max permettent aux vaisseaux encore vivants de pouvoir aller jusqu'au bout du terrain de jeu.


### c. Affichage du score et du nombre de vie :

On ne peut pas afficher directement le score, contenu dans une variable, à l'écran. 

Ex :
```c
serial_putchar('0') != serial_putchar(0x00)

serial_putchar('0') //affiche 0

serial_putchar(0x00) //affiche rien du tout 
```
Pour pouvoir afficher le nombre 0, il faut prendre en considération sa valeur hexadécimale correspondant dans la table ASCII :  0x48. 

Dans la table ASCII, nous remarquons que les chiffres de 0 à 9 se succèdent. Il suffit juste d'incrémenter la valeur hexadécimale pour afficher un chiffre de 0 à 9. 

Un simple algorithme permet par la suite de traiter si c'est le chiffre des unités, des centaines, des milliers... (voir "ui.c" dans le projet)

## 4. Compétences acquises / découvertes / peaufinées :

* Utilisation des pointeurs 
* Utilisation des structures 
* Créer un logiciel complexe

## Conclusion

Dans l'ensemble, j'ai trouvé le projet très interessant.

La difficulté, quand on réalise un logiciel conséquent, est qu'il faut dès le départ, adopter une bonne manière de programmer, pour assurer le développement , par la suite des différents modules.

Aujourd'hui, je pense que mon programme peut être simplifié et optimisé, mais on peut jouer à Space Invaders !

Quand une partie se termine, le jeu se relance automatiquement.