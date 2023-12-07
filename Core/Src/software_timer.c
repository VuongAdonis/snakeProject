/*
 * software_timer.c
 *
 *  Created on: Sep 24, 2023
 *      Author: HaHuyen
 */

#include "software_timer.h"

#define TIMER_CYCLE_2 1

//software timer variable
uint16_t flagForButton = 0;
uint16_t timerForButton = 0;
uint16_t timerForButton_MUL = 0;

uint16_t flagForSnakeRun= 0;
uint16_t timerForSnakeRun= 0;
uint16_t timerForSnakeRun_MUL= 0;

uint16_t flagForTiming = 0;
uint16_t timerForTiming = 0;
uint16_t timerForTiming_MUL = 0;

uint16_t flagForDeTime = 0;
uint16_t timerForDeTime = 0;
uint16_t timerForDeTime_MUL = 0;

/**
  * @brief  Init timer interrupt
  * @param  None
  * @retval None
  */
void timer_init(){
	HAL_TIM_Base_Start_IT(&htim2);
}


/**
  * @brief  Set duration of software timer interrupt
  * @param  duration Duration of software timer interrupt
  * @retval None
  */
void setTimerSnakeRun(uint16_t duration){
	timerForSnakeRun_MUL= duration/ TIMER_CYCLE_2;
	timerForSnakeRun= timerForSnakeRun_MUL;
	flagForSnakeRun= 0;
}

void setTimerTiming(uint16_t duration)
{
	timerForTiming_MUL = duration/ TIMER_CYCLE_2;
	timerForTiming = timerForTiming_MUL;
	flagForTiming = 0;
}

void setTimerDeTime(uint16_t duration)
{
	timerForDeTime_MUL = duration/ TIMER_CYCLE_2;
	timerForDeTime = timerForDeTime_MUL;
	flagForDeTime = 0;
}

void setTimerButton(uint16_t duration)
{
	timerForButton_MUL= duration/TIMER_CYCLE_2;
	timerForButton= timerForButton_MUL;
	flagForButton= 0;
}

/**
  * @brief  Timer interrupt routine
  * @param  htim TIM Base handle
  * @note	This callback function is called by system
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		if(timerForSnakeRun > 0)
		{
			timerForSnakeRun--;
			if(timerForSnakeRun <= 0) {
				flagForSnakeRun = 1;
				timerForSnakeRun = timerForSnakeRun_MUL;
			}
		}
		if (timerForButton > 0)
		{
			timerForButton--;
			if (timerForButton <= 0)
			{
				flagForButton= 1;
				timerForButton= timerForButton_MUL;
			}
		}
		if(timerForTiming > 0)
		{
			timerForTiming--;
			if(timerForTiming <= 0)
			{
				flagForTiming = 1;
			}
		}
		if(timerForDeTime > 0)
		{
			timerForDeTime--;
			if(timerForDeTime <= 0)
			{
				flagForDeTime = 1;
			}
		}
		// 1ms interrupt here
//		led7_Scan();
	}
}

