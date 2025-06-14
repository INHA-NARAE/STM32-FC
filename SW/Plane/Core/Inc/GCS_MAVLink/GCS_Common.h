/*
 * GCS_Common.h
 *
 *  Created on: Mar 27, 2025
 *      Author: leecurrent04
 *      Email : leecurrent04@inha.edu
 */

#ifndef INC_GCS_MAVLINK_GCS_COMMON_H_
#define INC_GCS_MAVLINK_GCS_COMMON_H_


/* Includes ------------------------------------------------------------------*/
#include <main.h>

#include <GCS_MAVLink/MAVLink_MSG.h>


/* Variables -----------------------------------------------------------------*/
extern SYSTEM_TIME system_time;
extern SCALED_IMU scaled_imu;
extern RAW_IMU raw_imu;						// 27
extern SCALED_PRESSURE scaled_pressure;		// 29
extern SERVO_OUTPUT_RAW servo_output_raw;
extern RC_CHANNELS RC_channels;



#endif /* INC_GCS_MAVLINK_GCS_COMMON_H_ */
