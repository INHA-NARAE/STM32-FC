/*
 * Servo.c
 *
 *  Created on: Mar 27, 2025
 *      Author: leecurrent04
 *      Email : leecurrent04@inha.edu
 */


/* Includes ------------------------------------------------------------------*/
#include <FC_Servo/Servo.h>


/* Variables -----------------------------------------------------------------*/
/*
 * 0x[타이머][채널]
 * 타미머 : 1,3-5
 * 채널 : 1-4
 */
const uint8_t SERVO_TIMER_MAP[SERVO_CHANNEL_MAX] = {
		0x42, 0x31, 0x32, 0x44,
		0x51, 0x52, 0x53, 0x54,
		0x33, 0x34, 0x12, 0x14
};


/* Functions -----------------------------------------------------------------*/
/*
 * @brief SERVO 초기화
 * @detail 출력 프로토콜, 주기 변경
 * @parm none
 * @retval none
 */
int SERVO_Initialization(void)
{
	// PARAM_SERVO* servo = &paramServo;

	LL_TIM_EnableCounter(TIM1);
	LL_TIM_EnableCounter(TIM3);
	LL_TIM_EnableCounter(TIM5);

	if(!(LL_TIM_IsEnabledCounter(TIM1) &&
			LL_TIM_IsEnabledCounter(TIM3) &&
			LL_TIM_IsEnabledCounter(TIM4) &&
			LL_TIM_IsEnabledCounter(TIM5)
			)) return -1;

	SERVO_doDisarm();

	return 0;
}


/*
 * @brief 모든 채널 출력 활성화
 * @parm none
 * @retval none
 */
void SERVO_doArm(void)
{
	configurePWM(param.servo.RATE);

	for(uint8_t i=0; i<SERVO_CHANNEL_MAX; i++)
	{
	    // 해당 서보 채널이 활성화되어 있지 않으면 다음으로 건너뜀.
		if(!((param.servo.GPIO_MASK >> i)&0x1)){
			continue;
		}

		doArm2Channel(i+1, 1);
	}

	LL_TIM_GenerateEvent_UPDATE(TIM1);
	LL_TIM_GenerateEvent_UPDATE(TIM5);
	return;
}


/*
 * @brief 모든 출력 비활성화
 * @detail 출력 프로토콜 따라 수행
 * @parm none
 * @retval none
 */
void SERVO_doDisarm(void)
{
	configurePWM(param.servo.RATE);

	for(uint8_t i=0; i<SERVO_CHANNEL_MAX; i++)
	{
		doArm2Channel(i+1, 0);
	}

	LL_TIM_GenerateEvent_UPDATE(TIM1);
	LL_TIM_GenerateEvent_UPDATE(TIM5);
	return;
}

/*
 * @brief SERVO 출력
 * @detail 출력 프로토콜 따라 수행
 * @parm none
 * @retval none
 */
void SERVO_control(void)
{
	calculateServoOutput();

	setPWM();
	return;
}


/*
 * @brief Fail-Safe 동작
 * @retval none
 */
void SERVO_setFailsafe(void)
{
	setPWM2Channel(1, 1000);
	setPWM2Channel(2, 1500);
	setPWM2Channel(3, 1500);
	setPWM2Channel(4, 1500);
	return;
}


/*
 * @brief ESC Calibration
 * @parm uint8_t mode
 * 				0 : high 신호 입력
 * 				1 : low 신호 입력
 * @retval none
 */
void SERVO_doCalibrate(uint8_t mode)
{
	uint8_t channels[] = {1,2,3,4};
	if(mode)
	{
		configurePWM(50);

		doArm2Channels(&channels[0], sizeof(channels), 1);
		setPWM2Channels(&channels[0], sizeof(channels), 2000);
	}
	else
	{
		setPWM2Channels(&channels[0], sizeof(channels), 1000);
		HAL_Delay(1000);
		doArm2Channels(&channels[0], sizeof(channels), 0);
	}
	return;
}

/* Functions -----------------------------------------------------------------*/
/*
 * @brief 특정 채널 출력 모드 설정
 * @parm uint8_t servoCh (in 1-12)
 * @parm uint8_t state
 * 					0 : enable
 * 					1 : disable
 * @retval 0 : 설정됨
 * @retval -1 : ch 범위 오류
 */
int doArm2Channel(uint8_t servoCh, uint8_t state)
{
	if(servoCh<1 || servoCh>12) return -1;
	const TIM_TypeDef* timerArr[] = {
			0, TIM1, 0, TIM3, TIM4, TIM5
	};

	// map에서 상위 비트로 타이머 선택
	TIM_TypeDef* timer = (TIM_TypeDef*)timerArr[SERVO_TIMER_MAP[servoCh-1]>>4];

	// map에서 하위 비트로 채널 선택
	uint32_t ch;
	switch(SERVO_TIMER_MAP[servoCh-1]&0x0F){
	case 1: ch = LL_TIM_CHANNEL_CH1; break;
	case 2: ch = LL_TIM_CHANNEL_CH2; break;
	case 3: ch = LL_TIM_CHANNEL_CH3; break;
	case 4: ch = LL_TIM_CHANNEL_CH4; break;
	default: ch = 0; break;
	}

	if(timer&&ch){
		if(state == 1) LL_TIM_CC_EnableChannel(timer, ch);
		else if(state == 0) LL_TIM_CC_DisableChannel(timer, ch);
	}
	return 0;
}


