/*
 * FC_IMU/driver_IMU.h
 *
 *  Created on: May 1, 2025
 *      Author: leecurrent04
 *      Email : leecurrent04@inha.edu
 */

#ifndef INC_FC_IMU_IMU_H_
#define INC_FC_IMU_IMU_H_


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <GCS_MAVLink/GCS_MAVLink.h>

#include <FC_AHRS/FC_IMU/driver.h>

#include <FC_AHRS/FC_IMU/ICM42688P/driver.h>


/* Variables -----------------------------------------------------------------*/
extern SCALED_IMU scaled_imu;
extern RAW_IMU raw_imu;


/* Functions -----------------------------------------------------------------*/
void KalmanFilter(void);
void ComplementaryFilter(void);


#endif /* INC_FC_IMU_IMU_H_ */
