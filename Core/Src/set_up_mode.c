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

uint8_t wall_size = 10;

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
	lcd_Fill(0, 60, 240, 70 + wall_size, BLACK);
	// LEFT
//	lcd_DrawRectangle(0, 70, wall_size, 320, BLACK);
	lcd_Fill(0, 60, wall_size, 320, BLACK);
	// RIGHT
//	lcd_DrawRectangle(240 - wall_size, 70, 240, 320 - wall_size, BLACK);
	lcd_Fill(240 - wall_size, 60, 240, 320, BLACK);
	// BOTTOM
//	lcd_DrawRectangle(240 - wall_size, 320 - wall_size, 240, 320, BLACK);
	lcd_Fill(0, 320 - wall_size, 240, 320, BLACK);
}

void setUpLcdPlay(uint16_t id)
{
	lcd_Clear(WHITE);
	lcd_Fill(0, 0, 240, 30, BLUE);
	lcd_StrCenter(0, 5, "SNAKE GAME", RED, BLUE, 16, 1);
	char str1[50] = "ID: ";
	char *str2 = convert2str(id);

	strcat(str1, str2);
	lcd_ShowStr(20, 30, str1, WHITE, RED, 24, 0);
	lcd_ShowStr(110, 30, "TIMING: --", WHITE, RED, 24, 0);

//	lcd_DrawLine(0, 50, 240, 55, WHITE);

	lcdDrawWall();

	lcd_StrCenter(0, 60, "Score: 0", RED, BLUE, 16, 1);
}



