/*
 * @file   game.c
 *
 * SPDX-FileCopyrightText: 2024 Daniel Kopiecki
 * SPDX-License-Identifier: MIT
 */

#include "game.h"

#include <errno.h>
#include <ncurses.h>
#include <stdlib.h>

#include "config.h"
#include "ncge/ncge.h"
#include "ncge/types.h"
#include "snake.h"

#define child_of(base) (struct game*)(base)

static inline int get_rn(int lower, int upper)
{
	return (rand() % (upper - lower + 1)) + lower;
}

static inline int put_title(WINDOW* const w)
{
	return mvwprintw(w, 0, wcfgs[win_tp_main].dim.col / 2 - 4, "csnake");
}

static inline int put_score(WINDOW* const w, u32 score)
{
	return mvwprintw(
		w,
		wcfgs[win_tp_main].dim.row - 1,
		wcfgs[win_tp_main].dim.col / 2 - 4,
		"score: %d",
		score);
}

static inline int put_info(WINDOW* const w)
{
	return mvwprintw(w, 0, 0, "%s", ctrl_txt);
}

static inline int put_end_msg(WINDOW* const w, u32 score)
{
	return mvwprintw(
		w,
		9,
		0,
		"Final score: %d\n"
		"Try again? [y/N]\n",
		score);
}

static void spawn_food(struct board* const b, struct rect* const food)
{
	assert(b != NULL);
	assert(food != NULL);

	const struct vec2 min = { 1, 1 };
	const struct vec2 max = vec2_add_v(board_max(b), vec2_create(-1, -2));

	struct vec2 pos =
		vec2_create(get_rn(min.row, max.row), get_rn(min.col, max.col));

	if (!(pos.col & 1))
		pos.col += (pos.col + 1 >= max.col) ? -1 : 1;

	rect_fill(food, pos, food_col);
}

static int handle_collision(struct ncge* const ctx)
{
	assert(ctx != NULL);

	struct game* const g = child_of(ctx);

	struct board* const b = ncge_get_board(ctx, 0);
	if (snake_collides(&g->snake, &g->food)) {
		int err = snake_grow(&g->snake);
		if (err < 0)
			return err;

		err = put_score(b->w, ++g->score);
		if (err < 0)
			return err;

		spawn_food(b, &g->food);
	}

	return 0;
}

static int on_init(struct ncge* const ctx)
{
	assert(ctx != NULL);

	struct game* const g  = child_of(ctx);
	struct board* const b = ncge_get_board(ctx, 0);

	int err = snake_init(&g->snake, b, snake_hpos, snake_col);
	if (err < 0)
		return err;

	WINDOW* const w = ncge_get_win(ctx, win_tp_info);
	if (w == NULL)
		return -ENODATA;

	err = put_score(b->w, g->score);
	if (err < 0)
		return err;

	err = put_title(b->w);
	if (err < 0)
		return err;

	err = put_info(w);
	if (err < 0)
		return err;

	spawn_food(b, &g->food);

	g->dir   = dir_right;
	g->score = 0;

	ctx->state = state_play;

	return 0;
}

static int on_play(struct ncge* const ctx)
{
	assert(ctx != NULL);

	struct game* const g  = child_of(ctx);
	struct board* const b = ncge_get_board(ctx, 0);

	board_clear(b);

	snake_draw(&g->snake);
	rect_draw(&g->food, b);

	switch (getch()) {
	case 'w':
	case 'k':
	case KEY_UP:
		if (g->dir != dir_down)
			g->dir = dir_up;
		break;
	case 's':
	case 'j':
	case KEY_DOWN:
		if (g->dir != dir_up)
			g->dir = dir_down;
		break;
	case 'd':
	case 'l':
	case KEY_RIGHT:
		if (g->dir != dir_left)
			g->dir = dir_right;
		break;
	case 'a':
	case 'h':
	case KEY_LEFT:
		if (g->dir != dir_right)
			g->dir = dir_left;
		break;
	case '+':
		ctx->delay_step += DELAY_INC;
		break;
	case '-':
		ctx->delay_step -= DELAY_INC;
		break;
	case 'q':
	case KEY_ESC:
		ctx->state = state_exit;
		break;
	default:
		break;
	}

	return 0;
}

static void reinit(struct ncge* const ctx)
{
	assert(ctx != NULL);

	struct game* const g = child_of(ctx);

	g->dir   = dir_right;
	g->score = 0;

	snake_destroy(&g->snake);

	ctx->state = state_init;
}

static int on_lose(struct ncge* const ctx)
{
	assert(ctx != NULL);

	struct game* const g = child_of(ctx);

	WINDOW* const w = ncge_get_win(ctx, win_tp_info);

	int err = put_end_msg(w, g->score);
	if (err < 0)
		return err;

	switch (getch()) {
	case 'y':
		reinit(ctx);
		break;
	case '\n':
	case 'n':
		ctx->state = state_exit;
		break;
	default:
		break;
	}

	return 0;
}

static int on_leave(struct ncge* const ctx)
{
	struct game* const g = child_of(ctx);

	snake_destroy(&g->snake);

	return NCGE_EXIT;
}

static int on_frame(struct ncge* const ctx)
{
	struct game* const g = child_of(ctx);

	if (ctx->state == state_play) {
		const bool moved = snake_move(&g->snake, g->dir);
		if (!moved) {
			ctx->state = state_lose;
			return 0;
		}

		const int err = handle_collision(ctx);
		if (err < 0)
			return err;
	}

	return 0;
}

static struct ncge_ops ops = {
		.on_frame = on_frame,
		.state_ops = {
				[state_init] = on_init,
				[state_play] = on_play,
				[state_lose] = on_lose,
				[state_exit] = on_leave,
		},
	};

int game_run(struct game* const g)
{
	assert(g != NULL);

	int err = ncge_init(&g->base, &ops, 0);
	if (err < 0)
		return err;

	for (int i = 0; i < num_wins; i++) {
		err = ncge_create_win(&g->base, &wcfgs[i]);
		if (err < 0)
			return err;
	}

	err = ncge_create_board(&g->base, 0);
	if (err < 0)
		return err;

	return ncge_run(&g->base);
}

/**** END OF FILE ****/
