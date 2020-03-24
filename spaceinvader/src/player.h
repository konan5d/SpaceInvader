/*
 * player.h
 *
 *  Created on: 10 mars 2020
 *      Author: korantin
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "main.h"

uint8_t moveShipLR(t_character *tab_ship, uint8_t way, t_pos old_pos);
void movePlayerRocket(t_rocket *rocket, uint8_t *shoot);

#endif /* PLAYER_H_ */
