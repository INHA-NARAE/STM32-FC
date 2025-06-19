/*
 * BMI323.h
 * FC_AHRS/FC_IMU/BMI323/BMI323.h
 *
 *  Created on: June 19, 2025
 *      Author: leecurrent04
 *      Email : leecurrent04@inha.edu
 */

#ifndef INC_FC_AHRS_FC_IMU_BMI323_BMI321_H_
#define INC_FC_AHRS_FC_IMU_BMI323_BMI321_H_


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <GCS_MAVLink/GCS_MAVLink.h>

#include <FC_AHRS/FC_IMU/BMI323/driver.h>
#include <FC_AHRS/FC_IMU/BMI323/register_map.h>


/* Variables -----------------------------------------------------------------*/
extern RAW_IMU raw_imu;
extern SCALED_IMU scaled_imu;

extern int32_t gyro_x_offset, gyro_y_offset, gyro_z_offset;


/* Functions 1 ---------------------------------------------------------------*/
void BMI323_Get6AxisRawData(void);
void BMI323_ConvertGyroRaw2Dps(void);
void BMI323_ConvertAccRaw2G(void);
//int BMI323_DataReady(void);


/* Functions 2 ---------------------------------------------------------------*/
inline static void CHIP_SELECT(void);
inline static void CHIP_DESELECT(void);
unsigned char SPI3_SendByte(unsigned char data);

uint8_t BMI323_Readbyte(uint8_t reg_addr);
void BMI323_Readbytes(unsigned char reg_addr, unsigned char len, unsigned char* data);
void BMI323_Writebyte(uint8_t reg_addr, uint8_t val);
void BMI323_Writebytes(unsigned char reg_addr, unsigned char len, unsigned char* data);


#endif /* INC_FC_AHRS_FC_IMU_BMI323_BMI321_H_ */
