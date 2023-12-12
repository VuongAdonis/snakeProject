/*
 * snake.c
 *
 *  Created on: Dec 3, 2023
 *      Author: TVB09
 */

#include "snake.h"
#include "lcd.h"
#include "button.h"
#include "limits.h"
#include "time.h"
#include "stdlib.h"
#include "global.h"
#include "uart.h"

#define RIGHT 0
#define LEFT 1
#define DOWN 2
#define UP 3
#define rangeValidXLower 0
#define rangeValidXUpper 230
#define rangeValidYLower 70
#define rangeValidYUpper 310
#define snakeWidth 9
#define snakeStep 10
#define MAX_LENGTH 500
#define rangeXGenerate (rangeValidXUpper - rangeValidXLower) / snakeStep
#define rangeYGenerate (rangeValidYUpper - rangeValidYLower) / snakeStep

int rst = 0;

int xFruit = INT_MIN;
int yFruit = INT_MIN;
int flagEat = 1;

typedef struct
{
	int x;
	int y;
} infoXYSnake;

typedef struct
{
	int x;
	int y;
	int vertical;
} infoXYWall;

typedef struct
{
	void (*GOLEFT)(void);
	void (*GORIGHT)(void);
	void (*GOUP)(void);
	void (*GODOWN)(void);
	void (*MOVE)(void);
	void (*CHECKHEAD)();
	int snakeDirectionHead;
	infoXYSnake infoTempSnakeTail;
	int snakeLength;
	int stopSnakeFlag;
	infoXYSnake infoSnake[MAX_LENGTH];
} SNAKE;

SNAKE snakeObject;

typedef struct
{
	infoXYWall infoWall[MAX_LENGTH];
	int amountWallElement;
	int vertical;
	int stopGenerateWallFlag;
} WALLs;

WALLs wallObject;

void drawHeadSnake()
{
	switch (snakeObject.snakeDirectionHead)
	{
	case UP:
		lcd_Fill(snakeObject.infoSnake[0].x, snakeObject.infoSnake[0].y,
				 snakeObject.infoSnake[0].x + snakeWidth, snakeObject.infoSnake[0].y + snakeWidth, RED);
		lcd_Fill(snakeObject.infoSnake[0].x, snakeObject.infoSnake[0].y,
				 snakeObject.infoSnake[0].x + 4, snakeObject.infoSnake[0].y + 4, BLACK);
		lcd_Fill(snakeObject.infoSnake[0].x + 5, snakeObject.infoSnake[0].y,
				 snakeObject.infoSnake[0].x + 9, snakeObject.infoSnake[0].y + 4, BLACK);
		break;
	case DOWN:
		lcd_Fill(snakeObject.infoSnake[0].x, snakeObject.infoSnake[0].y,
				 snakeObject.infoSnake[0].x + snakeWidth, snakeObject.infoSnake[0].y + snakeWidth, RED);
		lcd_Fill(snakeObject.infoSnake[0].x, snakeObject.infoSnake[0].y + 5,
				 snakeObject.infoSnake[0].x + 4, snakeObject.infoSnake[0].y + 9, BLACK);
		lcd_Fill(snakeObject.infoSnake[0].x + 5, snakeObject.infoSnake[0].y + 5,
				 snakeObject.infoSnake[0].x + 9, snakeObject.infoSnake[0].y + 9, BLACK);
		break;
	case LEFT:
		lcd_Fill(snakeObject.infoSnake[0].x, snakeObject.infoSnake[0].y,
				 snakeObject.infoSnake[0].x + snakeWidth, snakeObject.infoSnake[0].y + snakeWidth, RED);
		lcd_Fill(snakeObject.infoSnake[0].x, snakeObject.infoSnake[0].y,
				 snakeObject.infoSnake[0].x + 4, snakeObject.infoSnake[0].y + 4, BLACK);
		lcd_Fill(snakeObject.infoSnake[0].x, snakeObject.infoSnake[0].y + 5,
				 snakeObject.infoSnake[0].x + 4, snakeObject.infoSnake[0].y + 9, BLACK);
		break;
	case RIGHT:
		lcd_Fill(snakeObject.infoSnake[0].x, snakeObject.infoSnake[0].y,
				 snakeObject.infoSnake[0].x + snakeWidth, snakeObject.infoSnake[0].y + snakeWidth, RED);
		lcd_Fill(snakeObject.infoSnake[0].x + 5, snakeObject.infoSnake[0].y,
				 snakeObject.infoSnake[0].x + 9, snakeObject.infoSnake[0].y + 4, BLACK);
		lcd_Fill(snakeObject.infoSnake[0].x + 5, snakeObject.infoSnake[0].y + 5,
				 snakeObject.infoSnake[0].x + 9, snakeObject.infoSnake[0].y + 9, BLACK);
		break;
	default:
		break;
	}
}

