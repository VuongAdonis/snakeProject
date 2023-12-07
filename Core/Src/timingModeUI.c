/*
 * timingModeUI.c
 *
 *  Created on: Dec 7, 2023
 *      Author: Acer
 */


#include "timingModeUI.h"
#include "global.h"
#include "picture.h"
#include "lcd.h"
#include "button.h"

void setupTiming()
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

	lcd_ShowStr(20, 210, "TIME:", WHITE, GRAY, 24, 0);
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
		lcd_DrawLine(165, 200, 185, 200, WHITE);
		lcd_DrawLine(175, 180, 165, 200, WHITE);
		lcd_DrawLine(185, 200, 175, 180, WHITE);
	}
	if(TIMING > 30)
	{
		lcd_DrawLine(165, 250, 185, 250, WHITE);
		lcd_DrawLine(165, 250, 175, 270, WHITE);
		lcd_DrawLine(185, 250, 175, 270, WHITE);
	}
}

void showTiming()
{
	char str5[50] = "TIMING: ";
	char *str6 = convert2str(TIMING);
	strcat(str5, str6);
	lcd_Fill(timingX, timingY, timingX+90, timingY+15, BLUE);
	lcd_ShowStr(timingX, timingY, str5, RED, BLUE, 16, 0);
}

void initTimingMode()
{
	if(button_count[3] == 1)
	{
		TIMING = TIMING + 30;
		if(TIMING > 120)
		{
			TIMING = 120;
		}
		setupTiming();
	}
	if(button_count[7] == 1)
	{
		TIMING = TIMING - 30;
		if(TIMING < 30)
		{
			TIMING = 30;
		}
		setupTiming();
	}
}
