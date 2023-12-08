/*
 * advanceModeUI.c
 *
 *  Created on: Dec 7, 2023
 *      Author: Acer
 */


#include "advanceModeUI.h"
#include "global.h"
#include "picture.h"
#include "lcd.h"
#include "button.h"

void setupAdvance()
{
	lcd_Clear(BLACK);

	//	lcd_Fill(0, 0, 240, 30, BLACK);

	lcd_ShowPicture(logoBKX, logoBKY, logoBKHeight, logoBKWidth, gImage_BKWHITEBG);

	lcd_ShowStr(60, 55, " SNAKE GAME ", WHITE, GRAY, 24, 0);

	char str1[50] = " ID: ";
	char *str2 = convert2str(ID);
	strcat(str1, str2);

	lcd_StrCenter(0, 100, str1, WHITE, GRAY, 24, 0);

	lcd_StrCenter(0, 150, " MODE: TIMING", WHITE, GRAY, 24, 0);

	lcd_ShowStr(20, 215, " TIME:", WHITE, GRAY, 24, 0);
	lcd_DrawRectangle(150, 210, 200, 240, WHITE);

	char *str3 = convert2str(TIMING);
	if(TIMING < 120)
	{
		lcd_ShowStr(165, 212, str3, WHITE, GRAY, 24, 1);
	}else{
		lcd_ShowStr(157, 212, str3, WHITE, GRAY, 24, 1);
	}

	if(TIMING < 120)
	{
		lcd_DrawLine(205, 220, 225, 220, WHITE);
		lcd_DrawLine(205, 220, 215, 210, WHITE);
		lcd_DrawLine(225, 220, 215, 210, WHITE);
	}
	if(TIMING > 30)
	{
		lcd_DrawLine(205, 230, 225, 230, WHITE);
		lcd_DrawLine(205, 230, 215, 240, WHITE);
		lcd_DrawLine(225, 230, 215, 240, WHITE);
	}

	lcd_ShowStr(20, 265, " WALL:", WHITE, GRAY, 24, 0);
	lcd_DrawRectangle(150, 260, 200, 290, WHITE);
	char *str4 = convert2str(WALL);
	if(WALL < 10)
	{
		lcd_ShowStr(170, 265, str4, WHITE, GRAY, 24, 1);
	}else{
		lcd_ShowStr(165, 265, str4, WHITE, GRAY, 24, 1);
	}

	if(WALL < 30)
	{
		lcd_DrawLine(205, 270, 225, 270, WHITE);
		lcd_DrawLine(205, 270, 215, 260, WHITE);
		lcd_DrawLine(225, 270, 215, 260, WHITE);
	}
	if(WALL > 0)
	{
		lcd_DrawLine(205, 280, 225, 280, WHITE);
		lcd_DrawLine(205, 280, 215, 290, WHITE);
		lcd_DrawLine(225, 280, 215, 290, WHITE);
	}
}

void initAdvanceMode()
{
	if(button_count[3] == 1)
	{
		TIMING = TIMING + 30;
		if(TIMING > 120)
		{
			TIMING = 120;
		}
		setupAdvance();
	}
	if(button_count[7] == 1)
	{
		TIMING = TIMING - 30;
		if(TIMING < 30)
		{
			TIMING = 30;
		}
		setupAdvance();
	}
	if(button_count[11] == 1)
	{
		WALL = WALL + 5;
		if(WALL > 30)
		{
			WALL = 30;
		}
		setupAdvance();
	}
	if(button_count[15] == 1)
	{
		WALL = WALL - 5;
		if(WALL < 0)
		{
			WALL = 0;
		}
		setupAdvance();
	}
}