void goLeft()
{
	if (snakeObject.stopSnakeFlag == 0)
	{
		switch (snakeObject.snakeDirectionHead)
		{
		case RIGHT:
			(*snakeObject.GORIGHT)();
			break;
		default:
			snakeObject.snakeDirectionHead = LEFT;
			infoXYSnake tempSnake1;
			infoXYSnake tempSnake2;
			for (int i = 0; i < snakeObject.snakeLength; i++)
			{
				if (i == 0)
				{
					tempSnake1 = snakeObject.infoSnake[i];
					snakeObject.infoSnake[i].x -= snakeStep;
					snakeObject.infoSnake[i].y = snakeObject.infoSnake[i].y;
					drawHeadSnake();
				}
				else
				{
					tempSnake2 = snakeObject.infoSnake[i];
					snakeObject.infoSnake[i] = tempSnake1;
					tempSnake1 = tempSnake2;
					if (i == 1)
						lcd_Fill(snakeObject.infoSnake[i].x, snakeObject.infoSnake[i].y,
								 snakeObject.infoSnake[i].x + snakeWidth, snakeObject.infoSnake[i].y + snakeWidth, BLACK);
					if (i == snakeObject.snakeLength - 1)
					{
						snakeObject.infoTempSnakeTail = tempSnake2;
						lcd_Fill(tempSnake2.x, tempSnake2.y, tempSnake2.x + snakeWidth, tempSnake2.y + snakeWidth, WHITE);
					}
				}
			}
			break;
		}
	}
}

void goRight()
{
	if (snakeObject.stopSnakeFlag == 0)
	{
		switch (snakeObject.snakeDirectionHead)
		{
		case LEFT:
			(*snakeObject.GOLEFT)();
			break;
		default:
			snakeObject.snakeDirectionHead = RIGHT;
			infoXYSnake tempSnake1;
			infoXYSnake tempSnake2;
			for (int i = 0; i < snakeObject.snakeLength; i++)
			{
				if (i == 0)
				{
					tempSnake1 = snakeObject.infoSnake[i];
					snakeObject.infoSnake[i].x += snakeStep;
					snakeObject.infoSnake[i].y = snakeObject.infoSnake[i].y;
					drawHeadSnake();
				}
				else
				{
					tempSnake2 = snakeObject.infoSnake[i];
					snakeObject.infoSnake[i] = tempSnake1;
					tempSnake1 = tempSnake2;
					if (i == 1)
						lcd_Fill(snakeObject.infoSnake[i].x, snakeObject.infoSnake[i].y,
								 snakeObject.infoSnake[i].x + snakeWidth, snakeObject.infoSnake[i].y + snakeWidth, BLACK);
					if (i == snakeObject.snakeLength - 1)
					{
						snakeObject.infoTempSnakeTail = tempSnake2;
						lcd_Fill(tempSnake2.x, tempSnake2.y, tempSnake2.x + snakeWidth, tempSnake2.y + snakeWidth, WHITE);
					}
				}
			}
			break;
		}
	}
}

void goUp()
{
	if (snakeObject.stopSnakeFlag == 0)
	{
		switch (snakeObject.snakeDirectionHead)
		{
		case DOWN:
			(*snakeObject.GODOWN)();
			break;
		default:
			snakeObject.snakeDirectionHead = UP;
			infoXYSnake tempSnake1;
			infoXYSnake tempSnake2;
			for (int i = 0; i < snakeObject.snakeLength; i++)
			{
				if (i == 0)
				{
					tempSnake1 = snakeObject.infoSnake[i];
					snakeObject.infoSnake[i].x = snakeObject.infoSnake[i].x;
					snakeObject.infoSnake[i].y -= snakeStep;
					drawHeadSnake();
				}
				else
				{
					tempSnake2 = snakeObject.infoSnake[i];
					snakeObject.infoSnake[i] = tempSnake1;
					tempSnake1 = tempSnake2;
					if (i == 1)
						lcd_Fill(snakeObject.infoSnake[i].x, snakeObject.infoSnake[i].y,
								 snakeObject.infoSnake[i].x + snakeWidth, snakeObject.infoSnake[i].y + snakeWidth, BLACK);
					if (i == snakeObject.snakeLength - 1)
					{
						snakeObject.infoTempSnakeTail = tempSnake2;
						lcd_Fill(tempSnake2.x, tempSnake2.y, tempSnake2.x + snakeWidth, tempSnake2.y + snakeWidth, WHITE);
					}
				}
			}
			break;
		}
	}
}

