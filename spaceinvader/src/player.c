/*
 * player.c
 *
 *  Created on: 10 mars 2020
 *      Author: korantin
 */


#include "player.h"

uint8_t moveShipLR(t_character *tab_ship, uint8_t way, t_pos old_pos) {

	if (way == LEFT) {
		tab_ship[old_pos - 1] = tab_ship[old_pos];
		tab_ship[old_pos] = ' ';
		old_pos -= 1;
	} else if (way == RIGHT) {
		tab_ship[old_pos + 1] = tab_ship[old_pos];
		tab_ship[old_pos] = ' ';
		old_pos += 1;
	}
	//vt100_clear_line();
	return old_pos;
}

void movePlayerRocket(t_rocket *rocket, uint8_t *shoot) {
	if (*shoot == TRUE)
	{
		rocket->pos_y -= 1;

		/* Affichage de la rocket */
		vt100_move(rocket->pos_x, rocket->pos_y);
		serial_putchar(rocket->rocket);

		if (rocket->old_pos_y != PLAYER_POSITION_Y)
		{
			vt100_move(rocket->old_pos_x, rocket->old_pos_y);
			serial_putchar(' ');
		}

		/* On sauvgarde l'ancienne position de la rocket */
		rocket->old_pos_x = rocket->pos_x;
		rocket->old_pos_y = rocket->pos_y;

		if (rocket->pos_y == 1)
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
