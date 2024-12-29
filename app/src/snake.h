/*
 * @file   snake.h
 *
 * SPDX-FileCopyrightText: 2024 Daniel Kopiecki
 * SPDX-License-Identifier: MIT
 */

#ifndef SNAKE_H_INCLUDED_
#define SNAKE_H_INCLUDED_

#include "ncge/ll.h"
#include "ncge/rect.h"

struct snake {
	struct ll body;
	struct board* b;
	enum color col;
};

int snake_init(
	struct snake* const s, struct board* const b, struct vec2 hp, enum color col);

void snake_destroy(struct snake* const s);
void snake_draw(const struct snake* const s);

int snake_grow(struct snake* const s);
int snake_reset(struct snake* const s, struct vec2 hp);

bool snake_move(struct snake* const s, enum dir d);
bool snake_collides(const struct snake* const s, const struct rect* const with);

#endif /* SNAKE_H_INCLUDED_ */

/**** END OF FILE ****/
