/*
 * PPM.c
 *
 *  Created on: Apr 5, 2025
 *      Author: leecurrent04
 *      Email : leecurrent04@inha.edu
 */


/* Includes ------------------------------------------------------------------*/
#include <FC_RC/Protocol/PPM.h>


/* Variables -----------------------------------------------------------------*/
/* Functions 1 ---------------------------------------------------------------*/
/*
 * @brief PPM 입력 설정
 * @detail RC_Initialization()에서 실행됨
 * @retval 0 : 정상 수신
 */
int PPM_init(void)
{
	while(PPM_getControlData());
	return 0;
}


/*
 * @brief PPM IRQ2
 * @detail RC_receiveIRQ2에서 호출됨
 * 		GPIO 핀에서 인터럽트가 발생한 시간차(system time)을 기반으로 동작함.
 *
 * @parm timer 데이터 (ms 단위)
 *
 * @retval 0 : 정상 수신
 * @retval 1 : 모든 수신 읽음 (= 첫수신)
 * @retval -1 : 이상 데이터
 */
int PPM_readData(uint16_t data)
{
	static uint16_t previous = 0;
    static uint8_t cnt = 0;
	uint16_t rx = msg.system_time.time_unix_usec - previous;

	previous = msg.system_time.time_unix_usec;

	// 첫 수신
    if(rx>2500){
    	cnt = 0;
    	return 1;
    }
    // 수신값 이상
    else if(rx>2200 || rx<800) return -1;

	((uint16_t*)RC_Buffer)[cnt] = rx;
    cnt++;

	return 0;
}


/*
 * @brief 조종 데이터 로딩
 * @detail RC_GetData()에서 실행됨
 * @retval 0 : 정상 수신
 * @retval -1 : 수신 값 없음
 * @retval -2 : 수신 버퍼가 설정되지 않음
 * @retval 0xf2 : FailSafe
 */
int PPM_getControlData(void)
{
	if(IS_FL_RX == 0) return -1;
	if(RC_isBufferInit() != 0) return -2;

	// flag clear
	CLEAR_FL_RX();

	for(int i=0; i<PPM_MAX_CHANNEL; i++){
		uint16_t value = ((uint16_t*)RC_Buffer)[i];
		RC_MSG_setChannelValue(value, i);
	}

	RC_MSG_setChannelInfo(8, 100);

	return 0;
}
