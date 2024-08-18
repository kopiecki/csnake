/*
 * @file   snake.c
 *
 * SPDX-FileCopyrightText: 2024 Daniel Kopiecki
 * SPDX-License-Identifier: MIT
 */

#include "snake.h"

#include <assert.h>
#include <ncurses.h>
#include <stdlib.h>

#include "common.h"
#include "rect.h"

static inline struct vec2 dir_to_vec(enum dir d)
{
	assert(d <= dir_left);

	switch (d) {
	case dir_up:
		return (struct vec2) {
			.row = -1,
			.col = 0,
		};
	case dir_down:
		return (struct vec2) {
			.row = 1,
			.col = 0,
		};
	case dir_left:
		return (struct vec2) {
			.row = 0,
			.col = -2,
		};
	case dir_right:
		return (struct vec2) {
			.row = 0,
			.col = 2,
		};
	default:
		return (struct vec2) {
			.row = 0,
			.col = 0,
		};
	}
}

static struct node* create_node(struct vec2 d, enum color col)
{
	struct node* n = calloc(1, sizeof(struct node));
	if (n == NULL)
		return n;

	n->d.col = col;
	rect_set(&n->d, d);

	return n;
}

static int add_node(struct snake* const s, struct vec2 d, enum color col)
{
	assert(s != NULL);

	struct node* cur = NULL;
	if (s->head == NULL) {
		s->head = create_node(d, col);
		if (s->head == NULL)
			return ERR;
	} else {
		cur = s->head;
		while (cur->next != NULL)
			cur = cur->next;

		cur->next = create_node(d, col);
	}

	return OK;
}

static int move_tail(struct snake* const s)
{
	struct node* cur = s->head;
	if (cur == NULL)
		return ERR;

	struct rect hp = s->head->d;
	for (; cur != NULL; cur = cur->next) {
		struct rect np = cur->d;
		cur->d         = hp;
		hp             = np;
	}

	return OK;
}

static bool bites(const struct snake* const s)
{
	struct node* cur = s->head;
	if (cur == NULL)
		return ERR;

	cur = cur->next;
	for (; cur != NULL; cur = cur->next)
		if (rect_intersect(&s->head->d, &cur->d))
			return true;

	return false;
}

struct snake* snake_create(struct board* const b, struct vec2 hp, enum color col)
{
	assert(b != NULL);

	struct snake* s = calloc(1, sizeof(struct snake));
	if (s == NULL)
		return s;

	s->b = b;

	int err = add_node(s, hp, col);
	if (err < 0)
		return NULL;

	return s;
}

int snake_draw(const struct snake* const s)
{
	struct node* cur = s->head;
	if (cur == NULL)
		return ERR;

	for (; cur != NULL; cur = cur->next)
		rect_draw(&cur->d, s->b);

	return OK;
}

int snake_move(struct snake* const s, enum dir d)
{
	struct vec2 new_hp = vec2_add_v(s->head->d.left, dir_to_vec(d));

	int err = move_tail(s);
	if (err < 0)
		return err;

	rect_set(&s->head->d, new_hp);
	if (bites(s))
		return BITE;

	return err;
}

int snake_gain(struct snake* const s)
{
	struct vec2 hp = s->head->d.left;
	int err        = add_node(s, hp, color_red);
	if (err < 0)
		return err;

	return OK;
}

bool snake_collides(const struct snake* const s, const struct rect* const with)
{
	return rect_intersect(&s->head->d, with);
}

void snake_destroy(struct snake* const s)
{
	struct node* cur  = s->head;
	struct node* next = cur;

	while (cur != NULL) {
		next = cur->next;
		free(cur);
		cur = next;
	}

	free(s);
}

/**** END OF FILE ****/