void goDown()
{
	if (snakeObject.stopSnakeFlag == 0)
	{
		switch (snakeObject.snakeDirectionHead)
		{
		case UP:
			(*snakeObject.GOUP)();
			break;
		default:
			snakeObject.snakeDirectionHead = DOWN;
			infoXYSnake tempSnake1;
			infoXYSnake tempSnake2;
			for (int i = 0; i < snakeObject.snakeLength; i++)
			{
				if (i == 0)
				{
					tempSnake1 = snakeObject.infoSnake[i];
					snakeObject.infoSnake[i].x = snakeObject.infoSnake[i].x;
					snakeObject.infoSnake[i].y += snakeStep;
					drawHeadSnake();
				}
				else
				{
					tempSnake2 = snakeObject.infoSnake[i];
					snakeObject.infoSnake[i] = tempSnake1;
					tempSnake1 = tempSnake2;
					if (i == 1)
						lcd_Fill(snakeObject.infoSnake[i].x, snakeObject.infoSnake[i].y,
								 snakeObject.infoSnake[i].x + snakeWidth, snakeObject.infoSnake[i].y + snakeWidth, BLACK);
					if (i == snakeObject.snakeLength - 1)
					{
						snakeObject.infoTempSnakeTail = tempSnake2;
						lcd_Fill(tempSnake2.x, tempSnake2.y, tempSnake2.x + snakeWidth, tempSnake2.y + snakeWidth, WHITE);
					}
				}
			}
			break;
		}
	}
}

void resumeGame()
{
	uartSendContinuePlay();
	lcd_Fill(0, wallY[0] + wallSize, 240, 320, WHITE);
	for (int i = 0; i < snakeObject.snakeLength; i++)
	{
		if (i == 0)
			drawHeadSnake();
		else
			lcd_Fill(snakeObject.infoSnake[i].x, snakeObject.infoSnake[i].y,
					 snakeObject.infoSnake[i].x + snakeWidth, snakeObject.infoSnake[i].y + snakeWidth, BLACK);
	}
	// print wall again
	for (int i = 0; i < wallObject.amountWallElement; i++)
	{
		int X = wallObject.infoWall[i].x;
		int Y = wallObject.infoWall[i].y;
		lcd_Fill(X, Y, X + snakeWidth, Y + snakeWidth, BROWN);
		if (wallObject.infoWall[i].vertical == 1)
		{
			lcd_Fill(X, Y + snakeStep, X + snakeWidth, Y + snakeStep + snakeWidth, BROWN);
			lcd_Fill(X, Y - snakeStep, X + snakeWidth, Y - snakeStep + snakeWidth, BROWN);
		}
		else
		{
			lcd_Fill(X + snakeStep, Y, X + snakeStep + snakeWidth, Y + snakeWidth, BROWN);
			lcd_Fill(X - snakeStep, Y, X - snakeStep + snakeWidth, Y + snakeWidth, BROWN);
		}
	}
	lcd_Fill(xFruit, yFruit, xFruit + snakeWidth, yFruit + snakeWidth, DARKBLUE);
}

int checkOutOfValidRange()
{
	if ((snakeObject.infoSnake[0].x < 0) || (snakeObject.infoSnake[0].x > 230) || (snakeObject.infoSnake[0].y < 70) || (snakeObject.infoSnake[0].y > 312))
		return 1;
	return 0;
}

int checkEatBody()
{
	for (int i = 1; i < snakeObject.snakeLength; i++)
		if (snakeObject.infoSnake[0].x == snakeObject.infoSnake[i].x && snakeObject.infoSnake[0].y == snakeObject.infoSnake[i].y)
			return 1;
	return 0;
}

int checkEatFruit()
{
	if (snakeObject.infoSnake[0].x == xFruit && snakeObject.infoSnake[0].y == yFruit)
		return 1;
	return 0;
}

