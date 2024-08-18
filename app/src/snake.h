/*
 * @file   snake.h
 *
 * SPDX-FileCopyrightText: 2024 Daniel Kopiecki
 * SPDX-License-Identifier: MIT
 */

#ifndef SNAKE_H_INCLUDED_
#define SNAKE_H_INCLUDED_

#include "board.h"
#include "rect.h"

#define BITE 1

struct node {
	struct rect d;
	struct node* next;
};

struct snake {
	struct node* head;
	struct board* b;
};

struct snake* snake_create(struct board* const b, struct vec2 hp, enum color col);
void snake_destroy(struct snake* const s);

int snake_draw(const struct snake* const s);
int snake_move(struct snake* const s, enum dir d);
int snake_gain(struct snake* const s);
bool snake_collides(const struct snake* const s, const struct rect* const with);

#endif /* SNAKE_H_INCLUDED_ */

/**** END OF FILE ****/
