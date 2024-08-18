/*
 * @file   board.c
 *
 * SPDX-FileCopyrightText: 2024 Daniel Kopiecki
 * SPDX-License-Identifier: MIT
 */

#include "board.h"

#include <assert.h>
#include <ncurses.h>

#include "common.h"

static int board_put(const struct board* const b, struct vec2 p)
{
	struct cell cl = board_atc(b, p);

	int err = wattron(b->w, COLOR_PAIR(cl.c));
	if (err < 0)
		return err;

	err = mvwaddch(b->w, p.row, p.col, cl.ch);
	if (err < 0)
		return err;

	err = wattroff(b->w, COLOR_PAIR(cl.c));
	if (err < 0)
		return err;

	return err;
}

void board_clear(struct board* const b)
{
	struct vec2 p         = { 0, 0 };
	const struct vec2 max = win_max(b->w);

	for (; p.row < max.row; p.row++)
		for (p.col = 1; p.col < max.col; p.col++)
			*board_at(b, p) = CELL_EMPTY;
}

int board_create(struct board* const b)
{
	assert(b != NULL);
	assert(b->w != NULL);

	const struct vec2 max = win_max(b->w);

	b->grid = calloc((u32)max.row, sizeof(struct cell*));
	if (b->grid == NULL)
		return ERR;

	for (i32 row = 0; row < max.row; row++) {
		b->grid[row] = calloc((u32)max.col, sizeof(struct cell));
		if (b->grid[row] == NULL)
			return ERR;
	}

	board_clear(b);

	return OK;
}

void board_destroy(struct board* const b)
{
	assert(b != NULL);
	assert(b->grid != NULL);

	free(b->grid);
}

int board_render(const struct board* const b)
{
	assert(b != NULL);
	assert(b->grid != NULL);
	assert(b->w != NULL);

	int err = OK;

	struct vec2 p         = { 1, 1 };
	const struct vec2 max = win_max(b->w);

	for (; p.row < max.row; p.row++) {
		for (p.col = 1; p.col < max.col; p.col++) {
			err = board_put(b, p);
			if (err < 0)
				return err;
		}
	}

	return err;
}

/**** END OF FILE ****/