/*
 * @brief 특정 채널 출력 모드 설정
 * @parm uint8_t* pCh (each in 1-12)
 * @parm uint8_t len : array size
 * @parm uint8_t state
 * 					0 : enable
 * 					1 : disable
 * @retval 0 : 설정됨
 */
int doArm2Channels(uint8_t *pCh, uint8_t len, uint8_t state)
{
	for(uint8_t i=0; i<len; i++)
	{
		uint8_t ch = pCh[i];
		doArm2Channel(ch, state);
	}
	return 0;
}


/*
 * @brief PWM 주기 설정
 * @detail 50-490Hz까지 변경
 * @parm uint16_t hz (in 50-490)
 * @retval 0 : 설정됨
 * @retval 1 : 주파수 범위 오설정
 */
uint8_t configurePWM(uint16_t hz)
{
	if(hz>490 || hz<50) return 1;

	// (추가) PPM 입력이 활성화 되어 있으면 50Hz 고정하도록
	LL_TIM_SetAutoReload(TIM1, 1000000/hz-1);
	LL_TIM_SetAutoReload(TIM3, 1000000/hz-1);
	LL_TIM_SetAutoReload(TIM4, 1000000/hz-1);
	LL_TIM_SetAutoReload(TIM5, 1000000/hz-1);

	LL_TIM_SetPrescaler(TIM1, 168-1);
	LL_TIM_SetPrescaler(TIM3, 84-1);
	LL_TIM_SetPrescaler(TIM4, 84-1);
	LL_TIM_SetPrescaler(TIM5, 84-1);

	LL_TIM_GenerateEvent_UPDATE(TIM1);
	LL_TIM_GenerateEvent_UPDATE(TIM5);

	return 0;
}


/*
 * @brief 출력할 값(CCR) 계산
 * @detail
 * @parm none
 * @retval none
 */
void calculateServoOutput(void)
{
	msg.servo_output_raw.time_usec = msg.system_time.time_boot_ms;

	for(uint8_t i=0; i<SERVO_CHANNEL_MAX; i++)
	{
		// 해당 서보 채널이 활성화되어 있지 않으면 다음으로 건너뜀.
		if(!((param.servo.GPIO_MASK >> i)&0x1)){
			continue;
		}

		msg.servo_output_raw.servo_raw[i] = msg.RC_channels.value[i];
		// servo_output_raw.servo_raw[i] = scaled_imu + RC_channels 를 기반으로 요리조리 계산해서 결정.
	}

	return;
}


/*
 * @brief standard PWM 출력
 * @detail
 * @parm none
 * @retval none
 */
void setPWM(void)
{
	for(uint8_t i=0; i<SERVO_CHANNEL_MAX; i++)
	{
		// 해당 서보 채널이 활성화되어 있지 않으면 다음으로 건너뜀.
		if(!((param.servo.GPIO_MASK >> i)&0x1)){
			continue;
		}
		setPWM2Channel(i+1, msg.servo_output_raw.servo_raw[i]);
	}
	return;
}


/*
 * @brief 특정 서보 채널에 standard PWM 출력
 * @parm uint8_t ch (in 1-12)
 * @parm uint16_t value (in 1000-2000)
 * @retval 0
 */
int setPWM2Channel(uint8_t ch, uint16_t value)
{
	if(ch<1 || ch>12) return -1;
	if(value<800||value>2000) return -2;

	const TIM_TypeDef* timerArr[] = {
		0, TIM1, 0, TIM3, TIM4, TIM5
	};

	// map에서 상위 비트로 타이머 선택
	TIM_TypeDef* timer = (TIM_TypeDef*)timerArr[SERVO_TIMER_MAP[ch-1]>>4];

	// map에서 하위 비트로 채널 선택
	switch(SERVO_TIMER_MAP[ch-1]&0x0F){
	case 1: timer->CCR1 = value; break;
	case 2: timer->CCR2 = value; break;
	case 3: timer->CCR3 = value; break;
	case 4: timer->CCR4 = value; break;
	}

//	LL_TIM_GenerateEvent_UPDATE(TIM5);
	return 0;
}


/*
 * @brief 특정 서보 채널 그룹에 standard PWM 출력
 * @parm uint8_t* pCh (each in 1-12)
 * @parm uint8_t len : array size
 * @parm uint16_t value (in 1000-2000)
 * @retval 0
 */
int setPWM2Channels(uint8_t *pCh, uint8_t len, uint16_t value)
{
	for(uint8_t i=0; i<len; i++)
	{
		uint8_t ch = pCh[i];
		setPWM2Channel(ch, value);
	}
	return 0;
}

