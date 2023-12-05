/*
 * fruit.c
 *
 *  Created on: Dec 3, 2023
 *      Author: ADMIN
 */

#include "snake_game/fruit.h"
#include "lcd.h"
#include "software_timer.h"

/**
 * @brief set x and y for fruit
 * @param x x-axis value
 * @param y y-axis value
 * @retval None
 * */
oFruit setFruit(uint16_t x, uint16_t y) {
	oFruit fr1;
	fr1.x = x;
	fr1.y = y;
	fr1.color = BLUE;
	fr1.Eaten = 0;
	fr1.point = 1;
	return fr1;
}

/**
 * @brief display fruit
 * @param fruit fruit object to display
 * @retval None
 * */

void displayFruit(oFruit fruit) {
	// Draw a fruit object with area is 5x5 (squared unit)
	lcd_Fill(fruit.x, fruit.y, fruit.x + 5, fruit.y + 5, fruit.color);
}


/**
 * @brieaf Randomly generate x (y) coordinate
 * @param lower lower bound in range of number need to generate
 * @param upper upper bound in range of number need to generate
 * @param count number of generating time
 * @retval num randomn coordinate
 * */
uint16_t randomCoordinate(uint16_t lower, uint16_t upper, uint16_t count) {
	uint16_t num;
	for (uint16_t i = 0; i < count; i++) {
		num = (rand() % (upper - lower + 1)) + lower;
	}
	return num;
}

/**
 * @brieaf Check if fruit is eaten by snake
 * @param fruit current fruit object
 * @param snakeX x-axis value of the head of the snake
 * @param snakeY y-axis value of the head of the snake
 * @retval 1 if fruit is eaten, 0 is not
 * */
int isEaten(oFruit fruit, uint16_t snakeX, uint16_t snakeY) {
	uint16_t x_start = fruit.x;
	uint16_t x_end = x_start + 5;
	uint16_t y_start = fruit.y;
	uint16_t y_end = y_start + 5;

	// Circummeter
	float center_x = (x_start + x_end) / 2;
	float center_y = (y_start + y_end) / 2;

	// Check if this fruit is eaten by snake
	// by check the distance from circummeter to head of the snake
	int diffX = x_end - x_start;
	int diffY = y_end - y_start;
	float distanceToCornerPointSquared = diffX * diffX  + diffY * diffY; // distance = diffX^2 + diffY^2

	float diffCenterX = snakeX - center_x;
	float diffCenterY = snakeY - center_y;
	float distanceToHeadOfSnakeSquared = diffCenterX * diffCenterX + diffCenterY * diffCenterY;

	if (distanceToHeadOfSnakeSquared < distanceToCornerPointSquared) {
		fruit.Eaten = 1;
		return 1;
	}
	return 0;
}

void generateFruit() {
	uint16_t x = randomCoordinate(5, 230, 1);
	uint16_t y = randomCoordinate(65, 310, 1);

	oFruit fruit = setFruit(x, y);
	displayFruit(fruit);
	HAL_Delay(500);

	lcd_Clear(WHITE);

	HAL_Delay(1000);
}
