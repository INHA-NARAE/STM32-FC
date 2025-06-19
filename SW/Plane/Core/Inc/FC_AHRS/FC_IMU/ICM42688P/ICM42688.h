/**

 * FC_Gyro/ICM42688.c
 * @author ChrisP @ M-HIVE

 * This library source code has been created for STM32F4. Only supports SPI.
 *
 * Development environment specifics:
 * STM32CubeIDE 1.0.0
 * STM32CubeF4 FW V1.24.1
 * STM32F4 LL Driver(SPI) and HAL Driver(RCC for HAL_Delay() function)
 *
 * Created by ChrisP(Wonyeob Park) @ M-HIVE Embedded Academy, July, 2019
 * Rev. 1.0
 *
 * https://github.com/ChrisWonyeobPark/
 * https://www.udemy.com/course/stm32-drone-programming/?referralCode=E24CB7B1CD9993855D45
 * https://www.inflearn.com/course/stm32cubelde-stm32f4%EB%93%9C%EB%A1%A0-%EA%B0%9C%EB%B0%9C
*/

#ifndef INC_FC_IMU_ICM42688P_ICM42688_H_
#define INC_FC_IMU_ICM42688P_ICM42688_H_


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <GCS_MAVLink/GCS_MAVLink.h>

#include <FC_AHRS/FC_IMU/ICM42688P/driver.h>
#include <FC_AHRS/FC_IMU/ICM42688P/register_map.h>


/* Variables -----------------------------------------------------------------*/
extern int32_t gyro_x_offset, gyro_y_offset, gyro_z_offset;


/* Functions 1 ---------------------------------------------------------------*/
void ICM42688_Get6AxisRawData(void);
void ICM42688_ConvertGyroRaw2Dps(void);
void ICM42688_ConvertAccRaw2G(void);
//int ICM42688_DataReady(void);


/* Functions 2 ---------------------------------------------------------------*/
inline static void CHIP_SELECT(void);
inline static void CHIP_DESELECT(void);
unsigned char SPI1_SendByte(unsigned char data);

uint8_t ICM42688_Readbyte(uint8_t reg_addr);
void ICM42688_Readbytes(unsigned char reg_addr, unsigned char len, unsigned char* data);
void ICM42688_Writebyte(uint8_t reg_addr, uint8_t val);
void ICM42688_Writebytes(unsigned char reg_addr, unsigned char len, unsigned char* data);

#endif
