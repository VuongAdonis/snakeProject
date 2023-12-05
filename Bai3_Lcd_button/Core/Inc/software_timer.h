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

extern uint16_t flag_timer2;
extern uint16_t fruit_timer_flag;
extern uint16_t fruit_counter;

void timer_init();
void setTimer2(uint16_t duration);

/**
 * Fruit's Timer
 * */
void setFruitTimer(uint16_t duration);
void fruitTimerRun();


#endif /* INC_SOFTWARE_TIMER_H_ */
