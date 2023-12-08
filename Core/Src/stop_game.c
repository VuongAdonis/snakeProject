/*
 * stop_game.c
 *
 *  Created on: Dec 5, 2023
 *      Author: Acer
 */

#include "lcd.h"
#include "startGame.h"
#include "set_up_mode.h"
#include "global.h"
#include "main.h"
#include "button.h"
#include "picture.h"
#include "stop_game.h"
#include "snake.h"
#include "software_timer.h"

void showNotifyStop()
{

	lcd_StrCenter(0, overWallY[0] + 10, " PAUSE GAME ", WHITE, BLACK, 16, 0);

	lcd_ShowStr(overWallX[0]+8, (overWallY[2]+overWallY[0])/2 - 20, "RESUME", BLACK, GRAY, 16, 1);

	lcd_ShowStr(overWallX[0]+8, (overWallY[2]+overWallY[0])/2 + 15, "EXIT", BLACK, GRAY, 16, 1);
}


void drawArrowStop()
{
	int yValNewGame = (overWallY[2]+overWallY[0])/2 - 15 + 7;
	int yValExit = (overWallY[2]+overWallY[0])/2 + 20 + 8;

	switch(arrowStopMode)
	{
	case RESUME:
		eraseFull();
		lcd_ShowStr(overWallX[0]+8, (overWallY[2]+overWallY[0])/2 - 20, "RESUME", RED, GRAY, 16, 1);
		lcd_ShowStr(overWallX[0]+8, (overWallY[2]+overWallY[0])/2 + 15, "EXIT", BLACK, GRAY, 16, 1);
		lcd_DrawLine(overWallX[1] - 15, yValNewGame, overWallX[1] - 10, yValNewGame - 5, BLACK);
		lcd_DrawLine(overWallX[1] - 15, yValNewGame, overWallX[1] - 10, yValNewGame + 5, BLACK);
		lcd_DrawLine(overWallX[1] - 10, yValNewGame - 5, overWallX[1] - 10, yValNewGame + 5, BLACK);
		break;
	case EXIT:
		eraseFull();
		lcd_ShowStr(overWallX[0]+8, (overWallY[2]+overWallY[0])/2 - 20, "RESUME", BLACK, GRAY, 16, 1);
		lcd_ShowStr(overWallX[0]+8, (overWallY[2]+overWallY[0])/2 + 15, "EXIT", RED, GRAY, 16, 1);
		lcd_DrawLine(overWallX[1] - 15, yValExit, overWallX[1] - 10, yValExit - 5, BLACK);
		lcd_DrawLine(overWallX[1] - 15, yValExit, overWallX[1] - 10, yValExit + 5, BLACK);
		lcd_DrawLine(overWallX[1] - 10, yValExit - 5, overWallX[1] - 10, yValExit + 5, BLACK);
		break;
	}
}

void gameStopUI()
{
	showWallnotify();
	showNotifyStop();
	drawArrowStop();
}

void pickStop()
{
	if(statusGame == STOPMODE)
	{
		if(button_count[3] == 1)
		{
			flagStop = 1;
			switch(arrowStopMode)
			{
			case RESUME:
				// Do nothing
				return;
				break;
			case EXIT:
				arrowStopMode = RESUME;
				gameStopUI();
				break;
			}
		}
		if(button_count[7] == 1)
		{
			flagStop = 1;
			switch(arrowStopMode)
			{
			case RESUME:
				arrowStopMode = EXIT;
				gameStopUI();
				break;
			case EXIT:
				// Do nothing
				return;
				break;
			}
		}
		if(flagStop == 1)
		{
			gameStopUI();
			flagStop = 0;
		}
	}
}

uint8_t initStopGame(uint8_t val)
{
	if(val == 1)
	{
		statusGame = STOPMODE;
		arrowStopMode = RESUME;
		setTimerTiming(0);
		setTimerGenerateWall(0);
		flagStop = 1;
		pickStop();
	}
	return 0;
}
