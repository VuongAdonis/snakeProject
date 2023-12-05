/*
 * fruit.h
 *
 *  Created on: Dec 3, 2023
 *      Author: ADMIN
 */

#ifndef INC_SNAKE_GAME_FRUIT_H_
#define INC_SNAKE_GAME_FRUIT_H_

#include "main.h"
#include "software_timer.h"
#include "stdio.h"
#include "sys/time.h"

typedef struct {
	uint16_t x; // x-axis start value
	uint16_t y; // y-axis start value
	uint16_t color;
	uint16_t point;
	uint8_t Eaten;
} oFruit;

uint16_t randomCoordinate(uint16_t lower, uint16_t upper, uint16_t count);
void displayFruit(oFruit fruit);
void generateFruit();
oFruit setFruit(uint16_t x, uint16_t y);
int isEaten(oFruit fruit, uint16_t snake_X, uint16_t snakeY);

#endif /* INC_SNAKE_GAME_FRUIT_H_ */
