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
#define rangeValidXLower 0
#define rangeValidXUpper 232
#define rangeValidYLower 64
#define rangeValidYUpper 312
#define snakeWidth 8
#define MAX_LENGTH 500

extern int xFruit;
extern int yFruit;
extern int rangeXGenerate;
extern int rangeYGenerate;
extern int flagEat;

void snakeInit();
void snakeRun();
void generateFruit();
void resumeGame();

#endif /* INC_SNAKE_H_ */
