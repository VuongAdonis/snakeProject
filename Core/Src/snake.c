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
#define rangeXGenerate (rangeValidXUpper- rangeValidXLower)/ snakeStep
#define rangeYGenerate (rangeValidYUpper- rangeValidYLower)/ snakeStep

int xFruit= INT_MIN;
int yFruit = INT_MIN;
int flagEat= 1;

typedef struct
{
	int x;
	int y;
}infoXY;

typedef struct
{
	void (*GOLEFT)(void);
	void (*GORIGHT)(void);
	void (*GOUP)(void);
	void (*GODOWN)(void);
	void (*MOVE)(void);
	void (*CHECKHEAD)();
	int snakeDirectionHead;
	infoXY infoTempSnakeTail;
	int snakeLength;
	int stopFlag;
	infoXY infoSnake[MAX_LENGTH];

}SNAKE;

SNAKE snakeObject;

void drawHeadSnake()
{
	switch (snakeObject.snakeDirectionHead)
	{
		case UP:
			lcd_Fill(snakeObject.infoSnake[0].x, snakeObject.infoSnake[0].y,
				snakeObject.infoSnake[0].x+ snakeWidth, snakeObject.infoSnake[0].y+ snakeWidth, RED);
			lcd_Fill(snakeObject.infoSnake[0].x, snakeObject.infoSnake[0].y,
					snakeObject.infoSnake[0].x+ 4, snakeObject.infoSnake[0].y +4, BLACK);
			lcd_Fill(snakeObject.infoSnake[0].x+ 5, snakeObject.infoSnake[0].y,
					snakeObject.infoSnake[0].x+ 9, snakeObject.infoSnake[0].y + 4, BLACK);
			break;
		case DOWN:
			lcd_Fill(snakeObject.infoSnake[0].x, snakeObject.infoSnake[0].y,
				snakeObject.infoSnake[0].x+ snakeWidth, snakeObject.infoSnake[0].y+ snakeWidth, RED);
			lcd_Fill(snakeObject.infoSnake[0].x, snakeObject.infoSnake[0].y+ 5,
					snakeObject.infoSnake[0].x+ 4, snakeObject.infoSnake[0].y +9, BLACK);
			lcd_Fill(snakeObject.infoSnake[0].x+ 5, snakeObject.infoSnake[0].y + 5,
					snakeObject.infoSnake[0].x+ 9, snakeObject.infoSnake[0].y + 9, BLACK);
			break;
		case LEFT:
			lcd_Fill(snakeObject.infoSnake[0].x, snakeObject.infoSnake[0].y,
				snakeObject.infoSnake[0].x+ snakeWidth, snakeObject.infoSnake[0].y+ snakeWidth, RED);
			lcd_Fill(snakeObject.infoSnake[0].x, snakeObject.infoSnake[0].y,
					snakeObject.infoSnake[0].x+ 4, snakeObject.infoSnake[0].y +4, BLACK);
			lcd_Fill(snakeObject.infoSnake[0].x, snakeObject.infoSnake[0].y + 5,
					snakeObject.infoSnake[0].x+ 4, snakeObject.infoSnake[0].y + 9, BLACK);
			break;
		case RIGHT:
			lcd_Fill(snakeObject.infoSnake[0].x, snakeObject.infoSnake[0].y,
				snakeObject.infoSnake[0].x+ snakeWidth, snakeObject.infoSnake[0].y+ snakeWidth, RED);
			lcd_Fill(snakeObject.infoSnake[0].x+ 5, snakeObject.infoSnake[0].y,
					snakeObject.infoSnake[0].x+ 9, snakeObject.infoSnake[0].y +4, BLACK);
			lcd_Fill(snakeObject.infoSnake[0].x+ 5, snakeObject.infoSnake[0].y + 5,
					snakeObject.infoSnake[0].x+ 9, snakeObject.infoSnake[0].y + 9, BLACK);
			break;
		default:
			break;
	}
}

void goLeft()
{
	if (snakeObject.stopFlag== 0)
	{
		switch (snakeObject.snakeDirectionHead)
		{
		case RIGHT:
			(*snakeObject.GORIGHT)();
			break;
		default:
			snakeObject.snakeDirectionHead= LEFT;
			infoXY tempSnake1;
			infoXY tempSnake2;
			for (int i= 0; i < snakeObject.snakeLength; i++)
			{
				if (i== 0)
				{
					tempSnake1= snakeObject.infoSnake[i];
					snakeObject.infoSnake[i].x-= snakeStep;
					snakeObject.infoSnake[i].y= snakeObject.infoSnake[i].y;
					drawHeadSnake();
				}
				else
				{
					tempSnake2= snakeObject.infoSnake[i];
					snakeObject.infoSnake[i]= tempSnake1;
					tempSnake1= tempSnake2;
					if (i== 1)
						lcd_Fill(snakeObject.infoSnake[i].x, snakeObject.infoSnake[i].y,
							snakeObject.infoSnake[i].x+ snakeWidth, snakeObject.infoSnake[i].y+ snakeWidth, BLACK);
					if (i== snakeObject.snakeLength -1)
					{
						snakeObject.infoTempSnakeTail= tempSnake2;
						lcd_Fill(tempSnake2.x, tempSnake2.y, tempSnake2.x+ snakeWidth, tempSnake2.y+ snakeWidth, WHITE);
					}
				}
			}
			break;
		}
	}
}

