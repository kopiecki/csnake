/**
 * @file   snake.c
 * @brief  Snake representation
 * @author Daniel Kopiecki <daniel.kopiecki@protonmail.com>
 * @date   2025-01-26
 *
 * @copyright Copyright (c) 2025 Daniel Kopiecki
 * @par       License: MIT
 */

#include "snake.h"

#include <assert.h>
#include <ncurses.h>
#include <stdlib.h>

#include "ncge/ll.h"
#include "ncge/types.h"

static inline struct vec2 dir_to_vec(enum dir d)
{
	assert(d <= DIR_LEFT);

	switch (d) {
	case DIR_UP:
		return vec2_create(-1, 0);
	case DIR_DOWN:
		return vec2_create(1, 0);
	case DIR_LEFT:
		return vec2_create(0, -2);
	case DIR_RIGHT:
		return vec2_create(0, 2);
	default:
		return vec2_create(0, 0);
	}
}

static void move_body(struct snake* const s)
{
	assert(s != NULL);

	struct rect hp = ll_dcast(s->body.head, struct rect);
	ll_foreach (&s->body) {
		struct rect np           = ll_dcast(n, struct rect);
		ll_dcast(n, struct rect) = hp;
		hp                       = np;
	}
}

static bool bites(const struct snake* const s)
{
	assert(s != NULL);

	const struct node* const h = s->body.head;

	struct node* n = s->body.head->next;
	ll_for (&s->body, n)
		if (rect_eq(h->d, n->d))
			return true;

	return false;
}

static inline bool in_bounds(const struct snake* const s)
{
	assert(s != NULL);

	const struct rect* const h = s->body.head->d;

	return board_in(s->b, h->left) && board_in(s->b, h->right);
}

int snake_init(
	struct snake* const s, struct board* const b, struct vec2 hp, enum color col)
{
	assert(b != NULL);

	s->b   = b;
	s->col = col;

	ll_init(&s->body, sizeof(struct rect), NULL);
	struct rect head = rect_create(hp, s->col);

	return ll_add(&s->body, &head, false);
}

void snake_draw(const struct snake* const s)
{
	assert(s != NULL);

	ll_foreach (&s->body)
		rect_draw(n->d, s->b);
}

bool snake_move(struct snake* const s, enum dir d)
{
	assert(s != NULL);

	struct rect* hp    = s->body.head->d;
	struct vec2 new_hp = vec2_add_v(hp->left, dir_to_vec(d));

	move_body(s);
	rect_fill(hp, new_hp, s->col);

	return (!bites(s) && in_bounds(s));
}

int snake_grow(struct snake* const s)
{
	assert(s != NULL);

	struct rect* hp = s->body.head->d;
	struct rect r   = *hp;

	return ll_add(&s->body, &r, false);
}

bool snake_collides(const struct snake* const s, const struct rect* const with)
{
	assert(s != NULL);
	assert(with != NULL);

	struct rect* h = s->body.head->d;

	return rect_eq(h, with);
}

void snake_destroy(struct snake* const s)
{
	assert(s != NULL);

	ll_destroy(&s->body);
}

/**** END OF FILE ****/
