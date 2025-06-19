/*
 * FC_Basic/Buzzer/Buzzer.h
 *
 *  Created on: Feb 26, 2025
 *      Author: leecurrent04
 *      Email : leecurrent04@inha.edu
 */

#include "main.h"
#include <FC_Basic/Buzzer/Buzzer.h>

#include <GCS_MAVLink/GCS_MAVLink.h>


/* Functions -----------------------------------------------------------------*/
/*
 * @brief 초기 알림
 * @detail 기본 점검 전 알림
 * @retval None
 */
void BuzzerPlayInit(void)
{
	TIM4->ARR = 21;
	TIM4->CCR3 = TIM4->ARR/2;

	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH3);
	TIM4->PSC = 2000;
	HAL_Delay(100);
	TIM4->PSC = 1500;
	HAL_Delay(100);
	TIM4->PSC = 1000;
	HAL_Delay(100);

	LL_TIM_CC_DisableChannel(TIM4, LL_TIM_CHANNEL_CH3);
	return;
}


/*
 * @brief 점검 완료 알림
 * @retval None
 */
void BuzzerPlayOneCycle(void)
{
	for (int i=0; i<8; i++){
		playNote(i, 150);
	}
	return;
}


/* Functions (RC Alarm) ------------------------------------------------------*/
void BuzzerEnableThrottleHigh(void)
{
	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH3);
	TIM4->ARR = 21;
	TIM4->CCR3 = TIM4->ARR/2;
	TIM4->PSC = 2000;

	return;
}

void BuzzerDisableThrottleHigh(void)
{
	LL_TIM_CC_DisableChannel(TIM4, LL_TIM_CHANNEL_CH3);
	return;
}


/* Functions 3 ----------------------------------------------------------------*/
void playNote(Note note, uint16_t time)
{
	TIM4->PSC = 4;
	TIM4->ARR = APB1_CLOCKS/(TIM4->PSC)/tones[note];
	TIM4->CCR3 = TIM4->ARR/2;

	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH3);

	HAL_Delay(time);
	LL_TIM_CC_DisableChannel(TIM4, LL_TIM_CHANNEL_CH3);
	return;
}
