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

/**
 * struct game - Snake game representation
 * @base:  Pointer to base class. In this case it is `ncge` layer.
 * @snake: Snake representation.
 * @food:  Food representation.
 * @score: Game score.
 * @dir:   Current direction in which snake's moving.
 */
struct game {
	struct ncge base;
	struct snake snake;
	struct rect food;
	u32 score;
	enum dir dir;
};

int game_run(struct game* const g);

#endif /* GAME_H_INCLUDED_ */

/**** END OF FILE ****/
