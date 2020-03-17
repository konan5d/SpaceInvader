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
#define PLAYER_SCORE ('0')
#define PLAYER_LIFE ('3')

#define ENEMY_POSITION_X (19)
#define ENEMY_POSITION_Y (3)
#define ENEMY_SHIP ('H')
#define ENEMY_LIFE (1)

#define ENEMIES (115)//165
#define ENEMIES_PER_LINE (23)
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
	t_character new_pos_y;
	t_character ship;
	uint8_t life;
} t_ship;

typedef struct {
	t_character pos_x;
	t_character pos_y;
	t_character ship;
	uint8_t score;
	uint8_t life;
} t_player;

typedef struct {
	t_character pos_x;
	t_character pos_y;
	t_character old_pos_x;
	t_character old_pos_y;
	const t_character rocket;
}t_rocket;


typedef struct {
	uint8_t d;
	uint8_t c;
	uint8_t m;
} t_score;


enum way {
	LEFT, RIGHT
};
enum booleen {
	FALSE, TRUE
};



void initPlayground(uint8_t tab_playground[80][24], t_ship *tab_enemies);

void displayEnemiesOnPlayground(uint8_t tab_playground[80][24],
		t_ship *tab_enemies);

uint8_t isEnemyHit(t_ship *tab_enemies, t_rocket *rocket, uint8_t *shoot);

uint8_t random(uint8_t value, uint8_t a, uint8_t b, uint8_t m);

uint8_t random_enemy_rocket(void);

void delay(uint32_t time);
#endif /* MAIN_H_ */
