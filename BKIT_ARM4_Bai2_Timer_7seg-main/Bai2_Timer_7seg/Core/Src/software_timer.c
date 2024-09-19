/*
 * software_timer.c
 *
 *  Created on: Sep 24, 2023
 *      Author: HaHuyen
 */

#include "software_timer.h"

#define TIMER_CYCLE_2 1
#define FREQ_1 500
#define FREQ_2 20
#define FREQ_3 5

//software timer variable
uint16_t flag_timer2 = 0;
uint16_t timer2_counter = 0;
uint16_t timer2_MUL = 0;
uint16_t counter = 0;


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
		// 0.5ms interrupt here
		// 1Hz
		counter = (counter + 1) % FREQ_1;
		if(counter == 0){
			led7_Scan();
		}

	}
}

