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


/*typedef uint32_t t_baudrate;
typedef uint8_t t_character;
typedef uint8_t t_pos;
typedef struct {
	t_character pos_x;
	t_character pos_y;
	t_character new_pos_y;
	t_character ship;
	uint8_t life;
} t_ship;*/

void moveOneEnemyX(t_ship *enemy, uint8_t direction);

void moveOneEnemyY(t_ship *enemy);

void moveEnemiesX(t_ship *enemy, uint8_t direction);

#endif /* ENEMY_H_ */
