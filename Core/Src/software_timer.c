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
		// 1ms interrupt here
//		led7_Scan();
	}
}

