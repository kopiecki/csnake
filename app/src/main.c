/**
 * @file   main.c
 * @brief  Application entry point
 * @author Daniel Kopiecki <daniel.kopiecki@protonmail.com>
 * @date   2025-01-26
 *
 * @copyright Copyright (c) 2025 Daniel Kopiecki
 * @par       License: MIT
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
