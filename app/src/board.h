/*
 * @file   board.h
 *
 * SPDX-FileCopyrightText: 2024 Daniel Kopiecki
 * SPDX-License-Identifier: MIT
 */

#ifndef BOARD_H_INCLUDED_
#define BOARD_H_INCLUDED_

#include <ncurses.h>

#include "common.h"

struct board {
	WINDOW* w;
	struct cell** grid;
};

/**
 * @brief Create new board
 *
 * @param b     Instance pointer
 * @return int  0 on success, -1 on error
 */
int board_create(struct board* const b);

/**
 * @brief Destroy board
 *
 * @param b     Instance pointer
 */
void board_destroy(struct board* const b);

/**
 * @brief Fill whole board with whitespaces
 *
 * @param b     Instance pointer
 */
void board_clear(struct board* const b);

/**
 * @brief Put board to coresponding window
 *
 * @param b     Instance pointer
 * @return int  0 on success, -1 on error
 */
int board_render(const struct board* const b);

/**
 * @brief Check if board is filled at certain position
 *
 * @param b     Instance pointer
 * @param p     Position to check
 * @return true
 * @return false
 */
static inline bool board_is(const struct board* const b, struct vec2 p)
{
	struct cell cl = b->grid[p.row][p.col];
	return (cl.c != CELL_EMPTY.c) && (cl.ch != CELL_EMPTY.ch);
}

/**
 * @brief Get cell at certain position (RW)
 *
 * @param b                     Instance pointer
 * @param p                     Position of the cell
 * @return struct cell* const   Cell at passed position
 */
static inline struct cell* board_at(struct board* const b, struct vec2 p)
{
	return &b->grid[p.row][p.col];
}

/**
 * @brief Get cell at certain position (R))
 *
 * @param b                     Instance pointer
 * @param p                     Position of the cell
 * @return struct cell const   Cell at passed position
 */
static inline struct cell board_atc(const struct board* const b, struct vec2 p)
{
	return b->grid[p.row][p.col];
}

/**
 * @brief Check if passed position is within bounds of the board
 *
 * @param b     Instance pointer
 * @param p     Position to check
 * @return true
 * @return false
 */
static inline bool board_in(const struct board* const b, struct vec2 p)
{
	const struct vec2 max = win_max(b->w);
	return (p.row > 0) && (p.row < max.row) && (p.col > 0)
	       && (p.col < max.col);
}

#endif /* BOARD_H_INCLUDED_ */

/**** END OF FILE ****/
