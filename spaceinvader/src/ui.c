/*
 * ui.c
 *
 *  Created on: 17 mars 2020
 *      Author: korantin
 */

#include "ui.h"
#include "main.h"

/* ### Score ### */
void displayScore(t_player *player, t_score *score) {

	vt100_move(9, 1);
	serial_putchar(score->m);
	vt100_move(10, 1);
	serial_putchar(score->c);
	vt100_move(11, 1);
	serial_putchar(score->d);
	vt100_move(12, 1);
	serial_putchar('0');
}

void changeScore(t_player *player, t_score *score) {
	score->d += 2;
	if (score->d == ':') {
		score->d = '0';
		score->c += 1;
	}

	if (score->c == ':') {
		score->c = '0';
		score->m += 1;
	}
}
