/*
 * board.c
 *
 *  Created on: Dec 3, 2023
 *      Author: ADMIN
 */

#include "snake_game/board.h"

void initBoard() {
	board1 = (struct Board*)malloc(sizeof(struct Board));
}

void setScreenSize(struct Board *board, uint16_t height, uint16_t width){
	board->height = height;
	board->width = width;
}