int checkHitWall()
{
	for (int i = 0; i < wallObject.amountWallElement; i++)
	{
		if (wallObject.infoWall[i].vertical == 1)
		{
			if ((snakeObject.infoSnake[0].y == wallObject.infoWall[i].y - snakeStep ||
				 snakeObject.infoSnake[0].y == wallObject.infoWall[i].y + snakeStep ||
				 snakeObject.infoSnake[0].y == wallObject.infoWall[i].y) &&
				(snakeObject.infoSnake[0].x == wallObject.infoWall[i].x))
			{
				return 1;
			}
		}
		else
		{
			if ((snakeObject.infoSnake[0].x == wallObject.infoWall[i].x + snakeStep ||
				 snakeObject.infoSnake[0].x == wallObject.infoWall[i].x - snakeStep ||
				 snakeObject.infoSnake[0].x == wallObject.infoWall[i].x) &&
				(snakeObject.infoSnake[0].y == wallObject.infoWall[i].y))
			{
				return 1;
			}
		}
	}
	return 0;
}
void checkHead()
{
	if (checkOutOfValidRange())
	{
		// showGameOver;
		initOverMode(3);
		//		lcd_ShowStr(10, 20, "NGU", WHITE, RED, 40, 0);
		//		lcd_ShowStr (20 , 30 , " Test lcd screen ", WHITE , RED , 24 ,
		//		0) ;
		return;
	}
	if (checkEatBody())
	{
		// ShowGameover
		initOverMode(2);
		//		lcd_ShowStr(10, 20, "NGU", WHITE, RED, 40, 0);
		//		lcd_ShowStr (20 , 30 , " Test lcd screen ", WHITE , RED , 24 ,
		//		0) ;
		return;
	}
	if (checkHitWall())
	{
		// showGameover
		initOverMode(0);
		//		lcd_ShowStr(10, 20, "NGU", WHITE, RED, 40, 0);
		//		lcd_ShowStr (20 , 30 , " Test lcd screen ", WHITE , RED , 24 ,
		//		0) ;
		return;
	}
	if (checkEatFruit())
	{
		xFruit = INT_MIN;
		yFruit = INT_MIN;
		snakeObject.snakeLength += 1;
		snakeObject.infoSnake[snakeObject.snakeLength - 1].x = snakeObject.infoTempSnakeTail.x;
		snakeObject.infoSnake[snakeObject.snakeLength - 1].y = snakeObject.infoTempSnakeTail.y;
		int x = snakeObject.infoSnake[snakeObject.snakeLength - 1].x;
		int y = snakeObject.infoSnake[snakeObject.snakeLength - 1].y;
		lcd_Fill(x, y, x + snakeWidth, y + snakeWidth, BLACK);
		flagEat = 1;

		SCORE++;
		printScore();
		return;
	}
}

void move()
{
	switch (snakeObject.snakeDirectionHead)
	{
	case DOWN:
		(*snakeObject.GODOWN)();
		break;
	case UP:
		(*snakeObject.GOUP)();
		break;
	case RIGHT:
		(*snakeObject.GORIGHT)();
		break;
	case LEFT:
		(*snakeObject.GOLEFT)();
		break;
	default:
		break;
	}
}

void wallInit()
{
	for (int i = 0; i < MAX_LENGTH; i++)
	{
		wallObject.infoWall[i].x = 0;
		wallObject.infoWall[i].y = 0;
		wallObject.infoWall[i].vertical = 0;
	}
	wallObject.amountWallElement = 0;
	wallObject.vertical = 1;
	wallObject.stopGenerateWallFlag = 0;
}

void snakeRun()
{
	if (buttonForSnake[0])
	{
		buttonForSnake[0]= 0;
		(*snakeObject.GOUP)();
		(*snakeObject.CHECKHEAD)();
	}
	else
	{
		if (buttonForSnake[1])
		{
			buttonForSnake[1]= 0;
			(*snakeObject.GOLEFT)();
			(*snakeObject.CHECKHEAD)();
		}
		else
		{
			if (buttonForSnake[2])
			{
				buttonForSnake[2]= 0;
				snakeObject.stopSnakeFlag = !snakeObject.stopSnakeFlag;
				wallObject.stopGenerateWallFlag = !wallObject.stopGenerateWallFlag;
				snakeObject.stopSnakeFlag = initStopGame(snakeObject.stopSnakeFlag);
			}
			else
			{
				if (buttonForSnake[3])
				{
					buttonForSnake[3]= 0;
					(*snakeObject.GORIGHT)();
					(*snakeObject.CHECKHEAD)();
				}
				else
				{
					if (buttonForSnake[4])
					{
						buttonForSnake[4]= 0;
						lcd_Clear(WHITE);
						xFruit = INT_MIN;
						yFruit = INT_MIN;
						snakeInit();
						wallInit();
						lcd_Fill(0, 0, 240, 70, RED);
						flagEat = 1;
					}
					else
					{
						if (buttonForSnake[5])
						{
							buttonForSnake[5]= 0;
							(*snakeObject.GODOWN)();
							(*snakeObject.CHECKHEAD)();
						}
						else
						{
							(*snakeObject.MOVE)();
							(*snakeObject.CHECKHEAD)();
						}
					}
				}
			}
		}
	}
}

