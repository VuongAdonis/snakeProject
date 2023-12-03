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

void startUI(){
	char str1[50] = "";

	lcd_Clear(BLACK);
//	lcd_Fill(0, 0, 240, 30, BLACK);
	lcd_ShowStr(60, 5, " SNAKE GAME ", WHITE, GRAY, 24, 0);

	lcd_ShowStr(40, 50, " ENTER YOUR ID ", WHITE, GRAY, 24, 0);

	lcd_DrawRectangle(60, 100, 180, 130, WHITE);

	char *str2 = convert2str(ID);
	strcat(str1, str2);
	lcd_StrCenter(0, 105, str1, WHITE, RED, 24, 0);

	lcd_ShowStr(80, 180, " START ", WHITE, GRAY, 24, 0);
}

void pickMode(uint16_t id){
	lcd_Clear(BLACK);
	lcd_Fill(0, 0, 240, 30, BLACK);
	lcd_ShowStr(60, 5, " SNAKE GAME ", WHITE, GRAY, 24, 0);

	char str1[50] = " ID: ";
	char *str2 = convert2str(id);
	strcat(str1, str2);

	lcd_StrCenter(0, 50, str1, WHITE, GRAY, 24, 0);

	lcd_StrCenter(0, 100, " MODE ", WHITE, GRAY, 24, 0);

	lcd_ShowStr(10, 150, " NORMAL MODE ", WHITE, GRAY, 24, 0);
	lcd_ShowStr(10, 200, " TIMING MODE ", WHITE, GRAY, 24, 0);
}

void beginStartGame()
{
	if(button_count[14] == 1)
	{
		switch (statusGame) {
			case INIT:
				statusGame = STARTMODE;
				ID = 0;
				point = 0;
				startUI();
				break;
			case STARTMODE:
				statusGame = PICKMODE;
				pickMode(ID);
				button_count[14] = 0;
				break;
			case PICKMODE:
				statusGame = NORMALMODE;
				setUpLcdPlay(ID);
				button_count[14] = 0;
				break;
			case NORMALMODE:
				statusGame = INIT;
				setUpLcdPlay(ID);
				button_count[14] = 0;
				break;
			case TIMINGMODE:
				statusGame = INIT;
				setUpLcdPlay(ID);
				button_count[14] = 0;
				break;
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
				lcd_Fill(60, 100, 180, 130, BLACK);
				lcd_DrawRectangle(60, 100, 180, 130, WHITE);
				lcd_StrCenter(0, 105, str1, WHITE, RED, 24, 0);
			}
		}
	}
	else
	{
		if(button_count[12] == 1)
		{
			statusGame = INIT;
			ID = 0;
			point = 0;
			startUI();
		}
	}
}
