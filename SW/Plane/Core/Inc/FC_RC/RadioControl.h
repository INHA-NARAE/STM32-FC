/*
 * FC_RC/RadioControl.h
 * Radio 범용 라이브러리
 *
 *  Created on: Mar 10, 2025
 *      Author: leecurrent04
 *      Email : leecurrent04@inha.edu
 */

#ifndef INC_FC_RC_RADIOCONTROL_H_
#define INC_FC_RC_RADIOCONTROL_H_


/* Includes ------------------------------------------------------------------*/
#include <main.h>
#include <stdlib.h>

#include <FC_RC/driver.h>
#include <FC_RC/Protocol/SRXL2/driver.h>
#include <FC_RC/Protocol/PPM.h>

#include <FC_Param/Param.h>
#include <GCS_MAVLink/GCS_MAVLink.h>

#include <FC_Basic/Buzzer/driver.h>
#include <FC_Servo/driver.h>
#include <FC_Failsafe/Failsafe.h>


/* Variables -----------------------------------------------------------------*/
extern uint8_t* RC_Buffer;

typedef enum {
	RX = 0,
	UART_TX = 1,
	UART_USING = 2,
} RC_FLAG;

enum RC_PARM_PROTOCOL{
	All 	 = 0,
	PPM 	 = 1,
	IBUS 	 = 2,
	SBUS 	 = 3,
	SBUS_NI  = 4,
	DSM 	 = 5,
	SUMD 	 = 6,
	SRXL 	 = 7,
	SRXL2 	 = 8,
	CRSF 	 = 9 ,
	ST24 	 = 10,
	FPORT	 = 11,
	FPORT2 	 = 12,
	FastSBUS = 13,
	DroneCAN = 14,
	Ghost	 = 15,
	MAVRadio = 16,
};


/* Functions 1 ---------------------------------------------------------------*/
int RC_receiveIRQ2(const uint16_t data);
int RC_isBufferInit(void);

int RC_enterESCcalibration();
int RC_setFailsafe(uint16_t protocol);

int RC_halfDuplex_Transmit(uint8_t *data, uint8_t len);


/* Functions 2 ---------------------------------------------------------------*/
uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max);

uint16_t RC_MSG_setChannelInfo(uint8_t chancout, uint8_t rssi);
uint16_t RC_MSG_setChannelValue(uint16_t value, uint8_t index);

uint16_t RC_applyChannelNormMinMax(uint16_t value, uint16_t min, uint16_t max);
uint16_t RC_applyChannelReverse(uint16_t value, uint8_t shouldInvert);
uint16_t RC_applyChannelDeadZone(uint16_t value, uint8_t deadZone);


/* Functions 3 ---------------------------------------------------------------*/
void setFlag(RC_FLAG i);
void clearFlag(RC_FLAG i);
int isFlag(RC_FLAG i);

#define SET_FL_RX() setFlag(RX)
#define SET_FL_UART_TX() setFlag(UART_TX)
#define SET_FL_UART_USING() setFlag(UART_USING)
#define CLEAR_FL_RX() clearFlag(RX)
#define CLEAR_FL_UART_TX() clearFlag(UART_TX)
#define CLEAR_FL_UART_USING() clearFlag(UART_USING)
#define IS_FL_RX isFlag(RX)
#define IS_FL_UART_TX isFlag(UART_TX)
#define IS_FL_UART_USING isFlag(UART_USING)


#endif /* INC_FC_RC_RADIOCONTROL_H_ */
