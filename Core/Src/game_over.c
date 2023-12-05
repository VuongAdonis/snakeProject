/*
 * gameOver.c
 *
 *  Created on: Dec 5, 2023
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

void showWallnotify()
{
	lcd_Fill(overWallX[0], overWallY[0], overWallX[3], overWallY[3] - wallSize, GRAY);

	// Wall top
	lcd_Fill(overWallX[0], overWallY[0], overWallX[1], overWallY[1] + wallSize, BLACK);
	// Wall left
	lcd_Fill(overWallX[0], overWallY[0], overWallX[2] + wallSize, overWallY[2], BLACK);
	//Wall right
	lcd_Fill(overWallX[1] - wallSize, overWallY[1], overWallX[3], overWallY[3], BLACK);
	//Wall bottom
	lcd_Fill(overWallX[2], overWallY[2] - wallSize, overWallX[3], overWallY[3], BLACK);

}

void showNotifyOver()
{
	lcd_StrCenter(0, overWallY[0] + 10, "GAME OVER", BLACK, GRAY, 16, 1);

	lcd_ShowStr(overWallX[0]+8, (overWallY[2]+overWallY[0])/2 - 15, "NEW GAME", BLACK, GRAY, 16, 1);

	lcd_ShowStr(overWallX[0]+8, (overWallY[2]+overWallY[0])/2 + 20, "EXIT", BLACK, GRAY, 16, 1);
}

void eraseFull()
{
	lcd_Fill(overWallX[0] + wallSize, overWallY[0] + 25, overWallX[1] - wallSize, overWallY[3]-5, GRAY);
}

void drawArrowOver()
{
	int yValNewGame = (overWallY[2]+overWallY[0])/2 - 15 + 7;
	int yValExit = (overWallY[2]+overWallY[0])/2 + 20 + 8;

	switch(arrowOverMode)
	{
	case NEWGAME:
		eraseFull();
		lcd_ShowStr(overWallX[0]+8, (overWallY[2]+overWallY[0])/2 - 15, "NEW GAME", RED, GRAY, 16, 1);
		lcd_ShowStr(overWallX[0]+8, (overWallY[2]+overWallY[0])/2 + 20, "EXIT", BLACK, GRAY, 16, 1);
		lcd_DrawLine(overWallX[1] - 15, yValNewGame, overWallX[1] - 10, yValNewGame - 5, BLACK);
		lcd_DrawLine(overWallX[1] - 15, yValNewGame, overWallX[1] - 10, yValNewGame + 5, BLACK);
		lcd_DrawLine(overWallX[1] - 10, yValNewGame - 5, overWallX[1] - 10, yValNewGame + 5, BLACK);
		break;
	case EXIT:
		eraseFull();
		lcd_ShowStr(overWallX[0]+8, (overWallY[2]+overWallY[0])/2 - 15, "NEW GAME", BLACK, GRAY, 16, 1);
		lcd_ShowStr(overWallX[0]+8, (overWallY[2]+overWallY[0])/2 + 20, "EXIT", RED, GRAY, 16, 1);
		lcd_DrawLine(overWallX[1] - 15, yValExit, overWallX[1] - 10, yValExit - 5, BLACK);
		lcd_DrawLine(overWallX[1] - 15, yValExit, overWallX[1] - 10, yValExit + 5, BLACK);
		lcd_DrawLine(overWallX[1] - 10, yValExit - 5, overWallX[1] - 10, yValExit + 5, BLACK);
		break;
	}
}

void gameOverUI()
{
	showOver();
	showNotifyOver();
	drawArrowOver();
}

void pickOver()
{
	if(statusGame == OVERMODE)
	{
		if(button_count[3] == 1)
		{
			switch(arrowOverMode)
			{
			case NEWGAME:
				// Do nothing
				return;
				break;
			case EXIT:
				arrowOverMode = NEWGAME;
				gameOverUI();
				break;
			}
		}
		if(button_count[7] == 1)
		{
			switch(arrowOverMode)
			{
			case NEWGAME:
				arrowOverMode = EXIT;
				gameOverUI();
				break;
			case EXIT:
				// Do nothing
				return;
				break;
			}
		}
	}
}
