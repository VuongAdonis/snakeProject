/*
 * software_timer.c
 *
 *  Created on: Sep 24, 2023
 *      Author: HaHuyen
 */

#include "software_timer.h"
#include "snake_game/fruit.h"

#define TIMER_CYCLE_2 1
#define FRUIT_CYCLE 1

//software timer variable
uint16_t flag_timer2 = 0;
uint16_t timer2_counter = 0;
uint16_t timer2_MUL = 0;

//Fruit's timer
uint16_t fruit_timer_flag = 0;
uint16_t fruit_timer_counter = 0;
uint16_t fruit_timer_cycle = 0;
uint16_t fruit_counter = 0;

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
void setTimer2(uint16_t duration){
	timer2_MUL = duration/TIMER_CYCLE_2;
	timer2_counter = timer2_MUL;
	flag_timer2 = 0;
}


/**
 * @brief Set duration for fruit timer
 * @param duration Duration of fruit timer
 * @retval None
 */
void setFruitTimer(uint16_t duration) {
	fruit_timer_cycle = duration/FRUIT_CYCLE;
	fruit_timer_counter = fruit_timer_cycle;
	fruit_timer_flag = 0;
	fruit_counter = 0;
}

/**
 * @brief Timer run logic for fruit timer
 * @param None
 * @retval None
 */
void fruitTimerRun() {
	if (fruit_timer_counter > 0) {
		fruit_timer_counter--;
	} else {
		if (fruit_counter > 400) {
			fruit_counter = 0;
		} else {
			fruit_counter++;
		}
		fruit_timer_flag = 1;
		fruit_timer_counter = fruit_timer_cycle;
	}
}

/**
  * @brief  Timer interrupt routine
  * @param  htim TIM Base handle
  * @note	This callback function is called by system
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		if(timer2_counter > 0){
			timer2_counter--;
			if(timer2_counter == 0) {
				flag_timer2 = 1;
				timer2_counter = timer2_MUL;
			}
		}
		fruitTimerRun();
		// 1ms interrupt here
		led7_Scan();
	}
}

