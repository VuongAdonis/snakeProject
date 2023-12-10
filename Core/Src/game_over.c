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
#include "uart.h"

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

void showNotifyOver(uint16_t overVal)
{
	char str1[50] = "";
	char* str2;
	switch(overVal)
	{
	case 0:
		str2 = " HIT WALL ";
		break;
	case 1:
		str2 = " TIME OUT ";
		break;
	case 2:
		str2 = " EAT BODY ";
		break;
	case 3:
		str2 = " OUT OF RANGE ";
		break;
	}
	strcat(str1, str2);
	lcd_StrCenter(0, overWallY[0] + 10, str1, WHITE, BLACK, 16, 0);

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

void gameOverUI(uint16_t overVal)
{
	showWallnotify();
	showNotifyOver(overVal);
	drawArrowOver();
}

void pickOver(uint16_t overVal)
{
	if(button_count[3] == 1)
	{
		flagOver = 1;
		switch(arrowOverMode)
		{
		case NEWGAME:
			// Do nothing
			return;
			break;
		case EXIT:
			arrowOverMode = NEWGAME;
			break;
		}
	}
	if(button_count[7] == 1)
	{
		flagOver = 1;
		switch(arrowOverMode)
		{
		case NEWGAME:
			arrowOverMode = EXIT;
			break;
		case EXIT:
			// Do nothing
			return;
			break;
		}
	}
	if(flagOver == 1)
	{
		gameOverUI(overVal);
		flagOver = 0;
	}
}

void initOverMode(uint16_t overVal)
{
	TOTALSCORE = TOTALSCORE + SCORE;
	TOTALTIMEPLAY = TOTALTIMEPLAY + TOTALTIME;
	TOTALPLAY = TOTALPLAY + 1;

	char str1[70] = "GAME_FINISH#";
	char *str2 = convert2str(ID);
	strcat(str1, str2);
	char str3[50] = "has finished game, performance value: ";
	char *str4 = convert2str(SCORE);
	strcat(str3, str4);
	strcat(str1, str3);
	strcat(str1, "#");

	char *str5 = convert2str(TOTALSCORE/TOTALPLAY);
	strcat(str1, str5);
	strcat(str1, "#");

	char *str6 = convert2str(TOTALTIMEPLAY/TOTALPLAY);
	strcat(str1, str6);
	strcat(str1, "#");
	uart_EspSendBytes(str1, strlen(str1));

	statusGame = OVERMODE;
	SCORE = 0;
	TOTALTIME = 0;
	arrowOverMode = NEWGAME;
	flagOver = 1;
	pickOver(overVal);
	OVERMESSAGE = overVal;

}
