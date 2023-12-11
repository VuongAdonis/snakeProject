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
uint32_t timerForTiming = 0;
uint32_t timerForTiming_MUL = 0;

uint16_t flagForDeTime = 0;
uint16_t timerForDeTime = 0;
uint16_t timerForDeTime_MUL = 0;

uint16_t flagForGenerateWall= 0;
uint16_t timerForGenerateWall= 0;
uint16_t timerForGenerateWall_MUL= 0;

uint16_t flagForUart= 0;
uint16_t timerForUart= 0;
uint16_t timerForUart_MUL= 0;

uint16_t flagForSendSensor= 0;
uint16_t timerForSendSensor= 0;
uint16_t timerForSendSensor_MUL= 0;

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
	timerForTiming_MUL =  (uint32_t)duration * 1000/ TIMER_CYCLE_2;
	timerForTiming = timerForTiming_MUL;
	flagForTiming = 0;
}

void setTimerDeTime(uint16_t duration)
{
	timerForDeTime_MUL = duration/ TIMER_CYCLE_2;
	timerForDeTime = timerForDeTime_MUL;
	flagForDeTime = 0;
}

void setTimerGenerateWall(uint16_t duration)
{
	timerForGenerateWall_MUL= duration/ TIMER_CYCLE_2;
	timerForGenerateWall= timerForGenerateWall_MUL;
	flagForGenerateWall= 0;
}

void setTimerUart(uint16_t duration)
{
	timerForUart_MUL= duration/ TIMER_CYCLE_2;
	timerForUart= timerForUart_MUL;
	flagForUart= 0;
}

void setTimerButton(uint16_t duration)
{
	timerForButton_MUL= duration/TIMER_CYCLE_2;
	timerForButton= timerForButton_MUL;
	flagForButton= 0;
}

void setTimerSendSensor(uint16_t duration)
{
	timerForSendSensor_MUL= duration/TIMER_CYCLE_2;
	timerForSendSensor= timerForSendSensor_MUL;
	flagForSendSensor= 0;
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
		if (timerForGenerateWall > 0)
		{
			timerForGenerateWall--;
			if (timerForGenerateWall <= 0)
			{
				flagForGenerateWall= 1;
				timerForGenerateWall= timerForGenerateWall_MUL;
			}
		}
		if (timerForUart > 0)
		{
			timerForUart--;
			if (timerForUart <= 0)
			{
				flagForUart= 1;
				timerForUart= timerForUart_MUL;
			}
		}
		if (timerForSendSensor > 0)
		{
			timerForSendSensor--;
			if (timerForSendSensor <= 0)
			{
				flagForSendSensor= 1;
				timerForSendSensor= timerForSendSensor_MUL;
			}
		}
		// 1ms interrupt here
		led7_Scan();
	}
}

