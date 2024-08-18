/*
 * @file   common.h
 *
 * SPDX-FileCopyrightText: 2024 Daniel Kopiecki
 * SPDX-License-Identifier: MIT
 */

#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <ncurses.h>
#include <stdint.h>
#include <stdlib.h>

#define ARR_SIZE(arr) sizeof(arr) / sizeof(arr[0])

#define BLOCK ' ' | A_REVERSE
#define EMPTY ' '

// clang-format off
#define CELL_EMPTY (struct cell) {EMPTY, color_none}
// clang-format on

typedef uint8_t u8;
typedef int32_t i32;
typedef int64_t i64;
typedef uint32_t u32;

/**
 * @brief Type of colors we are using within the ctetris game
 */
enum color {
	color_none,
	color_cyan,
	color_yellow,
	color_blue,
	color_magenta,
	color_green,
	color_red,
};

/**
 * @brief Generic directions
 */
enum dir {
	dir_down,
	dir_up,
	dir_right,
	dir_left,
};

/**
 * @brief Vector with two elements
 */
struct vec2 {
	i32 row;
	i32 col;
};

/**
 * @brief Cell within the board (character and its color)
 */
struct cell {
	u32 ch;
	enum color c;
};

/**
 * @brief Add two vectors together element-wise
 *
 * @param lhs           Equation left hand side
 * @param rhs           Equation right hand side
 * @return struct vec2  Result (lhs + rhs)
 */
static inline struct vec2 vec2_add_v(const struct vec2 lhs, const struct vec2 rhs)
{
	return (struct vec2) { lhs.row + rhs.row, lhs.col + rhs.col };
}

/**
 * @brief Get random intiger within (lower, upper) range
 *
 * @param lower         Lower range
 * @param upper         Upper range
 * @return int          Random integer
 */
inline static int get_rn(int lower, int upper)
{
	return (rand() % (upper - lower + 1)) + lower;
}

/**
 * @brief Get maximal rows and columns of created window
 *
 * @param w             ncurses window pointer
 * @return struct vec2  Maximal rows and columns
 */
static inline struct vec2 win_max(const WINDOW* const w)
{
	return (struct vec2) {
		.row = getmaxy(w) - 1,
		.col = getmaxx(w) - 1,
	};
}

#endif /* COMMON_H_INCLUDED */

/**** END OF FILE ****/
