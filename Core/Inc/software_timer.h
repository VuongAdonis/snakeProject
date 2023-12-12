/*
 * software_timer.h
 *
 *  Created on: Sep 24, 2023
 *      Author: HaHuyen
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "software_timer.h"

#include "tim.h"
#include "led_7seg.h"

extern uint16_t flagForSnakeRun;
extern uint16_t flagForButton;
extern uint16_t flagForTiming;
extern uint16_t flagForDeTime;
extern uint16_t flagForGenerateWall;
extern uint16_t flagForUart;
extern uint16_t flagForSendSensor;

void timer_init();
void setTimerSnakeRun(uint16_t duration);
void setTimerTiming(uint16_t duration);
void setTimerDeTime(uint16_t duration);
void setTimerButton(uint16_t duration);
void setTimerGenerateWall(uint16_t duration);
void setTimerUart(uint16_t duration);
void setTimerSendSensor(uint16_t duration);

#endif /* INC_SOFTWARE_TIMER_H_ */