/*
 * main.h
 *
 *  Created on: 28 janv. 2020
 *      Author: korantin
 */

#ifndef MAIN_H_
#define MAIN_H_

#define PLAYER_POSITION_X (40)
#define PLAYER_POSITION_Y (22)
#define PLAYER_SHIP ('M')
#define PLAYER_LIFE (3)

#define ENEMY_POSITION_X (9)
#define ENEMY_POSITION_Y (3)
#define ENEMY_SHIP ('H')
#define ENEMY_LIFE (1)

#define ENEMIES (165)
#define ENEMIES_PER_LINE (33)
#define ENEMIES_PER_COL (5)

#define BAUDRATE (115200)

#include "vt100.h"
#include "serial.h"
#include "stdint.h"

typedef uint32_t t_baudrate;
typedef uint8_t t_character;
typedef uint8_t t_pos;

typedef struct {
	t_character pos_x;
	t_character pos_y;
	t_character ship;
	uint8_t life;
} t_ship;

enum way {LEFT, RIGHT};

void initEnemy(t_ship *tab_enemies, t_ship enemy, uint8_t enemy_in_line,
		uint8_t nbr_of_line);

void initPlayground(uint8_t tab_playground[80][24],t_ship *tab_enemies);

uint8_t movePlayer(t_character *tab_player, uint8_t way, t_pos old_pos);
#endif /* MAIN_H_ */
