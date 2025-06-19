/*
 * FC_RC/SRXL2.h
 *
 *  Created on: Mar 7, 2025
 *      Author: leecurrent04
 *      Email : leecurrent04@inha.edu
 */

#ifndef INC_FC_RC_SRXL2_H_
#define INC_FC_RC_SRXL2_H_


/* Includes ------------------------------------------------------------------*/
#include <main.h>

#include <FC_Param/Param.h>
#include <GCS_MAVLink/GCS_MAVLink.h>

#include <FC_RC/RadioControl.h>

#include <FC_RC/Protocol/SRXL2/driver.h>
#include <FC_RC/Protocol/SRXL2/spm_srxl.h>
#include <FC_RC/Protocol/SRXL2/SRXL2_type.h>


/* Macro ---------------------------------------------------------------------*/
#define SPEKTRUM_SRXL_ID        (0xA6)
#define SRXL_MAX_DEVICES        (16)

#define SRXL_CTRL_VALUE_MIN 	(10912)
#define SRXL_CTRL_VALUE_MAX 	(54612)


/* Variables -----------------------------------------------------------------*/
extern uint8_t* RC_Buffer;
extern SRXL2_Packet packet;
extern SRXL2_Handshake_Data receiver_info;
extern const uint8_t SRXL_FC_DEVICE_ID;


/* Functions 2 ---------------------------------------------------------------*/
int SRXL2_doHandshake(SRXL2_Handshake_Packet *tx_packet);
int SRXL2_parseControlData(SRXL2_Control_Packet *rx);
int SRXL2_isReceived(void);


/* Functions 3 ---------------------------------------------------------------*/
uint16_t calculate_crc(const uint8_t *data, uint8_t len);
uint16_t insert_crc(uint8_t *data, uint8_t len);
uint8_t countSetBits(uint32_t i);


/* Functions 3 ---------------------------------------------------------------*/
/*
 * In Progress!
 * SRXL_testing.c
 */
int SRXL2_doBind(SRXL2_Bind_Packet* tx_packet);
SRXL2_SignalQuality_Data SRXL2_reqSignalQuality(void);
int SRXL2_SendTelemetryData(void);

#endif /* INC_RC_SRXL2_H_ */
