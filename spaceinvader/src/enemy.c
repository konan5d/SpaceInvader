/*
 * enemy.c
 *
 *  Created on: 19 févr. 2020
 *      Author: korantin
 */

#include "enemy.h"

/* FONCTIONS : Déplacement */
/* Permet de bouger 1 vaisseau enemy */
void moveOneEnemyX(t_ship *enemy, uint8_t direction) {
	if (direction == RIGHT) {
		enemy->pos_x++;
	} else if (direction == LEFT) {
		enemy->pos_x--;
	}
}

void moveOneEnemyY(t_ship *enemy) {
	enemy->new_pos_y++;
	;
}

void moveEnemiesX(t_ship *enemy, uint8_t direction) {
	uint8_t i;
	for (i = 0; i <= ENEMIES; i++) {
		moveOneEnemyX(&enemy[i], direction);
	}
}

void displayEnemies(t_ship *enemy, uint8_t *directionX) {
	uint8_t count_enemies = ENEMIES;
	uint8_t i;
	moveEnemiesX(enemy, *directionX);

	if ((enemy[ENEMIES - 1].pos_x == VT100_SCREEN_WIDTH)
			&& (*directionX == RIGHT)) {
		*directionX = LEFT;
		/* Déplacement en Y */
		for (i = 0; i <= count_enemies; i++) {
			moveOneEnemyY(&enemy[i]);
		}

	} else if ((enemy[0].pos_x == 1) && (*directionX == LEFT)) {
		*directionX = RIGHT;
		/* Déplacement en Y */
		for (i = 0; i <= count_enemies; i++) {
			moveOneEnemyY(&enemy[i]);
		}
	}
}

/* FONCTIONS : Rocket */

void moveEnemiesRocket(t_rocket *rocket, uint8_t *shoot) {
	if (*shoot == TRUE)
		{
			rocket->pos_y += 1;

			/* Affichage de la rocket */
			vt100_move(rocket->pos_x, rocket->pos_y);
			serial_putchar(rocket->rocket);

			if (rocket->old_pos_y != 8)
			{
				vt100_move(rocket->old_pos_x, rocket->old_pos_y);
				serial_putchar(' ');
			}

			/* On sauvgarde l'ancienne position de la rocket */
			rocket->old_pos_x = rocket->pos_x;
			rocket->old_pos_y = rocket->pos_y;

			if (rocket->pos_y == 23)
			{
				vt100_move(rocket->old_pos_x, rocket->old_pos_y);
				serial_putchar(' ');
				*shoot = FALSE;

			}
			else
			{
				*shoot = TRUE;
			}
		}
}

uint8_t isEnemyHit(t_ship *tab_enemies, t_rocket *rocket, uint8_t *shoot) {
uint8_t shooted = FALSE;

if (*shoot == TRUE) {
	for (uint8_t count_enemies = 0; count_enemies <= ENEMIES - 1;
			count_enemies++) {
		/* Si l'ennemi est en vie */
		if (tab_enemies[count_enemies].life == 1) {
			/* Si la position de la rocket et de l'ennemi sont égales, alors on tue l'ennemi */
			if ((tab_enemies[count_enemies].pos_x == rocket->pos_x)
					&& (tab_enemies[count_enemies].pos_y == rocket->pos_y)) {
				/* On fait disparaitre l'ennemi */
				tab_enemies[count_enemies].life = 0;
				tab_enemies[count_enemies].ship = ' ';
				/* Ajouter un délai */
				vt100_move(rocket->old_pos_x, rocket->old_pos_y);
				serial_putchar(' ');

				*shoot = FALSE;
				shooted = 1;
				break;
			}
		} else {
			shooted = 0;
		}
	}
}
return shooted;
}

/*
 * Paramètres : dimensions de l'écran, nbre d'ennemis
 */
