/*
 * RadioControl.c
 * Radio 범용 라이브러리
 *
 *  Created on: Mar 10, 2025
 *      Author: leecurrent04
 *      Email : leecurrent04@inha.edu
 *
 */


/* Includes ------------------------------------------------------------------*/
#include <FC_RC/RadioControl.h>


/* Variables -----------------------------------------------------------------*/
uint8_t rxFlag = 0;
uint8_t* RC_Buffer = 0;


/* Functions (driver) --------------------------------------------------------*/
/*
 * @brief RC 초기 설정
 * @detail RC 종류에 따라 메모리 설정
 * 			쓰로틀 체크 및 ESC 캘리브레이션 수행
 */
int RC_Initialization(void)
{
	LL_GPIO_SetOutputPin(LED_RED_GPIO_Port, LED_RED_Pin);

	// 메모리 설정
	for(int i=0; i<8*sizeof(param.rc.PROTOCOLS); i++)
	{
		if(!(param.rc.PROTOCOLS&(0x1<<i))) continue;

		switch(i){
		case PPM:
			RC_Buffer = malloc(PPM_MAX_BUFFER_SIZE*sizeof(uint16_t));
			PPM_init();
			break;
		case SRXL2:
			RC_Buffer = malloc(SRXL_MAX_BUFFER_SIZE*sizeof(uint8_t));
			SRXL2_connect();
			break;
		}

		/*
		 * Enable multiple receiver support
		 */
		if(param.rc.OPTIONS&(0x1<<10)) continue;
		else break;
	}

	// 쓰로틀 체크 & ESC 캘리브레이션
	uint32_t previous_time = msg.system_time.time_boot_ms;
	while(1){
		uint8_t flag_cali =  msg.system_time.time_boot_ms - previous_time > 5000;
		uint8_t retVal = RC_checkThrottle();

		// 쓰로틀이 low 인 경우나 신호가 없는 경우
		if(0 == retVal && 0 == flag_cali) break;
		else if(-2 == retVal) return retVal;

		BuzzerEnableThrottleHigh();

		// calibration 조건(5s 동안 High)를 만족하지 못하면 while
		if(0 == flag_cali) continue;

		// ESC Calibration
		BuzzerDisableThrottleHigh();
		if(RC_enterESCcalibration()==0) break;
	}

	LL_GPIO_ResetOutputPin(LED_RED_GPIO_Port, LED_RED_Pin);

	return 0;
}

/*
 * @brief 조종 데이터 로딩
 * @detail 프로토콜에 따라 다르게 동작
 * @retval 0 : 정상 수신
 * @retval -1 : 수신 버퍼 없음
 * @retval -2 : 조종 데이터가 아님
 */
int RC_GetData(void)
{
	int retVal = 0;

	for(int i=0; i<8*sizeof(param.rc.PROTOCOLS); i++)
	{
		// 모든 프로토콜에 대해 확인하되, 파마리터에서 설정된 것만 받아옴
		if(!((param.rc.PROTOCOLS>>i)&0x1)) continue;

		switch(i){
		case PPM:
			retVal = PPM_getControlData();
			break;
		case SRXL2:
			retVal = SRXL2_getControlData();
			break;
		}

		/*
		 * Enable multiple receiver support
		 */
		if((param.rc.OPTIONS>>10)&0x1) continue;
		else break;
	}

	if(retVal == -1 || retVal ==-2) return retVal;
	if(retVal!=0xf2) fsFlag = 0;

	return 0;
}


/*
 * @brief 쓰로틀 체크
 *
 * @parm None
 * @retval 0 : 쓰로틀 정상
 * @retval -1 : 쓰로틀 비정상
 * @retval -2 : RC 신호 없음
 */
int RC_checkThrottle(void)
{
	uint8_t num = 0;
	while(RC_GetData()){
		if(num++ > 1000) return -2;
	}

	if(msg.RC_channels.value[param.rc.map.THR]>1050) return -1;

	return 0;
}


/* Functions -----------------------------------------------------------------*/
/*
 * @brief 수신 인터럽트 IRQ2
 * @detail
 * 	PPM : data 값은 의미 없음. 수신 인터럽트가 발생한 것을 알리는 목적
 * 	UART : 수신 받은 data 값 (1byte)
 * 		- half_duplex : 모든 수신 패킷을 처리하면 RC_rxFlag를 1로 처리함.
 *
 * @parm uint8_t data : 1byte packet
 *
 * @retval 0 : IRQ2 처리 완료
 * @retval 1 : (half_duplex) 송신 패킷임
 */
