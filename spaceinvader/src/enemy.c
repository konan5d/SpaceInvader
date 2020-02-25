/*
 * enemy.c
 *
 *  Created on: 19 févr. 2020
 *      Author: korantin
 */

#include "enemy.h"

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

	if ((enemy[ENEMIES - 1].pos_x == VT100_SCREEN_WIDTH) && (*directionX == RIGHT)) {
		*directionX = LEFT;
		/* Déplacement en Y */
		for (i = 0; i <= count_enemies; i++) {
			moveOneEnemyY(&enemy[i]);
		}

	} else if ((enemy[0].pos_x == 1) && (*directionX == LEFT)){
		*directionX = RIGHT;
		/* Déplacement en Y */
		for (i = 0; i <= count_enemies; i++) {
			moveOneEnemyY(&enemy[i]);
		}
	}
}

/*
 * Paramètres : dimensions de l'écran, nbre d'ennemis
 */
