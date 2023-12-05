/*
 * startGame.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Acer
 */

#include "lcd.h"
#include "startGame.h"
#include "set_up_mode.h"
#include "global.h"
#include "main.h"
#include "button.h"
#include "picture.h"

void startUI(){
	char str1[50] = "";

	lcd_Clear(BLACK);
//	lcd_Fill(0, 0, 240, 30, BLACK);
	lcd_ShowPicture(logoBKX, logoBKY, logoBKHeight, logoBKWidth, gImage_BKWHITEBG);
	lcd_ShowStr(60, 55, " SNAKE GAME ", WHITE, GRAY, 24, 0);

	lcd_ShowStr(40, 100, " ENTER YOUR ID ", WHITE, GRAY, 24, 0);

	lcd_DrawRectangle(60, 150, 180, 180, WHITE);

	char *str2 = convert2str(ID);
	strcat(str1, str2);
	lcd_StrCenter(0, 155, str1, WHITE, RED, 24, 1);

	lcd_ShowStr(80, 230, " START ", WHITE, GRAY, 24, 0);
}

void eraseArrow()
{
	lcd_Fill(ARROWX1, ARROWNORMALY2, ARROWX2+1, 2 * ARROWTIMINGY1 - ARROWNORMALY2 + 1, BLACK);
}

void drawArrow()
{
	// draw arrow
	eraseArrow();
	lcd_DrawLine(arrowX2, arrowY2, arrowX1, arrowY1, WHITE);
	lcd_DrawLine(arrowX1, arrowY1, arrowX2, 2 * arrowY1 - arrowY2, WHITE);
	lcd_DrawLine(arrowX2, arrowY2, arrowX2, 2 * arrowY1 - arrowY2, WHITE);
}

void arrowInPickMode()
{
	if(button_count[3] == 1)
	{
		flagChange = 1;
		//turn arrow up
		switch (arrowMode)
		{
		case NORMALMODE:
			// Do nothing
			break;
		case TIMINGMODE:
			// turn it up to the position of normal mode and take the window up
			arrowMode = NORMALMODE;
			break;
		case ADVANCEMODE:
			// Turn it up to the position of timing mode
			arrowMode = TIMINGMODE;
			flagUpDOwn = 0;
			break;
		}

	}
	if(button_count[7] == 1)
	{
		flagChange = 1;
		//turn arrow down
		switch (arrowMode)
		{
		case NORMALMODE:
			// turn it down to the position of timing mode
			arrowMode = TIMINGMODE;
			flagUpDOwn = 1;
			break;
		case TIMINGMODE:
			// turn it down to the position of advance mode and take the window down
			arrowMode = ADVANCEMODE;
			break;
		case ADVANCEMODE:
			// Do nothing
			break;
		}
	}
	if(flagChange == 1)
	{
		switch (arrowMode)
		{
		case NORMALMODE:
			arrowY1 = ARROWNORMALY1;
			arrowY2 = ARROWNORMALY2;

			// Show normal and timing mode & Draw the triangle show down
			lcd_Fill(0, 180, 240, 320, BLACK);
			lcd_ShowStr(10, 200, " NORMAL MODE ", RED, GRAY, 24, 0);
			lcd_ShowStr(10, 250, " TIMING MODE ", WHITE, GRAY, 24, 0);
			lcd_DrawLine(110, 300, 130, 300, WHITE);
			lcd_DrawLine(110, 300, 120, 310, WHITE);
			lcd_DrawLine(120, 310, 130, 300, WHITE);

			// Draw arrow
			drawArrow();
			break;
		case TIMINGMODE:
			if(flagUpDOwn == 0)
			{
				arrowY1 = ARROWNORMALY1;
				arrowY2 = ARROWNORMALY2;
			}
			else
			{
				arrowY1 = ARROWTIMINGY1;
				arrowY2 = ARROWTIMINGY2;
			}
			lcd_ShowStr(10, 250, " TIMING MODE ", RED, GRAY, 24, 0);
			drawArrow();
			break;
		case ADVANCEMODE:
			arrowY1 = ARROWADVANCEY1;
			arrowY2 = ARROWADVANCEY2;

			// Show timing and advance mode & Draw the triangle show up
			lcd_Fill(0, 180, 240, 320, BLACK);
			lcd_ShowStr(10, 200, " TIMING MODE ", WHITE, GRAY, 24, 0);
			lcd_ShowStr(10, 250, " ADVANCE MODE ", RED, GRAY, 24, 0);
			lcd_DrawLine(110, 190, 130, 190, WHITE);
			lcd_DrawLine(110, 190, 120, 180, WHITE);
			lcd_DrawLine(120, 180, 130, 190, WHITE);

			// draw arrow
			drawArrow();
		}
		flagChange = 0;
	}
}

