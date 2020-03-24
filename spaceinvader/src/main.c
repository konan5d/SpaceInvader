/*
 ******************************************************************************
 File:     main.c
 Info:     Generated by Atollic TrueSTUDIO(R) 9.3.0   2020-01-28

 The MIT License (MIT)
 Copyright (c) 2019 STMicroelectronics

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

 ******************************************************************************
 */

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"

#include "main.h"
#include "enemy.h"
#include "player.h"
#include "ui.h"
/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */

/**
 **===========================================================================
 **
 **  Abstract: main program
 **
 **===========================================================================
 */

volatile uint8_t flag = 0;

int main(void)
{
	/* INITIALISATION */
	/* Initialisation des variables */
	int i = 0;

	t_character user_input = 0;

	/* Variables : déplacement des vaisseaux ennemies */

	uint8_t dir = RIGHT;

	/* Variables : temps */
	uint32_t time_player = 30000;

	/* TEST */
	uint8_t compteur = 0;
	uint8_t var_shooted = 0;

	/* Variables : texte */

	/* Variables : missiles */
	uint8_t rocket_player = FALSE;
	uint8_t rocket_enemy = FALSE;
	uint8_t rand_pos_x = 2;

	uint8_t j = 0;
	uint8_t enemy_N = 0;

	/* Initialisation de la liaison série*/
	serial_init(BAUDRATE);

	/* Initialisation VT100 */
	vt100_clear_screen();

	/* Déclaration du joueur / des ennemies / du terrain de jeu / missile */

	t_player player =
	{ PLAYER_POSITION_X, PLAYER_POSITION_Y, PLAYER_SHIP,
	PLAYER_SCORE, PLAYER_LIFE };

	t_character playgroundPlayer[VT100_SCREEN_WIDTH] =
	{ 0 };
	playgroundPlayer[player.pos_x] = player.ship;

	t_ship enemy =
	{ ENEMY_POSITION_X, ENEMY_POSITION_Y, 0, ENEMY_SHIP,
	ENEMY_LIFE };

	t_rocket player_rocket =
	{ 0, 0, 0, 0, '|' };

	/* Missile Ennemi */

	t_rocket enemy_rocket =
	{ 0, 0, 0, 0, '|' };

	/* Initialisation du terrain de jeu */
	t_character playground[VT100_SCREEN_WIDTH][VT100_SCREEN_HEIGHT] =
	{ 0 }; /* 80 x 24 */

	/* Initialisation des ennemies */
	t_ship enemies[ENEMIES] =
	{ 0 };
	initEnemy(enemies, enemy, ENEMIES_PER_LINE, ENEMIES_PER_COL);
	initPlayground(playground, enemies);

	t_score toto =
	{ .d = '0', .c = '0', .m = '0' };

	/* Initialisation du joueur */
	playground[player.pos_x][player.pos_y] = player.ship;
	vt100_move(player.pos_x, player.pos_y);
	serial_putchar(playground[player.pos_x][player.pos_y]);

	/* TODO - Add your application code here */

	/* Infinite loop */
	while (1)
	{
		/* Initialisation du jeu */
		displayScore(&player, &toto);

		while ((enemies[ENEMIES - 1].new_pos_y != PLAYER_POSITION_Y - 1)
				|| (player.life == 0))
		{
			/* Affichae du :
			 * - scorez
			 * - nombre de vies du joueur
			 */

			/* Déplacement du joueur */

			for (i = 0; i <= time_player; i++)
			{
				user_input = serial_get_last_char();

				if (((user_input == 'd') || (user_input == 'D'))
						&& (player.pos_x != VT100_SCREEN_WIDTH))
				{

					/* Déplacement joueur */
					player.pos_x = moveShipLR(playgroundPlayer, RIGHT,
							player.pos_x);
					vt100_move(player.pos_x, player.pos_y);
					vt100_clear_line();
					serial_putchar(playgroundPlayer[player.pos_x]);

				}
				else if (((user_input == 'q') || (user_input == 'Q'))
						&& (player.pos_x != 0))
				{

					/* Déplacement joueur */
					player.pos_x = moveShipLR(playgroundPlayer, LEFT,
							player.pos_x);
					vt100_move(player.pos_x, player.pos_y);
					vt100_clear_line();
					serial_putchar(playgroundPlayer[player.pos_x]);

				}
				else if (((user_input == 'z') || (user_input == 'Z'))
						&& (rocket_player == FALSE))
				{
					/* Déplacement des missiles (joueur & ennemies) */
					player_rocket.pos_x = player.pos_x;
					player_rocket.pos_y = player.pos_y;
					rocket_player = TRUE;
				}
			}

			compteur++;

			/* Déplacement des missiles */
			/* Joueur */
			movePlayerRocket(&player_rocket, &rocket_player); // rocket joueur
			var_shooted = isEnemyHit(enemies, &player_rocket, &rocket_player);

			moveEnemiesRocket(&enemy_rocket, &rocket_enemy);

			/* Déplacement des ennemies */
			if (var_shooted == 1)
			{
				/* Si un ennemi est touché, alors on le fait disparaitre et on incrémente le score */
				displayEnemiesOnPlayground(playground, enemies);
				changeScore(&player, &toto);
				displayScore(&player, &toto);
			}
			var_shooted = 0;

			/* Tire d'un missile */
			if ((compteur == 10) && (rocket_enemy == FALSE))
			{
				rand_pos_x = random_enemy_rocket();
				enemy_rocket.pos_x = rand_pos_x + enemies[1].pos_x;

				/* Position en Y du missile */

				for (j = ENEMIES_PER_COL; j > 0; j--)
				{
					if (j == 1)
					{
						enemy_N = j + rand_pos_x;
					}
					else
					{
						enemy_N = (j - 1) * ENEMIES_PER_LINE + rand_pos_x;
					}

					if (enemies[enemy_N].life == 1)
					{
						enemy_rocket.pos_y = enemies[enemy_N].pos_y;
						break;
					}
					else
					{
						enemy_rocket.pos_y = 0;
					}
				}

				if (enemy_rocket.pos_y != 0)
				{
					rocket_enemy = TRUE;
				}

			}

			/* Déplacement des ennemis */
			if (compteur == 20)
			{
				displayEnemies(enemies, &dir);
				displayEnemiesOnPlayground(playground, enemies);
				compteur = 0;
			}
		}
		/* GAME OVER */
	}

}

