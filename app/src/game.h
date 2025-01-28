/**
 * @file   game.h
 * @brief  Snake game implementation
 * @author Daniel Kopiecki <daniel.kopiecki@protonmail.com>
 * @date   2025-01-26
 *
 * @copyright Copyright (c) 2025 Daniel Kopiecki
 * @par       License: MIT
 */

#ifndef GAME_H_INCLUDED_
#define GAME_H_INCLUDED_

#include <ncurses.h>

#include "ncge/ncge.h"
#include "ncge/rect.h"
#include "snake.h"

/**
 * @brief Snake game representation
 */
struct game {
	struct ncge base;   /**< Pointer to base class*/
	struct snake snake; /**< Snake representation */
	struct rect food;   /**< Food representation */
	u32 score;          /**< Current score*/
	enum dir dir;       /**< Current snake direction */
};

/**
 * @brief Run game
 *
 * @param g    Instance pointer
 * @return int 0 on success, negative errno otherwise
 */
int game_run(struct game* const g);

/**
 * @brief Destroy game
 *
 * @param g    Instance pointer
 */
void game_destroy(struct game* const g);

#endif /* GAME_H_INCLUDED_ */

/**** END OF FILE ****/
