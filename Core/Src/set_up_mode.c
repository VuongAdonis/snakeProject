/*
 * normal_mode.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Acer
 *//*
 * normal_mode.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Acer
 */

#include "lcd.h"
#include "set_up_mode.h"
#include "global.h"
#include "picture.h"

char *convert2str(uint16_t val)
{
    char str2[50];
    snprintf(str2, sizeof(str2), "%d", val);

    return strdup(str2); // Đảm bảo chuỗi được trả về được giữ nguyên giá trị sau khi thoát khỏi hàm.
}

void lcdDrawWall()
{
	// TOP
//	lcd_DrawRectangle(0, 70, 240 - wall_size, 70 + wall_size, BLACK);
	lcd_Fill(wallX[0], wallY[0], wallX[1], wallY[1] + wallSize, BLACK);
	// LEFT
//	lcd_DrawRectangle(0, 70, wall_size, 320, BLACK);
//	lcd_Fill(wallX[0], wallY[0], wallX[2] + wallSize, wallY[2], BLACK);
	// RIGHT
//	lcd_DrawRectangle(240 - wall_size, 70, 240, 320 - wall_size, BLACK);
//	lcd_Fill(wallX[1] - wallSize, wallY[1], wallX[3], wallY[3], BLACK);
	// BOTTOM
//	lcd_DrawRectangle(240 - wall_size, 320 - wall_size, 240, 320, BLACK);
//	lcd_Fill(wallX[2], wallY[2] - wallSize, wallX[3], wallY[3], BLACK);
}

void setUpLcdNormalPlay(uint16_t id, uint16_t score)
{
	lcd_Clear(WHITE);
	lcd_Fill(0, 0, wallX[1], wallY[0], BLUE);
	lcd_ShowStr(0, 5, " MODE: NORMAL", RED, BLUE, 16, 1);

	char str1[50] = "ID: ";
	char *str2 = convert2str(ID);

	strcat(str1, str2);
	lcd_ShowStr(idX, idY, str1, RED, WHITE, 16, 1);

	char str3[50] = "SCORE: ";
	char *str4 = convert2str(SCORE);
	strcat(str3, str4);
	lcd_ShowStr(scoreX, scoreY+5, str3, RED, BLUE, 16, 0);
	lcd_ShowPicture(logoBKX, logoBKY, logoBKHeight, logoBKWidth, gImage_BKWHITEBG);
//	lcd_DrawLine(0, 50, 240, 55, WHITE);

	lcdDrawWall();
}

void setUpLcdTimingPlay(uint16_t id, uint16_t timing)
{
	lcd_Clear(WHITE);
	lcd_Fill(0, 0, wallX[1], wallY[0], BLUE);
	lcd_ShowStr(0, 5, " MODE: TIMING", RED, BLUE, 16, 1);

	char str1[50] = "ID: ";
	char *str2 = convert2str(ID);
	strcat(str1, str2);
	lcd_ShowStr(idX, idY, str1, RED, WHITE, 16, 1);

	char str3[50] = "SCORE: ";
	char *str4 = convert2str(0);
	strcat(str3, str4);
	lcd_ShowStr(scoreX, scoreY+5, str3, RED, WHITE, 16, 1);

	showTiming();

	lcd_ShowPicture(logoBKX, logoBKY, logoBKHeight, logoBKWidth, gImage_BKWHITEBG);
//	lcd_DrawLine(0, 50, 240, 55, WHITE);

	lcdDrawWall();
}

void setUpLcdAdvancePlay(uint16_t id, uint16_t timing)
{
	lcd_Clear(WHITE);
	lcd_Fill(0, 0, wallX[1], wallY[0], BLUE);
	lcd_ShowStr(0, 5, " MODE: ADVANCE", RED, BLUE, 16, 1);

	char str1[50] = "ID: ";
	char *str2 = convert2str(ID);
	strcat(str1, str2);
	lcd_ShowStr(idX, idY, str1, RED, WHITE, 16, 1);

	char str3[50] = "SCORE: ";
	char *str4 = convert2str(0);
	strcat(str3, str4);
	lcd_ShowStr(scoreX, scoreY+5, str3, RED, WHITE, 16, 1);

	showTiming();

	lcd_ShowPicture(logoBKX, logoBKY, logoBKHeight, logoBKWidth, gImage_BKWHITEBG);
//	lcd_DrawLine(0, 50, 240, 55, WHITE);

	lcdDrawWall();
}

void printScore()
{
	if(statusGame == NORMALMODE)
	{
		char str3[50] = "SCORE: ";
		char *str4 = convert2str(SCORE);
		strcat(str3, str4);
		lcd_ShowStr(scoreX, scoreY+5, str3, RED, BLUE, 16, 0);
	}
	if(statusGame == TIMINGMODE || statusGame == ADVANCEMODE)
	{
		char str3[50] = "SCORE: ";
		char *str4 = convert2str(SCORE);
		strcat(str3, str4);
		lcd_ShowStr(scoreX, scoreY+5, str3, RED, BLUE, 16, 0);

		showTiming();
	}
}
