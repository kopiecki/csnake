/**
 * @file   game.c
 * @brief  Snake game implementation
 * @author Daniel Kopiecki <daniel.kopiecki@protonmail.com>
 * @date   2025-01-26
 *
 * @copyright Copyright (c) 2025 Daniel Kopiecki
 * @par       License: MIT
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
	return mvwprintw(w, 0, wcfgs[WIN_MAIN].dim.col / 2 - 4, "csnake");
}

static inline int put_score(WINDOW* const w, u32 score)
{
	return mvwprintw(
		w,
		wcfgs[WIN_MAIN].dim.row - 1,
		wcfgs[WIN_MAIN].dim.col / 2 - 4,
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

	WINDOW* const w = ncge_get_win(ctx, WIN_INFO);
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

	g->dir   = DIR_RIGHT;
	g->score = 0;

	ctx->state = STATE_PLAY;

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
		if (g->dir != DIR_DOWN)
			g->dir = DIR_UP;
		break;
	case 's':
	case 'j':
	case KEY_DOWN:
		if (g->dir != DIR_UP)
			g->dir = DIR_DOWN;
		break;
	case 'd':
	case 'l':
	case KEY_RIGHT:
		if (g->dir != DIR_LEFT)
			g->dir = DIR_RIGHT;
		break;
	case 'a':
	case 'h':
	case KEY_LEFT:
		if (g->dir != DIR_RIGHT)
			g->dir = DIR_LEFT;
		break;
	case '+':
		ctx->delay_step += DELAY_INC;
		break;
	case '-':
		ctx->delay_step -= DELAY_INC;
		break;
	case 'q':
	case KEY_ESC:
		ctx->state = STATE_EXIT;
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

	g->dir   = DIR_RIGHT;
	g->score = 0;

	snake_destroy(&g->snake);

	ctx->state = STATE_INIT;
}

static int on_lose(struct ncge* const ctx)
{
	assert(ctx != NULL);

	struct game* const g = child_of(ctx);

	WINDOW* const w = ncge_get_win(ctx, WIN_INFO);

	int err = put_end_msg(w, g->score);
	if (err < 0)
		return err;

	switch (getch()) {
	case 'y':
		reinit(ctx);
		break;
	case '\n':
	case 'n':
		ctx->state = STATE_EXIT;
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

	if (ctx->state == STATE_PLAY) {
		const bool moved = snake_move(&g->snake, g->dir);
		if (!moved) {
			ctx->state = STATE_LOSE;
			return 0;
		}

		const int err = handle_collision(ctx);
		if (err < 0)
			return err;
	}

	return 0;
}

static const struct ncge_ops ops = {
	.on_frame = on_frame,
	.state_ops = {
		[STATE_INIT] = on_init,
		[STATE_PLAY] = on_play,
		[STATE_LOSE] = on_lose,
		[STATE_EXIT] = on_leave,
	},
};

int game_run(struct game* const g)
{
	assert(g != NULL);

	int err = ncge_init(&g->base, &ops, 0);
	if (err < 0)
		return err;

	for (int i = 0; i < NUM_WINS; i++) {
		err = ncge_create_win(&g->base, &wcfgs[i]);
		if (err < 0)
			goto ncge_free;
	}

	err = ncge_create_board(&g->base, 0);
	if (err < 0)
		goto ncge_free;

	return ncge_run(&g->base);

ncge_free:
	ncge_destroy(&g->base);

	return err;
}

void game_destroy(struct game* const g)
{
	ncge_destroy(&g->base);
}

/**** END OF FILE ****/