void snakeInit()
{
	srand(rst);
	rst++;
	flagEat = 1;
	snakeObject.stopSnakeFlag = 0;
	snakeObject.infoSnake[0].x = 20;
	snakeObject.infoSnake[0].y = rangeValidYLower;
	snakeObject.infoSnake[1].x = 10;
	snakeObject.infoSnake[1].y = rangeValidYLower;
	snakeObject.infoSnake[2].x = 0;
	snakeObject.infoSnake[2].y = rangeValidYLower;
	for (int i = 3; i < MAX_LENGTH; i++)
	{
		snakeObject.infoSnake[i].x = 0;
		snakeObject.infoSnake[i].y = 0;
	}
	snakeObject.GODOWN = goDown;
	snakeObject.GOLEFT = goLeft;
	snakeObject.GOUP = goUp;
	snakeObject.GORIGHT = goRight;
	snakeObject.MOVE = move;
	snakeObject.CHECKHEAD = checkHead;
	snakeObject.snakeLength = 3;
	snakeObject.snakeDirectionHead = RIGHT;
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
			drawHeadSnake();
		else
			lcd_Fill(snakeObject.infoSnake[i].x, snakeObject.infoSnake[i].y,
					 snakeObject.infoSnake[i].x + snakeWidth, snakeObject.infoSnake[i].y + snakeWidth, BLACK);
	}
}

void generateFruit()
{
	if (flagEat == 1)
	{
		while (1)
		{
			int remind = 0;
			xFruit = (rand() % (rangeXGenerate + 1)) * snakeStep;
			yFruit = (rand() % (rangeYGenerate + 1) + 7) * snakeStep;
			for (int i = 0; i < snakeObject.snakeLength; i++)
			{
				if (xFruit == snakeObject.infoSnake[i].x && yFruit == snakeObject.infoSnake[i].y)
				{
					xFruit = INT_MIN;
					yFruit = INT_MIN;
					remind = 1;
					break;
				}
			}
			if (remind)
				continue;
			for (int i = 0; i < wallObject.amountWallElement; i++)
			{
				if (wallObject.infoWall[i].vertical == 1)
				{
					if ((wallObject.infoWall[i].y == yFruit ||
						 wallObject.infoWall[i].y + snakeStep == yFruit ||
						 wallObject.infoWall[i].y - snakeStep == yFruit) &&
						(wallObject.infoWall[i].x == xFruit))
					{
						remind = 1;
						break;
					}
				}
				else
				{
					if ((wallObject.infoWall[i].x == xFruit ||
						wallObject.infoWall[i].x + snakeStep == xFruit ||
						wallObject.infoWall[i].x - snakeStep == xFruit) &&
						(wallObject.infoWall[i].y == yFruit))
					{
						remind = 1;
						break;
					}
				}
			}
			if (remind)
				continue;
			lcd_Fill(xFruit, yFruit, xFruit + snakeWidth, yFruit + snakeWidth, DARKBLUE);
			flagEat = 0;
			break;
		}
	}
}

