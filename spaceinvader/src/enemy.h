/*
 * enemy.h
 *
 *  Created on: 19 févr. 2020
 *      Author: korantin
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "main.h"
#include "stdint.h"

void moveOneEnemyX(t_ship *enemy, uint8_t direction);

void moveOneEnemyY(t_ship *enemy);

void moveEnemiesX(t_ship *enemy, uint8_t direction);

void displayEnemies(t_ship *enemy, uint8_t *directionX) ;

void moveEnemiesRocket(t_rocket *rocket, uint8_t *shoot);

void initEnemy(t_ship *tab_enemies, t_ship enemy, uint8_t enemy_in_line,
		uint8_t nbr_of_line);

#endif /* ENEMY_H_ */
