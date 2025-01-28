/**
 * @file   snake.h
 * @brief  Snake representation
 * @author Daniel Kopiecki <daniel.kopiecki@protonmail.com>
 * @date   2025-01-26
 *
 * @copyright Copyright (c) 2025 Daniel Kopiecki
 * @par       License: MIT
 */

#ifndef SNAKE_H_INCLUDED_
#define SNAKE_H_INCLUDED_

#include "ncge/ll.h"
#include "ncge/rect.h"

/**
 * @brief Snake representation
 */
struct snake {
	struct ll body;  /**< Single linked list holding snake body parts*/
	struct board* b; /**< Board reference at which snake's moving*/
	enum color col;  /**< Snake body color*/
};

/**
 * @brief Initialize snake object
 *
 * @param[in] s    Instance pointer.
 * @param[in] b    Board at which snake will be living.
 * @param[in] hp   Initial snake head position.
 * @param[in] col  Sneak body color.
 * @return int     0 on success, negative errno otherwise.
 */
int snake_init(
	struct snake* const s, struct board* const b, struct vec2 hp, enum color col);

/**
 * @brief Destroy snake object
 *
 * @param[in] s Instance pointer.
 */
void snake_destroy(struct snake* const s);

/**
 * @brief Draw snake on the board
 * @details Snake will be drawn on the board passed into @p snake_init.
 *
 * @param[in] s Instance pointer.
 */
void snake_draw(const struct snake* const s);

/**
 * @brief Increase snakes body.
 *
 * @param[in] s    Instance pointer.
 * @return int     0 on success, negative errno otherwise.
 */
int snake_grow(struct snake* const s);

/**
 * @brief Move snake in specified direction.
 *
 * @param[in] s      Instance pointer.
 * @param[in] d      Direction to move to.
 * @return true      Snake can move.
 * @return false     Snake can't move.
 */
bool snake_move(struct snake* const s, enum dir d);

/**
 * @brief Check if snake collides with board element.
 *
 * @param[in] s      Instance pointer.
 * @param[in] with   Rectangle on the board to check if snakes collides with.
 * @return true      Snake collides.
 * @return false     Snake don't collide.
 */
bool snake_collides(const struct snake* const s, const struct rect* const with);

#endif /* SNAKE_H_INCLUDED_ */

/**** END OF FILE ****/
