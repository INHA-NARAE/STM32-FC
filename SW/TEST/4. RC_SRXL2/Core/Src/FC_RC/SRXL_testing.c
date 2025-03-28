/*
 * SRXL_testing.c
 * 우선 순위가 낮으면서 테스트 중인 코드
 *
 *  Created on: Mar 7, 2025
 *      Author: leecurrent04
 *      Email : leecurrent04@inha.edu
 */

#include <FC_RC/SRXL2.h>


/*
 * 장치간 Handshake 동작 수행
 * Bus내 연결된 장치 정보 알림
 *
 * @parm SRXL2_Handshake_Packet *packet
 * @retval 0 : 송신 완료
 * @retval -1 : 송신 실패
 */
SRXL2_SignalQuality_Data SRXL2_reqSignalQuality()
{
	SRXL2_SignalQuality_Data *rx_data;
	SRXL2_SignalQuality_Data data;

	uint8_t tx_packet[10] ={
			SPEKTRUM_SRXL_ID,
			SRXL_RSSI_ID,
			0x0a,
			SRXL_RSSI_REQ_REQUEST,
			0x12, 0x34, 0x56, 0x78, 		// Antenna A,B,L,R
			0x00, 0x00						// CRC.
	};

	insert_crc(tx_packet, sizeof(tx_packet));

	while(RC_halfDuplex_Transmit(tx_packet, sizeof(tx_packet)));
	for(uint8_t i=0; i<10; i++)
	{

		SRXL2_GetData();
		if(packet.header.pType == SRXL_RSSI_REQ_SEND)
		{
			rx_data = &((SRXL2_SignalQuality_Packet*)SRXL2_data)->data;
			data.Request = rx_data->Request;
			data.AntennaA = rx_data->AntennaA;
			data.AntennaB = rx_data->AntennaB;
			data.AntennaL = rx_data->AntennaL;
			data.AntennaR = rx_data->AntennaR;

			break;
		}

	}
	return data;
}


/*
 * (@ In Progress)
 * 수신기에서 Control 패킷에 ReplyID를 전송함.
 * ReplyID가 Handshake에서 등록한 ID와 같다면 데이터 전송
 * 통신 규칙에 따라 응답 요구 후 바로 답해야 함.
 * 그러나 위 규칙이 지켜지지 않음.
 *  0 : 전송 성공
 * -1 : 전송 실패
 */
int SRXL2_SendTelemetryData(void)
{
	SRXL2_Control_Packet* rx_packet;
	rx_packet = (SRXL2_Control_Packet *)SRXL2_data;

	if(rx_packet->ReplyID != SRXL_FC_DEVICE_ID)
	{
		return -1;
	}

	LL_GPIO_SetOutputPin(LED_DEBUG2_GPIO_Port, LED_DEBUG2_Pin);
	uint8_t telm_packet[22] =
	{
		SPEKTRUM_SRXL_ID,
		SRXL_TELEM_ID,
		22,
		receiver_info.SrcID,	// DeviceID (Receiver)
		0x50,					// source id
		0x30,					// secondary id
		0x00, 0x00,				// int16 field1
		0x00, 0xa0,				// int16 field2
		0x00, 0x00,				// int16 field3
		0x00, 0xa0,				// uint16 field1
		0x00, 0x00,				// uint16 field2
		0x00, 0x00,				// uint16 field3
		0x00, 0x00,				// uint16 field4
		0x00, 0x00   			// CRC 자리 (계산 후 입력)
	};
	insert_crc(telm_packet, sizeof(telm_packet));


	RC_halfDuplex_Transmit(telm_packet, sizeof(telm_packet));
	LL_GPIO_ResetOutputPin(LED_DEBUG2_GPIO_Port, LED_DEBUG2_Pin);
	return 0;
}
