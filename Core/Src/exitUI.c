/*
 * exitUI.c
 *
 *  Created on: Dec 8, 2023
 *      Author: Acer
 */

#include <game_over.h>
#include "lcd.h"
#include "startGame.h"
#include "set_up_mode.h"
#include "global.h"
#include "main.h"
#include "button.h"
#include "picture.h"
#include "exitUI.h"

void eraseEverything()
{

}

void showNotifyExit()
{
	lcd_StrCenter(0, overWallY[0] + 5, "DO YOU WANT", WHITE, BLACK, 16, 0);
	lcd_StrCenter(0, overWallY[0] + 20, "TO EXIT?", WHITE, BLACK, 16, 0);

	lcd_ShowStr(overWallX[0]+8, (overWallY[2]+overWallY[0])/2 - 20, "YES", BLACK, GRAY, 16, 1);

	lcd_ShowStr(overWallX[0]+8, (overWallY[2]+overWallY[0])/2 + 25, "NO", BLACK, GRAY, 16, 1);
}

void drawArrowExit()
{
	int yValNewGame = (overWallY[2]+overWallY[0])/2 - 15 + 7;
	int yValExit = (overWallY[2]+overWallY[0])/2 + 20 + 8;

	switch(arrowExitMode)
	{
	case YES:
		lcd_Fill(overWallX[0] + wallSize, overWallY[0] + 35, overWallX[1] - wallSize, overWallY[3]-5, GRAY);

		lcd_ShowStr(overWallX[0]+8, (overWallY[2]+overWallY[0])/2 - 15, "YES", RED, GRAY, 16, 1);
		lcd_ShowStr(overWallX[0]+8, (overWallY[2]+overWallY[0])/2 + 20, "NO", BLACK, GRAY, 16, 1);
		lcd_DrawLine(overWallX[1] - 15, yValNewGame, overWallX[1] - 10, yValNewGame - 5, BLACK);
		lcd_DrawLine(overWallX[1] - 15, yValNewGame, overWallX[1] - 10, yValNewGame + 5, BLACK);
		lcd_DrawLine(overWallX[1] - 10, yValNewGame - 5, overWallX[1] - 10, yValNewGame + 5, BLACK);
		break;
	case NO:
		lcd_Fill(overWallX[0] + wallSize, overWallY[0] + 35, overWallX[1] - wallSize, overWallY[3]-5, GRAY);

		lcd_ShowStr(overWallX[0]+8, (overWallY[2]+overWallY[0])/2 - 15, "YES", BLACK, GRAY, 16, 1);
		lcd_ShowStr(overWallX[0]+8, (overWallY[2]+overWallY[0])/2 + 20, "NO", RED, GRAY, 16, 1);
		lcd_DrawLine(overWallX[1] - 15, yValExit, overWallX[1] - 10, yValExit - 5, BLACK);
		lcd_DrawLine(overWallX[1] - 15, yValExit, overWallX[1] - 10, yValExit + 5, BLACK);
		lcd_DrawLine(overWallX[1] - 10, yValExit - 5, overWallX[1] - 10, yValExit + 5, BLACK);
		break;
	}
}

void gameExitUI()
{
	showWallnotify();
	showNotifyExit();
	drawArrowExit();
}

void askToExit()
{
	if(statusGame == EXITMODE)
	{
		if(button_count[3] == 1)
		{
			flagExit = 1;
			switch(arrowExitMode)
			{
			case YES:
				// Do nothing
				return;
				break;
			case NO:
				arrowExitMode = YES;
				break;
			}
		}
		if(button_count[7] == 1)
		{
			flagExit = 1;
			switch(arrowExitMode)
			{
			case YES:
				arrowExitMode = NO;
				break;
			case NO:
				// Do nothing
				return;
				break;
			}
		}
		if(flagExit == 1)
		{
			gameExitUI();
			flagExit = 0;
		}
	}
}

void initExit()
{
	gameExitUI();
}