void generateWall()
{
	if (wallObject.amountWallElement >= WALL)
	{
		return;
	}
	if (wallObject.stopGenerateWallFlag == 0)
	{
		while (1)
		{
			int remind = 0;
			int X = (rand() % (rangeXGenerate - 1) + 1) * snakeStep;
			int Y = (rand() % (rangeYGenerate - 1) + 8) * snakeStep;
			// check conflict with exist wall
			for (int i = 0; i < wallObject.amountWallElement; i++)
			{
				int x = wallObject.infoWall[i].x;
				int y = wallObject.infoWall[i].y;
				if (wallObject.vertical == 1)
				{
					if (wallObject.infoWall[i].vertical == 1)
					{
						if ((y - 2 * snakeStep == Y || y + 2 * snakeStep == Y || y - snakeStep == Y ||
							 y + snakeStep == Y || y == Y) &&
							(x == X))
						{
							remind = 1;
							break;
						}
					}
					else
					{
						if (((y - snakeStep == Y || y + snakeStep == Y || y == Y) && (x == X)) ||
							((y - snakeStep == Y || y + snakeStep == Y || y == Y) && (x - snakeStep == X)) ||
							((y - snakeStep == Y || y + snakeStep == Y || y == Y) && (x + snakeStep == X)))
						{
							remind = 1;
							//							break;
						}
					}
				}
				else
				{
					if (wallObject.infoWall[i].vertical == 1)
					{
						if (((x - snakeStep == X || x + snakeStep == X || x == X) && (y == Y)) ||
							((x - snakeStep == X || x + snakeStep == X || x == X) && (y - snakeStep == Y)) ||
							((x - snakeStep == X || x + snakeStep == X || x == X) && (y + snakeStep == Y)))
						{
							remind = 1;
							break;
						}
					}
					else
					{
						if ((x - 2 * snakeStep == X || x + 2 * snakeStep == X || x + snakeStep == X ||
							 x - snakeStep == X || x == X) &&
							(y == Y))
						{
							remind = 1;
							break;
						}
					}
				}
			}
			if (remind)
				continue;
			// check conflict with snake
			for (int i = 0; i < snakeObject.snakeLength; i++)
			{
				int x = snakeObject.infoSnake[i].x;
				int y = snakeObject.infoSnake[i].y;
				if (wallObject.vertical == 1)
				{
					if ((X == x) && (Y == y || Y - snakeStep == y || Y + snakeStep == y))
					{
						remind = 1;
						break;
					}
				}
				else
				{
					if ((Y == y) && (X == x || X - snakeStep == x || X + snakeStep == x))
					{
						remind = 1;
						break;
					}
				}
			}
			if (remind)
				continue;
			// check conflict with head snake
			switch (snakeObject.snakeDirectionHead)
			{
			case UP:
				if ((snakeObject.infoSnake[0].x == X) && (snakeObject.infoSnake[0].y - snakeStep == Y))
					remind = 1;
				break;
			case DOWN:
				if ((snakeObject.infoSnake[0].x == X) && (snakeObject.infoSnake[0].y + snakeStep == Y))
					remind = 1;
				break;
			case LEFT:
				if ((snakeObject.infoSnake[0].x - snakeStep == X) && (snakeObject.infoSnake[0].y == Y))
					remind = 1;
				break;
			case RIGHT:
				if ((snakeObject.infoSnake[0].x + snakeStep == X) && (snakeObject.infoSnake[0].y== Y))
					remind= 1;
				break;
				default:
					break;
			}
			if (remind)
				continue;
			// check conflict with fruit
			if (wallObject.vertical == 1)
			{
				if ((X == xFruit) && (Y == yFruit || Y - snakeStep == yFruit || Y + snakeStep == yFruit))
					continue;
			}
			else
			{
				if ((Y == yFruit) && (X == xFruit || X - snakeStep == xFruit || X + snakeStep == xFruit))
					continue;
			}
			wallObject.infoWall[wallObject.amountWallElement].x = X;
			wallObject.infoWall[wallObject.amountWallElement].y = Y;
			lcd_Fill(X, Y, X + snakeWidth, Y + snakeWidth, BROWN);
			if (wallObject.vertical == 1)
			{
				lcd_Fill(X, Y + snakeStep, X + snakeWidth, Y + snakeStep + snakeWidth, BROWN);
				lcd_Fill(X, Y - snakeStep, X + snakeWidth, Y - snakeStep + snakeWidth, BROWN);
				wallObject.infoWall[wallObject.amountWallElement].vertical = 1;
			}
			else
			{
				lcd_Fill(X + snakeStep, Y, X + snakeStep + snakeWidth, Y + snakeWidth, BROWN);
				lcd_Fill(X - snakeStep, Y, X - snakeStep + snakeWidth, Y + snakeWidth, BROWN);
				wallObject.infoWall[wallObject.amountWallElement].vertical = 0;
			}
			wallObject.amountWallElement++;
			wallObject.vertical = !wallObject.vertical;
			break;
		}
	}
}

void stopSnake()
{
	snakeObject.stopSnakeFlag = 1;
}
