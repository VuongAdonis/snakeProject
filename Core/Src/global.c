/*
 * global.c
 *
 *  Created on: Dec 3, 2023
 *      Author: Acer
 */


#include "global.h"
#include "main.h"

uint16_t ID = 0;
uint16_t TIMING = NOTIMING;
uint16_t SCORE = 0;

int arrowX1 = ARROWX1;
int arrowX2 = ARROWX2;
int arrowY1 = ARROWNORMALY1;
int arrowY2 = ARROWNORMALY2;
int arrowMode = NORMALMODE;

int wallX[4] = {0, 240, 0, 240};
int wallY[4] = {60, 60, 320, 320};
int wallSize = 5;

int overWallX[4] = {70, 170, 70, 170};
int overWallY[4] = {130, 130, 250, 250};
int arrowOverMode = NEWGAME;

int arrowStopMode = RESUME;

// 0 = Down, 1 = Up;
int flagUpDOwn = 0;
int flagChange = 0;

int idX = 5;
int idY = 5;
int timingX = 5;
int timingY = 45;
int scoreX = 5;
int scoreY = 25;
int logoBKX = 150;
int logoBKY = 10;
int logoBKHeight = 39;
int logoBKWidth = 40;

int upper[2] = {5, 65};
int lower[2] = {234, 314};

int statusGame = 0;



