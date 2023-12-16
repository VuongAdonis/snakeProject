/*
 * initUI.c
 *
 *  Created on: Dec 12, 2023
 *      Author: Acer
 */

#include "advanceModeUI.h"
#include "global.h"
#include "picture.h"
#include "lcd.h"
#include "button.h"


void runInit()
{
	lcd_ShowPicture(75, 10, 94, 120, gImage_logoTeam);
	lcd_ShowStr(40, 130, "THESIS DESIGN PROJECT", WHITE, BLACK, 16, 0);

	lcd_ShowStr(100, 160, "GVHD:", WHITE, BLACK, 16, 0);
	lcd_ShowStr(70, 180, "Vu Trong Thien", WHITE, BLACK, 16, 0);

	lcd_ShowStr(20, 200, "FULL NAME", WHITE, BLACK, 16, 0);
	lcd_ShowStr(190, 200, "ID", WHITE, BLACK, 16, 0);

	lcd_ShowStr(20, 220, "N.H.Vuong", WHITE, BLACK, 16, 0);
	lcd_ShowStr(170, 220, "2112677", WHITE, BLACK, 16, 0);

	lcd_ShowStr(20, 240, "T.V.Binh", WHITE, BLACK, 16, 0);
	lcd_ShowStr(170, 240, "2112909", WHITE, BLACK, 16, 0);

	lcd_ShowStr(20, 260, "D.N.An", WHITE, BLACK, 16, 0);
	lcd_ShowStr(170, 260, "2112726", WHITE, BLACK, 16, 0);

	lcd_ShowStr(20, 280, "B.N.T.Luan", WHITE, BLACK, 16, 0);
	lcd_ShowStr(170, 280, "2111700", WHITE, BLACK, 16, 0);

}
