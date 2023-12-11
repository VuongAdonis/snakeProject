/*
 * button.c
 *
 *  Created on: Sep 25, 2023
 *      Author: HaHuyen
 */
#include "button.h"

uint16_t button_count[16];
uint16_t spi_button = 0x0000;
uint16_t buttonForSnake[6];

/**
  * @brief  Init matrix button
  * @param  None
  * @retval None
  */
void button_init(){
	HAL_GPIO_WritePin(BTN_LOAD_GPIO_Port, BTN_LOAD_Pin, 1);
	for (int i= 0; i < 6; i++)
	{
		buttonForSnake[i]= 0;
	}
}

/**
  * @brief  Scan matrix button
  * @param  None
  * @note  	Call every 50ms
  * @retval None
  */
void button_Scan(){
	  HAL_GPIO_WritePin(BTN_LOAD_GPIO_Port, BTN_LOAD_Pin, 0);
	  HAL_GPIO_WritePin(BTN_LOAD_GPIO_Port, BTN_LOAD_Pin, 1);
	  HAL_SPI_Receive(&hspi1, (void*)&spi_button, 2, 10);
	  int button_index = 0;
	  uint16_t mask = 0x8000;
	  for(int i = 0; i < 16; i++){
		  if(i >= 0 && i <= 3){   /// 4 --> 7
			  button_index = i + 4;
		  } else if (i >= 4 && i <= 7){
			  button_index = 7 - i;
		  } else if (i >= 8 && i <= 11){
			  button_index = i + 4;
		  } else {
			  button_index = 23 - i;
		  }
		  if(spi_button & mask) button_count[button_index] = 0;
		  else
	  	  {
				button_count[button_index]++;
				switch (button_index)
				{
				case 5:
					buttonForSnake[0]++;
					break;
				case 8:
					buttonForSnake[1]++;
					break;
				case 9:
					buttonForSnake[2]++;
					break;
				case 10:
					buttonForSnake[3]++;
					break;
				case 12:
					buttonForSnake[4]++;
					break;
				case 13:
					buttonForSnake[5]++;
					break;
				default:
					break;
				}
		  }
		  mask = mask >> 1;
	  }
}



