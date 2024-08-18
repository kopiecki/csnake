/*
 * @file   rect.h
 *
 * SPDX-FileCopyrightText: 2024 Daniel Kopiecki
 * SPDX-License-Identifier: MIT
 */

#ifndef RECT_H_INCLUDED_
#define RECT_H_INCLUDED_

#include "board.h"
#include "common.h"

struct rect {
	struct vec2 left;
	struct vec2 right;
	enum color col;
};

void rect_set(struct rect* const r, struct vec2 p);
void rect_draw(struct rect* const r, struct board* const b);
void rect_spawn(struct rect* const r, struct board* const b);

static inline bool rect_intersect(
		const struct rect* const lhs, const struct rect* const rhs)
{
	return ((lhs->right.col == rhs->left.col) || (lhs->left.col == rhs->right.col)
			|| (lhs->left.col == rhs->left.col)
			|| (lhs->right.col == rhs->right.col))
		   && ((lhs->right.row == rhs->right.row)
			   || (lhs->left.row == rhs->left.row));
}

#endif /* RECT_H_INCLUDED_ */

/**** END OF FILE ****/
