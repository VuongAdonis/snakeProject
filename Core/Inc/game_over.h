/*
 * gameOver.h
 *
 *  Created on: Dec 5, 2023
 *      Author: Acer
 */

#ifndef INC_GAME_OVER_H_
#define INC_GAME_OVER_H_

#include "main.h"

void showWallnotify();
void eraseFull();
void gameOverUI(uint16_t overVal);
void pickOver(uint16_t overVal);
void initOverMode(uint16_t overVal);

#endif /* INC_GAME_OVER_H_ */
