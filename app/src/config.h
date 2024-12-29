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

static const enum color snake_col = color_red;
static const enum color food_col  = color_green;

enum wins {
	win_main = 0,
	win_info,
	num_wins,
};

static const struct win_cfg wcfgs[] = {
	[win_main] = {
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
	[win_info] = {
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

static const struct vec2 snake_hpos = {
	.row = 10,
	.col = 9,
};

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
