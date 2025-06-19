/*
 * LPS22HH.h
 * FC_AHRS/FC_Baro/LPS22HH/LPS22HH.h
 *
 *  Created on: June 7, 2025
 *      Author: leecurrent04
 *      Email : leecurrent04@inha.edu
 */

#ifndef INC_FC_BARO_LPS22HH_LPS22HH_H_
#define INC_FC_BARO_LPS22HH_LPS22HH_H_


/* Include -------------------------------------------------------------------*/
#include <GCS_MAVLink/GCS_MAVLink.h>

#include <FC_AHRS/FC_Baro/LPS22HH/driver.h>
#include <FC_AHRS/FC_Baro/LPS22HH/register_map.h>


/* Variables -----------------------------------------------------------------*/
float base_pressure;
float base_temperature;


/* Functions 2 ---------------------------------------------------------------*/
int dataReady(void);
void getPressure(int32_t* pressure);
void getTemperature(int16_t* temperature);


/* Functions 3 ---------------------------------------------------------------*/
inline static void CHIP_SELECT(void);
inline static void CHIP_DESELECT(void);
extern unsigned char SPI1_SendByte(unsigned char data);

uint8_t LPS22HH_Readbyte(uint8_t reg_addr);
void LPS22HH_Readbytes(unsigned char reg_addr, unsigned char len, unsigned char* data);

void LPS22HH_Writebyte(uint8_t reg_addr, uint8_t val);
void LPS22HH_Writebytes(unsigned char reg_addr, unsigned char len, unsigned char* data);


#endif
