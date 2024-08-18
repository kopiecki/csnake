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

#include "common.h"

#define DELAY_INIT INT16_MAX
#define DELAY_STEP (1 << 9)
#define DELAY_INC  (1 << 6)
#define KEY_ESC    27

static const struct vec2 game_win_dims = { 30, 60 };
static const struct vec2 game_win_pos  = { 0, 0 };
static const struct vec2 snake_hpos    = { 10, 10 };

static const enum color snake_col = color_red;
static const enum color food_col  = color_green;

#endif /* CFG_H_INCLUDED_ */

/**** END OF FILE ****/