void initPlayground(uint8_t tab_playground[VT100_SCREEN_WIDTH][VT100_SCREEN_HEIGHT], t_ship *tab_enemies)
{
	uint8_t j = 0;
	for (j = 0; j <= ENEMIES - 1; j++)
	{
		tab_playground[tab_enemies[j].pos_x][tab_enemies[j].pos_y] =
				tab_enemies[j].ship;
		vt100_move(tab_enemies[j].pos_x, tab_enemies[j].pos_y);
		serial_putchar(tab_enemies[j].ship);
	}

}

/* Fonction d'initialisation des vaisseaux ennemies */
void initEnemy(t_ship *tab_enemies, t_ship enemy, uint8_t enemy_in_line,
		uint8_t nbr_of_line)
{
	uint8_t count_line;
	uint8_t count_enemies;
	uint8_t total_enemies;

	total_enemies = 0;

	for (count_line = 0; count_line <= nbr_of_line - 1; count_line++)
	{
		enemy.pos_x = ENEMY_POSITION_X;

		for (count_enemies = 0; count_enemies <= enemy_in_line - 1;
				count_enemies++)
		{
			enemy.new_pos_y = enemy.pos_y;
			tab_enemies[total_enemies] = enemy;
			enemy.pos_x += 2;
			total_enemies += 1;
		}
		enemy.pos_y += 2;

	}
}

void displayEnemiesOnPlayground(uint8_t tab_playground[VT100_SCREEN_WIDTH][VT100_SCREEN_HEIGHT],
		t_ship *tab_enemies)
{
	/* Déplacement en x de l'ennemi n */
	/* Variables */

	/* Quand on arrive au bout de la ligne, déplacement en y de l'ennemi n */
	/* Remplissage du terrain de jeu avec les vaisseaux */
	uint8_t j = 0;
	uint8_t ligne = 0;
	for (j = 0; j <= ENEMIES - 1; j++)
	{
		if (tab_enemies[j].life == 1)
		{
			/* Déplacement du vaisseau */
			tab_playground[tab_enemies[j].pos_x][tab_enemies[j].pos_y] =
					tab_enemies[j].ship;

			/* Effacement de la ligne */
			if ((ligne != tab_enemies[j].pos_y)
					&& ((tab_enemies[j].pos_y) == (tab_enemies[j].new_pos_y)))
			{

				/* On passe au vaisseau suivant */
				vt100_move(tab_enemies[j].pos_x, tab_enemies[j].pos_y);
				vt100_clear_line();

				ligne = tab_enemies[j].pos_y;

			}
			else if ((ligne != tab_enemies[j].pos_y)
					&& ((tab_enemies[j].pos_y) != (tab_enemies[j].new_pos_y)))
			{
				/* On efface la ligne précédente avant de passer à la suivante */
				vt100_move(tab_enemies[j].pos_x, tab_enemies[j].pos_y);
				vt100_clear_line();
				/* On passe à la ligne suivante */
				vt100_move(tab_enemies[j].pos_x, tab_enemies[j].new_pos_y);

				/* On stock la nouvelle position */
				tab_enemies[j].pos_y = tab_enemies[j].new_pos_y;
				ligne = tab_enemies[j].pos_y;
			}

			vt100_move(tab_enemies[j].pos_x, tab_enemies[j].pos_y);
			serial_putchar(tab_enemies[j].ship);
			ligne = tab_enemies[j].pos_y;
		}
	}

}

uint8_t random(uint8_t value, uint8_t a, uint8_t b, uint8_t m)
{
	value = (a * value + b) % m;
	return value;
}

uint8_t random_enemy_rocket(void)
{
	static uint8_t value = 1;
	value = random(value, 7, 1, 45);
	return value;
}

void delay(uint32_t time)
{
	uint32_t i;
	for (i = 0; i <= time; i++)
		;
}