void pickMode(uint16_t id){
	lcd_Clear(BLACK);

//	lcd_Fill(0, 0, 240, 30, BLACK);

	lcd_ShowPicture(logoBKX, logoBKY, logoBKHeight, logoBKWidth, gImage_BKWHITEBG);

	lcd_ShowStr(60, 55, " SNAKE GAME ", WHITE, GRAY, 24, 0);

	char str1[50] = " ID: ";
	char *str2 = convert2str(id);
	strcat(str1, str2);

	lcd_StrCenter(0, 100, str1, WHITE, GRAY, 24, 0);

	lcd_StrCenter(0, 150, " MODE ", WHITE, GRAY, 24, 0);

	lcd_ShowStr(10, 200, " NORMAL MODE ", WHITE, GRAY, 24, 0);
	lcd_ShowStr(10, 250, " TIMING MODE ", WHITE, GRAY, 24, 0);

	// Draw the triangle show down
	drawArrow();
	lcd_DrawLine(110, 300, 130, 300, WHITE);
	lcd_DrawLine(110, 300, 120, 310, WHITE);
	lcd_DrawLine(120, 310, 130, 300, WHITE);

}

void beginStartGame()
{
	if(button_count[14] == 1)
	{
		switch (statusGame) {
			case INIT:
				statusGame = STARTMODE;
				ID = 0;
				SCORE = 0;
				arrowMode = NORMALMODE;
				TIMING = NOTIMING;
				startUI();
				break;
			case STARTMODE:
				statusGame = PICKMODE;
				pickMode(ID);
				break;
			case PICKMODE:
				statusGame = arrowMode;
				switch (arrowMode)
				{
				case NORMALMODE:
					setUpLcdNormalPlay(ID, SCORE);
					break;
				case TIMINGMODE:
					setUpLcdTimingPlay(ID, TIMING);
					break;
				case ADVANCEMODE:
					setUpLcdAdvancePlay(ID, TIMING);
					break;
				}
				break;
			case NORMALMODE:
				statusGame = STARTMODE;
				ID = 0;
				SCORE = 0;
				arrowMode = NORMALMODE;
				TIMING = NOTIMING;
				startUI();
				break;
			case TIMINGMODE:
				statusGame = STARTMODE;
				ID = 0;
				SCORE = 0;
				arrowMode = NORMALMODE;
				TIMING = NOTIMING;
				startUI();
				break;
			case ADVANCEMODE:
				statusGame = STARTMODE;
				ID = 0;
				SCORE = 0;
				arrowMode = NORMALMODE;
				TIMING = NOTIMING;
				startUI();
			default:
				break;
		}
	}
	if(statusGame == STARTMODE ){
		char str1[50] = "";
		char *str2;
		for(uint16_t i=0; i<14; i++)
		{
			if(button_count[i] == 1)
			{
				button_count[i] == 0;
				switch (i)
				{
					case 0:
						ID = ID*10 + i+1;
						str2 = convert2str(ID);
						strcat(str1, str2);
						break;
					case 1:
						ID = ID*10 + i+1;
						str2 = convert2str(ID);
						strcat(str1, str2);
						break;
					case 2:
						ID = ID*10 + i+1;
						str2 = convert2str(ID);
						strcat(str1, str2);
						break;
					case 3:
						continue;
						break;
					case 4:
						ID = ID*10 + i;
						str2 = convert2str(ID);
						strcat(str1, str2);
						break;
					case 5:
						ID = ID*10 + i;
						str2 = convert2str(ID);
						strcat(str1, str2);
						break;
					case 6:
						ID = ID*10 + i;
						str2 = convert2str(ID);
						strcat(str1, str2);
						break;
					case 7:
						continue;
						break;
					case 8:
						ID = ID*10 + i-1;
						str2 = convert2str(ID);
						strcat(str1, str2);
						break;
					case 9:
						ID = ID*10 + i-1;
						str2 = convert2str(ID);
						strcat(str1, str2);
						break;
					case 10:
						ID = ID*10 + i-1;
						str2 = convert2str(ID);
						strcat(str1, str2);
						break;
					case 11:
						continue;
						break;
					case 12:
						str1[50] = "";
						ID = ID/10;
						str2 = convert2str(ID);
						strcat(str1, str2);
						break;
					case 13:
						ID = ID*10;
						str2 = convert2str(ID);
						strcat(str1, str2);
						break;
				}
				lcd_Fill(60, 150, 180, 180, BLACK);
				lcd_DrawRectangle(60, 150, 180, 180, WHITE);
				lcd_StrCenter(0, 155, str1, WHITE, RED, 24, 1);
			}
		}
	}
	else
	{
		if(statusGame == PICKMODE)
		{
			arrowInPickMode();
		}
		if(button_count[12] == 1)
		{
			statusGame = STARTMODE;
			ID = 0;
			SCORE = 0;
			TIMING = NOTIMING;
			startUI();
			arrowMode = NORMALMODE;
		}
	}
}
