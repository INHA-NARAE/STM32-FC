/*
 * FC_Baro/Baro.h
 *
 *  Created on: June 7, 2025
 *      Author: leecurrent04
 *      Email : leecurrent04@inha.edu
 */

#ifndef INC_FC_BARO_BARO_H_
#define INC_FC_BARO_BARO_H_


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <math.h>

#include <GCS_MAVLink/GCS_MAVLink.h>

#include <FC_AHRS/FC_Baro/driver.h>

#include <FC_AHRS/FC_Baro/LPS22HH/driver.h>


/* Variables -----------------------------------------------------------------*/
extern SCALED_PRESSURE scaled_pressure;


/* Functions -----------------------------------------------------------------*/
int Baro_Initialization(void);
unsigned int Baro_GetData(void);


/* Functions 2 ---------------------------------------------------------------*/
float pascal2meter(float pressure, float temperature);


#endif
