/*
 * @file   game.h
 *
 * SPDX-FileCopyrightText: 2024 Daniel Kopiecki
 * SPDX-License-Identifier: MIT
 */

#ifndef GAME_H_INCLUDED_
#define GAME_H_INCLUDED_

#include <ncurses.h>

#include "ncge/ncge.h"
#include "ncge/rect.h"
#include "snake.h"

struct game {
	struct ncge base;
	struct snake snake;
	struct rect food;
	u32 score;
	enum dir dir;
};

int game_run(struct game* const g);
void game_destroy(struct game* const g);

#endif /* GAME_H_INCLUDED_ */

/**** END OF FILE ****/
