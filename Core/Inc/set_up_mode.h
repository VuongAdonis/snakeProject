/*
 * set_up_mode.h
 *
 *  Created on: Dec 3, 2023
 *      Author: Acer
 */

#ifndef INC_SET_UP_MODE_H_
#define INC_SET_UP_MODE_H_


char *convert2str(uint16_t val);
void lcdDrawWall();
void setUpLcdNormalPlay(uint16_t id, uint16_t score);
void setUpLcdTimingPlay(uint16_t id, uint16_t timing);
void setUpLcdAdvancePlay(uint16_t id, uint16_t timing);
void printScore();

#endif /* INC_SET_UP_MODE_H_ */
