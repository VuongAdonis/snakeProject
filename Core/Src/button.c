/*
 * button.c
 *
 *  Created on: Sep 25, 2023
 *      Author: HaHuyen
 */
#include "button.h"
#include "main.h"

uint16_t button_count[16];
uint16_t spi_button = 0x0000;
uint16_t buttonForSnake[6];

/**
  * @brief  Init matrix button
  * @param  None
  * @retval None
  */
void button_init(){
//	HAL_GPIO_WritePin(BTN_LOAD_GPIO_Port, BTN_LOAD_Pin, 1);
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
//	for (int i= 0; i < 16; i++)
//	{
//		button_count[i]= 0;
//	}
	 for (int i= 0; i < 4; i++)
	 {
	 	switch (i)
	 	{
	 		case 0:
	 			HAL_GPIO_WritePin(R0_GPIO_Port, R0_Pin, 0);
	 			HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, 1);
	 			HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, 1);
	 			HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, 1);
	 			if (HAL_GPIO_ReadPin(C0_GPIO_Port, C0_Pin)== 0)
	 				button_count[0]+= 1;
	 			else
	 			{
	 				button_count[0]= 0;
	 				if (HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin)== 0)
	 					button_count[1]+= 1;
	 				else
	 				{
	 					button_count[1]= 0;
	 					if (HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin)== 0)
	 						button_count[2]+= 1;
	 					else
	 					{
	 						button_count[2]= 0;
	 						if (HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin)== 0)
	 							button_count[3]+= 1;
	 						else
	 							button_count[3]= 0;
	 					}
	 				}
	 			}
	 			break;
	 		case 1:
	 			HAL_GPIO_WritePin(R0_GPIO_Port, R0_Pin, 1);
	 			HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, 0);
	 			HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, 1);
	 			HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, 1);
	 			if (HAL_GPIO_ReadPin(C0_GPIO_Port, C0_Pin)== 0)
	 				button_count[4]+= 1;
	 			else
	 			{
	 				button_count[4]= 0;
	 				if (HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin)== 0)
	 				{
	 					button_count[5]+= 1;
	 					buttonForSnake[0]+= 1;
	 				}
	 				else
	 				{
	 					button_count[5]= 0;
	 					if (HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin)== 0)
	 						button_count[6]+= 1;
	 					else
	 					{
	 						button_count[6]= 0;
	 						if (HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin)== 0)
	 							button_count[7]+= 1;
	 						else
	 							button_count[7]= 0;
	 					}
	 				}
	 			}
	 			break;
	 		case 2:
	 			HAL_GPIO_WritePin(R0_GPIO_Port, R0_Pin, 1);
	 			HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, 1);
	 			HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, 0);
	 			HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, 1);
	 			if (HAL_GPIO_ReadPin(C0_GPIO_Port, C0_Pin)== 0)
	 			{
	 				button_count[8]+= 1;
	 				buttonForSnake[1]+= 1;
	 			}
	 			else
	 			{
	 				button_count[8]= 0;
	 				if (HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin)== 0)
	 				{
	 					button_count[9]+= 1;
	 					buttonForSnake[2]+= 1;
	 				}
	 				else
	 				{
	 					button_count[9]= 0;
	 					if (HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin)== 0)
	 					{
	 						button_count[10]+= 1;
	 						buttonForSnake[3]+= 1;
	 					}
	 					else
	 					{
	 						button_count[10]= 0;
	 						if (HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin)== 0)
	 							button_count[11]+= 1;
	 						else
	 							button_count[11]= 0;
	 					}
	 				}
	 			}
	 			break;
	 		case 3:
	 			HAL_GPIO_WritePin(R0_GPIO_Port, R0_Pin, 1);
	 			HAL_GPIO_WritePin(R1_GPIO_Port, R1_Pin, 1);
	 			HAL_GPIO_WritePin(R2_GPIO_Port, R2_Pin, 1);
	 			HAL_GPIO_WritePin(R3_GPIO_Port, R3_Pin, 0);
	 			if (HAL_GPIO_ReadPin(C0_GPIO_Port, C0_Pin)== 0)
	 			{
	 				button_count[12]+= 1;
	 				buttonForSnake[4]+= 1;
	 			}
	 			else
	 			{
	 				button_count[12]= 0;
	 				if (HAL_GPIO_ReadPin(C1_GPIO_Port, C1_Pin)== 0)
	 				{
	 					button_count[13]+= 1;
	 					buttonForSnake[5]+= 1;
	 				}
	 				else
	 				{
	 					button_count[13]= 0;
	 					if (HAL_GPIO_ReadPin(C2_GPIO_Port, C2_Pin)== 0)
						{
	 						button_count[14]+= 1;
							button_init();
						}
	 					else
	 					{
	 						button_count[14]= 0;
	 						if (HAL_GPIO_ReadPin(C3_GPIO_Port, C3_Pin)== 0)
	 							button_count[15]+= 1;
							else
								button_count[15]= 0;
	 					}
	 				}
	 			}
	 			break;
	 		default:
	 			break;
	 	}
	 }
//	  HAL_GPIO_WritePin(BTN_LOAD_GPIO_Port, BTN_LOAD_Pin, 0);
//	  HAL_GPIO_WritePin(BTN_LOAD_GPIO_Port, BTN_LOAD_Pin, 1);
//	  HAL_SPI_Receive(&hspi1, (void*)&spi_button, 2, 10);
//	  int button_index = 0;
//	  uint16_t mask = 0x8000;
//	  for(int i = 0; i < 16; i++){
//		  if(i >= 0 && i <= 3){   /// 4 --> 7
//			  button_index = i + 4;
//		  } else if (i >= 4 && i <= 7){
//			  button_index = 7 - i;
//		  } else if (i >= 8 && i <= 11){
//			  button_index = i + 4;
//		  } else {
//			  button_index = 23 - i;
//		  }
//		  if(spi_button & mask) button_count[button_index] = 0;
//		  else
//	  	  {
//				button_count[button_index]++;
//				switch (button_index)
//				{
//				case 5:
//					buttonForSnake[0]= 1;
//					break;
//				case 8:
//					buttonForSnake[1]= 1;
//					break;
//				case 9:
//					buttonForSnake[2]= 1;
//					break;
//				case 10:
//					buttonForSnake[3]= 1;
//					break;
//				case 12:
//					buttonForSnake[4]= 1;
//					break;
//				case 13:
//					buttonForSnake[5]= 1;
//					break;
//				default:
//					break;
//				}
//		  }
//		  mask = mask >> 1;
//	  }
}