int RC_receiveIRQ2(const uint16_t data)
{
	SET_FL_UART_USING();
	// RC_rxFlag.half_using = 1;

	for(int i=0; i<8*sizeof(param.rc.PROTOCOLS); i++)
	{
		if(!((param.rc.PROTOCOLS>>i)&0x1)) continue;

		switch(i){
		case PPM:
			PPM_readData(data);
			SET_FL_RX();
			break;
		case SRXL2:
			// Half-Duplex에서 송신한 패킷을 무시
			if(IS_FL_UART_TX == 1) return 1;

			// 모든 바이트를 읽었는지 검사
			if(SRXL2_readByteIRQ2(data) == 0){
				SET_FL_RX();
				CLEAR_FL_UART_USING();
			}
			break;
		}

		/*
		 * Enable multiple receiver support
		 */
		if((param.rc.OPTIONS>>10)&0x1) continue;
		else break;
	}

	return 0;
}


/*
 * @brief Buffer가 설정 되었는지 확인
 *
 * @parm None
 * @retval 0 : 설정됨
 * @retval -1 : 설정되지 않음
 */
int RC_isBufferInit(void){
	if(RC_Buffer == 0) return -1;
	return 0;
}


/*
 * @brief ESC 캘리브레이션 진입
 * @detail 쓰로틀이 High인 상황이 5초 이상 지속될때 진입
 *
 * @parm None
 * @retval -2 : 조종기 이상
 */
int RC_enterESCcalibration()
{
	while(1)
	{
		uint8_t num = 0;
		while(RC_GetData()){
			if(num++ > 1000) return -2;
		}

		if(msg.RC_channels.value[param.rc.map.THR] > 1800){
			SERVO_doCalibrate(1);
			continue;
		}
		SERVO_doCalibrate(0);
		break;
	}
	return 0;
}

/*
 * @brief Failsafe 모드로 진입
 *
 * @retval 0 : Failsafe 해제됨
 */
int RC_setFailsafe(uint16_t protocol)
{
	// 만약 수신기가 여러 개인 경우, fs를 발동하지 않음.
	if((param.rc.OPTIONS>>10)&0x1) {
		// (추가) 수신기 하나에서 FS 임을 알림
		return 0;
	}

	fsFlag = 1;

	return 0xf2;
}


/*
 * @brief RC 데이터 송신 (Half-Duplex)
 *
 * @parm uint8_t* data : data address
 * @parm uint8_t len : sizeof(data)
 * @retval 0 : 송신 완료.
 * @retval -1 : 송신 실패.
 */
int RC_halfDuplex_Transmit(uint8_t *data, uint8_t len)
{
	if(IS_FL_UART_USING == 1) return -1;

	SET_FL_UART_TX();
	SET_FL_UART_USING();

	for(int i=0; i<len; i++){
		while(!LL_USART_IsActiveFlag_TXE(USART1));
		LL_USART_TransmitData8(USART1, data[i]);
	}

	CLEAR_FL_UART_TX();
	CLEAR_FL_UART_USING();
	return 0;
}


/* Functions 2 ---------------------------------------------------------------*/
/*
 * @brief 입력 값의 범위를 바꾸는 mapping 함수
 * @parm uint16_t x : input
 * @parm uint16_t in_min : x의 최솟값
 * @parm uint16_t in_max : x의 최댓값
 * @parm uint16_t out_min : x의 최솟값
 * @parm uint16_t out_max : x의 최댓값
 * @retVal uint16_t : 변환 값
 */
uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint16_t RC_normalizeChannelValue(){
	return 0;
}

uint16_t RC_applyDeadZoneChannelValue(uint16_t value, uint8_t deadZone){

	if(value > (1500-deadZone) && value < (1500+deadZone)){
		return 1500;
	}

	return value;
}



void setFlag(RC_FLAG i)
{
	rxFlag |= (0x1<<i);
	return;
}

void clearFlag(RC_FLAG i)
{
	rxFlag &= (uint8_t)(~(0x1<<i));
	return;
}


int isFlag(RC_FLAG i)
{
	return (rxFlag>>i)&0x1;
}