void goRight()
{
	if (snakeObject.stopFlag== 0)
	{
		switch (snakeObject.snakeDirectionHead)
		{
		case LEFT:
			(*snakeObject.GOLEFT)();
			break;
		default:
			snakeObject.snakeDirectionHead= RIGHT;
			infoXY tempSnake1;
			infoXY tempSnake2;
			for (int i= 0; i < snakeObject.snakeLength; i++)
			{
				if (i== 0)
				{
					tempSnake1= snakeObject.infoSnake[i];
					snakeObject.infoSnake[i].x+= snakeStep;
					snakeObject.infoSnake[i].y= snakeObject.infoSnake[i].y;
					drawHeadSnake();
				}
				else
				{
					tempSnake2= snakeObject.infoSnake[i];
					snakeObject.infoSnake[i]= tempSnake1;
					tempSnake1= tempSnake2;
					if (i== 1)
						lcd_Fill(snakeObject.infoSnake[i].x, snakeObject.infoSnake[i].y,
							snakeObject.infoSnake[i].x+ snakeWidth, snakeObject.infoSnake[i].y+ snakeWidth, BLACK);
					if (i== snakeObject.snakeLength -1)
					{
						snakeObject.infoTempSnakeTail= tempSnake2;
						lcd_Fill(tempSnake2.x, tempSnake2.y, tempSnake2.x+ snakeWidth, tempSnake2.y+ snakeWidth, WHITE);
					}
				}
			}
			break;
		}
	}
}

void goUp()
{
	if (snakeObject.stopFlag== 0)
	{
		switch (snakeObject.snakeDirectionHead)
		{
		case DOWN:
			(*snakeObject.GODOWN)();
			break;
		default:
			snakeObject.snakeDirectionHead= UP;
			infoXY tempSnake1;
			infoXY tempSnake2;
			for (int i= 0; i < snakeObject.snakeLength; i++)
			{
				if (i== 0)
				{
					tempSnake1= snakeObject.infoSnake[i];
					snakeObject.infoSnake[i].x = snakeObject.infoSnake[i].x;
					snakeObject.infoSnake[i].y-= snakeStep;
					drawHeadSnake();
				}
				else
				{
					tempSnake2= snakeObject.infoSnake[i];
					snakeObject.infoSnake[i]= tempSnake1;
					tempSnake1= tempSnake2;
					if (i== 1)
						lcd_Fill(snakeObject.infoSnake[i].x, snakeObject.infoSnake[i].y,
							snakeObject.infoSnake[i].x+ snakeWidth, snakeObject.infoSnake[i].y+ snakeWidth, BLACK);
					if (i== snakeObject.snakeLength -1)
					{
						snakeObject.infoTempSnakeTail= tempSnake2;
						lcd_Fill(tempSnake2.x, tempSnake2.y, tempSnake2.x+ snakeWidth, tempSnake2.y+ snakeWidth, WHITE);
					}
				}
			}
			break;
		}
	}
}

void goDown()
{
	if (snakeObject.stopFlag== 0)
	{
		switch (snakeObject.snakeDirectionHead)
		{
		case UP:
			(*snakeObject.GOUP)();
			break;
		default:
			snakeObject.snakeDirectionHead= DOWN;
			infoXY tempSnake1;
			infoXY tempSnake2;
			for (int i= 0; i < snakeObject.snakeLength; i++)
			{
				if (i== 0)
				{
					tempSnake1= snakeObject.infoSnake[i];
					snakeObject.infoSnake[i].x = snakeObject.infoSnake[i].x;
					snakeObject.infoSnake[i].y+= snakeStep;
					drawHeadSnake();
				}
				else
				{
					tempSnake2= snakeObject.infoSnake[i];
					snakeObject.infoSnake[i]= tempSnake1;
					tempSnake1= tempSnake2;
					if (i== 1)
						lcd_Fill(snakeObject.infoSnake[i].x, snakeObject.infoSnake[i].y,
							snakeObject.infoSnake[i].x+ snakeWidth, snakeObject.infoSnake[i].y+ snakeWidth, BLACK);
					if (i== snakeObject.snakeLength -1)
					{
						snakeObject.infoTempSnakeTail= tempSnake2;
						lcd_Fill(tempSnake2.x, tempSnake2.y, tempSnake2.x+ snakeWidth, tempSnake2.y+ snakeWidth, WHITE);
					}
				}
			}
			break;
		}
	}
}

