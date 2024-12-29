/*
 * @file   main.c
 *
 * SPDX-FileCopyrightText: 2024 Daniel Kopiecki
 * SPDX-License-Identifier: MIT
 */

#include "game.h"

static struct game g;

int main(void)
{
	int err = game_run(&g);
	if (err < 0)
		return err;

	return 0;
}

/**** END OF FILE ****/
