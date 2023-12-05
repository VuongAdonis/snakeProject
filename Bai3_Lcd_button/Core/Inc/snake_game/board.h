/*
 * board.h
 *
 *  Created on: Dec 3, 2023
 *      Author: ADMIN
 */

#ifndef INC_SNAKE_GAME_BOARD_H_
#define INC_SNAKE_GAME_BOARD_H_
#include <main.h>

#define MAX_WIDTH 240
#define MAX_HEIGHT 320

typedef struct Board{
	uint16_t height;
	uint16_t width;
} board;

extern board *board1;

void initBoard();
void setScreenSize(board *board, uint16_t height, uint16_t width);





#endif /* INC_SNAKE_GAME_BOARD_H_ */
