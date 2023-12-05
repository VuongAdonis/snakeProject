/*
 * snake.h
 *
 *  Created on: Dec 3, 2023
 *      Author: TVB09
 */

#ifndef INC_SNAKE_H_
#define INC_SNAKE_H_


#define RIGHT 0
#define LEFT 1
#define DOWN 2
#define UP 3

struct info
{
	int x;
	int y;
};

extern int lengthOfArray;
extern struct info snake[3000];
extern int direction;
extern int snakeLength;

void displaySnake();
void initGame();
void goLeft();
void goRight();
void goUp();
void goDown();
void move();
void runSnake();

#endif /* INC_SNAKE_H_ */
