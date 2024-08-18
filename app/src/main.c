/*
 * @file   main.c
 *
 * SPDX-FileCopyrightText: 2024 Daniel Kopiecki
 * SPDX-License-Identifier: MIT
 */

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "board.h"
#include "common.h"
#include "config.h"
#include "rect.h"
#include "snake.h"

static struct board board;
static struct rect food = { .col = food_col };

static WINDOW* win         = NULL;
static struct snake* snake = NULL;

static const u8 colors[] = {
	COLOR_CYAN,  COLOR_YELLOW, COLOR_BLUE,  COLOR_MAGENTA,
	COLOR_GREEN, COLOR_RED,    COLOR_WHITE, COLOR_BLACK,
};

static WINDOW* create_win(struct vec2 dim, struct vec2 pos, bool border)
{
	WINDOW* w = newwin(dim.row, dim.col, pos.row, pos.col);
	if (w == NULL)
		return NULL;

	int err = OK;
	if (border) {
		err = box(w, 0, 0);
		if (err < 0)
			return NULL;
	}

	err = wrefresh(w);
	if (err < 0)
		return NULL;

	return w;
}

static int init_col(void)
{
	int err = ERR;
	if (has_colors() == FALSE)
		return err;

	err = use_default_colors();
	if (err < 0)
		return err;

	err = start_color();
	if (err < 0)
		return err;

	for (u8 i = 0; i < ARR_SIZE(colors); i++) {
		err = init_pair(i + 1, colors[i], -1);
		if (err < 0)
			return err;
	}

	return err;
}

static int init_env(void)
{
	int err = ERR;
	if (initscr() == NULL)
		return err;

	err = cbreak();
	if (err < 0)
		return err;

	err = keypad(stdscr, 1);
	if (err < 0)
		return err;

	err = noecho();
	if (err < 0)
		return err;

	err = curs_set(0);
	if (err < 0)
		return err;

	timeout(1);
	srand((u32)time(NULL));

	err = atexit((void (*)(void))endwin);
	if (err < 0)
		return err;

	err = init_col();
	if (err < 0)
		return err;

	err = wrefresh(stdscr);
	if (err < 0)
		return err;

	return err;
}

static int create_board(void)
{
	int err = ERR;

	win = create_win(game_win_dims, game_win_pos, true);
	if (win == NULL)
		return err;

	board = (struct board) { .grid = NULL, .w = win };
	err   = board_create(&board);
	if (err < 0)
		return err;

	return err;
}

static void cleanup(void)
{
	snake_destroy(snake);
	board_destroy(&board);
	delwin(win);
}

static int update(void)
{
	int err = board_render(&board);
	if (err < 0)
		return err;

	err = wrefresh(win);
	if (err < 0)
		return err;

	return err;
}

int run_snake(void)
{
	int err = ERR;

	snake = snake_create(&board, snake_hpos, snake_col);
	if (snake == NULL)
		return ERR;

	rect_spawn(&food, &board);

	i32 delay     = DELAY_INIT;
	i32 step      = DELAY_STEP;
	enum dir dir  = dir_right;
	u32 score_cnt = 0;

	while (true) {
		board_clear(&board);

		snake_draw(snake);
		rect_draw(&food, &board);

		if (snake_collides(snake, &food)) {
			rect_spawn(&food, &board);
			err = snake_gain(snake);
			if (err < 0)
				goto exit;

			score_cnt++;
		}

		delay -= step;
		if (delay < 0) {
			err = snake_move(snake, dir);
			if (err < 0)
				return ERR;
			else if (err == BITE)
				goto exit;

			delay = INT16_MAX;
		}

		switch (getch()) {
		case 'w':
		case 'k':
		case KEY_UP:
			dir = dir_up;
			break;
		case 's':
		case 'j':
		case KEY_DOWN:
			dir = dir_down;
			break;
		case 'd':
		case 'l':
		case KEY_RIGHT:
			dir = dir_right;
			break;
		case 'a':
		case 'h':
		case KEY_LEFT:
			dir = dir_left;
			break;
		case '+':
			step += DELAY_INC;
			break;
		case '-':
			step -= DELAY_INC;
			break;
		case 'q':
		case KEY_ESC:
			goto exit;
		default:
			break;
		}

		err = update();
		if (err < 0)
			goto exit;
	}

exit:
	cleanup();

	return err;
}

int main(void)
{
	int err = init_env();
	if (err < 0)
		return err;

	err = create_board();
	if (err < 0)
		return err;

	err = run_snake();
	if (err < 0)
		return err;

	return err;
}

/**** END OF FILE ****/
