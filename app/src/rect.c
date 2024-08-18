/*
 * @file   rect.c
 *
 * SPDX-FileCopyrightText: 2024 Daniel Kopiecki
 * SPDX-License-Identifier: MIT
 */

#include "rect.h"

#include <assert.h>

void rect_set(struct rect* const r, struct vec2 p)
{
	assert(r != NULL);

	r->left  = p;
	r->right = p;
	r->right.col++;
}

void rect_draw(struct rect* const r, struct board* const b)
{
	*board_at(b, r->left) = (struct cell) {
		.ch = BLOCK,
		.c  = r->col,
	};

	*board_at(b, r->right) = (struct cell) {
		.ch = BLOCK,
		.c  = r->col,
	};
}

void rect_spawn(struct rect* const r, struct board* const b)
{
	const struct vec2 min = { 4, 4 };
	const struct vec2 max = win_max(b->w);

	struct vec2 pos = {
		.row = get_rn(min.row, max.row) - 1,
		.col = get_rn(min.col, max.col) - 1,
	};

	if (pos.col & 1)
		pos.col++;

	rect_set(r, pos);
}

/**** END OF FILE ****/
