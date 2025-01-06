/*
 * @file   cfg.h
 *
 * SPDX-FileCopyrightText: 2024 Daniel Kopiecki
 * SPDX-License-Identifier: MIT
 */

#ifndef CFG_H_INCLUDED_
#define CFG_H_INCLUDED_

#include <complex.h>
#include <stdbool.h>

#include "ncge/ncge.h"

#define DELAY_INIT INT16_MAX
#define DELAY_STEP (1 << 9)
#define DELAY_INC  (1 << 6)
#define KEY_ESC    27

/**
 * @brief Snake body color
 */
static const enum color snake_col = color_red;

/**
 * @brief Food color
 */
static const enum color food_col = color_green;

/**
 * @brief Type of windows that csnake game consists of
 */
enum win_tp {
	win_tp_main = 0,
	win_tp_info,
	num_wins,
};

/**
 * @brief Windows configuration
 */
static const struct win_cfg wcfgs[] = {
	[win_tp_main] = {
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
	[win_tp_info] = {
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

#endif /* CFG_H_INCLUDED_ */

/**** END OF FILE ****/
