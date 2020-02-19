/*
 * enemy.c
 *
 *  Created on: 19 févr. 2020
 *      Author: korantin
 */

#include "enemy.h"


/* Permet de bouger 1 vaisseau enemy */
void moveOneEnemyX(t_ship *enemy, uint8_t direction){
	if(direction == RIGHT){
		enemy->pos_x++;
	}else if (direction == LEFT){
		enemy->pos_x--;
	}
}

void moveOneEnemyY(t_ship *enemy){
	enemy->pos_y++;;
}

void moveEnemiesX(t_ship *enemy, uint8_t direction){
	uint8_t i;
	for (i = 0; i <= ENEMIES; i++){
		moveOneEnemyX(&enemy[i], direction);
	}
}

