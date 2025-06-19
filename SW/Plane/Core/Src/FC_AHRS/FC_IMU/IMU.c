/*
 * IMU.c
 *
 *  Created on: April 30, 2025
 *      Author: leecurrent04
 *      Email : leecurrent04@inha.edu
 */


/* Includes ------------------------------------------------------------------*/
#include <FC_AHRS/FC_IMU/IMU.h>
#include <GCS_MAVLink/GCS_MAVLink.h>


/* Functions -----------------------------------------------------------------*/
/*
 * @brief IMU 초기화
 * @detail IMU 1 - ICM42688P : GYRO, ACC, TEMP
 * @parm none
 * @retval 0
 */
int IMU_Initialization(void)
{
	LL_GPIO_SetOutputPin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);

	ICM42688_Initialization();

	LL_GPIO_ResetOutputPin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);
	return 0;
}


/*
 * @brief 데이터 로딩
 * @detail SCALED_IMU(2,3)에 저장
 * @parm none
 * @retval none
 */
unsigned int IMU_GetData(void)
{

	// SCALED_IMU
	ICM42688_GetData();

	// SCALED_IMU2
	// SCALED_IMU3

//	ComplementaryFilter();
//	KalmanFilter();

	return 0;
}


/* Functions -----------------------------------------------------------------*/
void KalmanFilter(void)
{
	return;
}


void ComplementaryFilter(void)
{
	return;
}