void resumeGame()
{
	for (int i= 0; i < snakeObject.snakeLength; i++)
	{
		if (i== 0)
			drawHeadSnake();
		else
			lcd_Fill(snakeObject.infoSnake[i].x, snakeObject.infoSnake[i].y,
				snakeObject.infoSnake[i].x+ snakeWidth, snakeObject.infoSnake[i].y+ snakeWidth, BLACK);
	}
}

void checkHead()
{
	lcd_ShowIntNum(100, 100, snakeObject.infoSnake[0].x, 3, BLACK, WHITE, 24);
	lcd_ShowIntNum(150, 100, snakeObject.infoSnake[0].y, 3, BLACK, WHITE, 24);
	if ((snakeObject.infoSnake[0].x < 0) || (snakeObject.infoSnake[0].x > 232)
		|| (snakeObject.infoSnake[0].y < 70) || (snakeObject.infoSnake[0].y > 312))
	{
		// show gameover
		lcd_ShowIntNum(100, 200, 14, 3, RED, WHITE, 24);
	}
	else
	{
		for (int i= 1; i < snakeObject.snakeLength; i++)
		{
			if (snakeObject.infoSnake[0].x== snakeObject.infoSnake[i].x
				&& snakeObject.infoSnake[0].y== snakeObject.infoSnake[i].y)
			{
				// showGameover
				lcd_ShowIntNum(100, 200, 14, 3, RED, WHITE, 24);
				return;
			}
		}
		lcd_ShowIntNum(100, 200, 14, 3, WHITE, WHITE, 24);
		if (snakeObject.infoSnake[0].x== xFruit && snakeObject.infoSnake[0].y== yFruit)
		{
			xFruit= INT_MIN;
			yFruit= INT_MIN;
			snakeObject.snakeLength+= 1;
			snakeObject.infoSnake[snakeObject.snakeLength-1].x= snakeObject.infoTempSnakeTail.x;
			snakeObject.infoSnake[snakeObject.snakeLength-1 ].y= snakeObject.infoTempSnakeTail.y;
			int x= snakeObject.infoSnake[snakeObject.snakeLength-1].x;
			int y= snakeObject.infoSnake[snakeObject.snakeLength-1 ].y;
			lcd_Fill(x, y, x+ snakeWidth, y + snakeWidth, BLACK);
			flagEat= 1;
		}
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

void snakeRun()
{
	if (button_count[5])
	{
		(*snakeObject.GOUP)();
		(*snakeObject.CHECKHEAD)();
	}
	else
	{
	  if (button_count[13])
	  {
		  (*snakeObject.GODOWN)();
		  (*snakeObject.CHECKHEAD)();
	  }
	  else
	  {
		  if (button_count[10])
		  {
			  (*snakeObject.GORIGHT)();
			  (*snakeObject.CHECKHEAD)();
		  }
		  else
		  {
			  if (button_count[8])
			  {
				  (*snakeObject.GOLEFT)();
				  (*snakeObject.CHECKHEAD)();
			  }
			  else
			  {
				  if (button_count[9])
					  snakeObject.stopFlag= !snakeObject.stopFlag;
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

void snakeInit()
{
	snakeObject.infoSnake[0].x= 20;
	snakeObject.infoSnake[0].y= rangeValidYLower;
	snakeObject.infoSnake[1].x= 10;
	snakeObject.infoSnake[1].y= rangeValidYLower;
	snakeObject.infoSnake[2].x= 0;
	snakeObject.infoSnake[2].y= rangeValidYLower;
	for (int i= 3; i < MAX_LENGTH; i++)
	{
		snakeObject.infoSnake[i].x= 0;
		snakeObject.infoSnake[i].y= 0;
	}
	snakeObject.GODOWN= goDown;
	snakeObject.GOLEFT= goLeft;
	snakeObject.GOUP= goUp;
	snakeObject.GORIGHT= goRight;
	snakeObject.MOVE= move;
	snakeObject.CHECKHEAD= checkHead;
	snakeObject.snakeLength= 3;
	snakeObject.snakeDirectionHead= RIGHT;
	for (int i= 0; i < 3; i++)
	{
		if (i== 0)
			drawHeadSnake();
		else
			lcd_Fill(snakeObject.infoSnake[i].x, snakeObject.infoSnake[i].y,
					snakeObject.infoSnake[i].x+ snakeWidth, snakeObject.infoSnake[i].y+ snakeWidth, BLACK);
	}
}

void generateFruit()
{
	if (flagEat== 1)
	{
		xFruit= (rand()%(rangeXGenerate+ 1))*snakeStep;
		yFruit= (rand()%(rangeYGenerate+ 1)+ 7)*snakeStep;
		for (int i= 0; i < snakeObject.snakeLength; i++)
		{
			if (xFruit== snakeObject.infoSnake[i].x && yFruit == snakeObject.infoSnake[i].y)
			{
				xFruit= INT_MIN;
				yFruit= INT_MIN;
				return;
			}
		}
		lcd_Fill(xFruit, yFruit, xFruit+ snakeWidth, yFruit+ snakeWidth, DARKBLUE);
		flagEat= 0;
	}
}
