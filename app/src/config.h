/**
 * @file   config.h
 * @brief  Configuration file
 * @author Daniel Kopiecki <daniel.kopiecki@protonmail.com>
 * @date   2025-01-26
 *
 * @copyright Copyright (c) 2025 Daniel Kopiecki
 * @par       License: MIT
 */

#include <stdbool.h>

#include "ncge/ncge.h"

/**
 * @brief Game speed incrementation step
 */
#define DELAY_INC  (1 << 6)

/**
 * @brief Snake body color
 */
static const enum color snake_col = COL_RED;

/**
 * @brief Food color
 */
static const enum color food_col = COL_GREEN;

/**
 * @brief Type of windows that csnake game consists of
 */
enum win_tp {
	WIN_MAIN = 0,
	WIN_INFO,
	NUM_WINS,
};

/**
 * @brief Windows configuration
 */
static const struct win_cfg wcfgs[] = {
	[WIN_MAIN] = {
		.dim = {
			.row = 30,
			.col = 60,
		},
		.pos = {
			.row = 0,
			.col = 0,
		},
		.border = true,
	},
	[WIN_INFO] = {
		.dim = {
			.row = 30,
			.col = 25,
		},
		.pos = {
			.row = 0,
			.col = 61,
		},
		.border = false,
	}
};

/**
 * @brief Initial snake head position
 */
static const struct vec2 snake_hpos = {
	.row = 10,
	.col = 9,
};

/**
 * @brief Game controls information text
 */
static const char* ctrl_txt =
	"controls\n"
	"---------------------\n"
	"a/left/h: move left\n"
	"d/right/l: move right\n"
	"w/up/k: move up\n"
	"s/down/j: move down\n"
	"+/-: change speed\n"
	"q/ESC/ctrl+c: quit\n"
	"---------------------\n";

/**** END OF FILE ****/
