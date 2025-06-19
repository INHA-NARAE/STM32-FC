/*
 * Log.h
 *
 *  Created on: Mar 23, 2025
 *      Author: leecurrent04
 *      Email : leecurrent04@inha.edu
 */

#ifndef INC_FC_LOG_LOG_H_
#define INC_FC_LOG_LOG_H_


/* Includes ------------------------------------------------------------------*/
#include <main.h>
#include <stdlib.h>
#include <string.h>

#include <GCS_MAVLink/GCS_MAVLink.h>


/* Variables -----------------------------------------------------------------*/
extern const uint8_t code;
extern uint16_t logType;


/* Functions -----------------------------------------------------------------*/
int Log_Send();
int Log_transmit(uint8_t* p, uint8_t len);


/* Macros --------------------------------------------------------------------*/
#define LOG_TRANSMIT(x) Log_transmit((uint8_t*)&(x), sizeof(x))


#endif /* INC_FC_LOG_LOG_H_ */
