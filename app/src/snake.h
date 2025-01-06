/*
 * @file   snake.h
 *
 * SPDX-FileCopyrightText: 2024 Daniel Kopiecki
 * SPDX-License-Identifier: MIT
 */

#ifndef SNAKE_H_INCLUDED_
#define SNAKE_H_INCLUDED_

#include "ncge/ll.h"
#include "ncge/rect.h"

/**
 * struct snake - snake representation
 * @body: Single linked list holding snake body parts.
 * @b:    Board reference at which snake's moving.
 * @col:  Snake body color.
 */
struct snake {
	struct ll body;
	struct board* b;
	enum color col;
};

/**
 * @brief Initialize snake object
 *
 * @param s    Instance pointer.
 * @param b    Board at which snake will be living.
 * @param hp   Initial snake head position.
 * @param col  Sneak body color.
 * @return int 0 on success, negative errno otherwise.
 */
int snake_init(
	struct snake* const s, struct board* const b, struct vec2 hp, enum color col);

/**
 * @brief Destroy snake object
 *
 * @param s Instance pointer.
 */
void snake_destroy(struct snake* const s);

/**
 * @brief Draw snake on the board
 *
 * @param s Instance pointer.
 *
 * Snake will be drawn on the board passed into @ref snake_init.
 */
void snake_draw(const struct snake* const s);

/**
 * @brief Increase snakes body.
 *
 * @param s    Instance pointer.
 * @return int 0 on success, negative errno otherwise.
 */
int snake_grow(struct snake* const s);


/**
 * @brief Move snake in specified direction.
 *
 * @param s      Instance pointer.
 * @param d      Direction to move to.
 * @return true  Snake can move.
 * @return false Snake can't move.
 */
bool snake_move(struct snake* const s, enum dir d);

/**
 * @brief Check if snake collides with board element.
 *
 * @param s      Instance pointer.
 * @param with   Rectangle on the board to check if snakes collides with.
 * @return true  Snake collides.
 * @return false Snake don't collide.
 */
bool snake_collides(const struct snake* const s, const struct rect* const with);

#endif /* SNAKE_H_INCLUDED_ */

/**** END OF FILE ****/
