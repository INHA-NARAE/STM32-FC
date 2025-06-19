/*
 * LPS22HH/LPS22HH.c
 *
 *  Created on: June 7, 2025
 *      Author: leecurrent04
 *      Email : leecurrent04@inha.edu
 */


/* Includes ------------------------------------------------------------------*/
#include <FC_AHRS/FC_Baro/LPS22HH/LPS22HH.h>


/* Functions -----------------------------------------------------------------*/
/*
 * @brief 초기 설정
 * @detail Baro 1 - LPS22H
 * @parm none
 * @retval 0
 */
int LPS22HH_Initialization(void)
{
	uint8_t temp_reg;

	if(!LL_SPI_IsEnabled(SPI1)){
		LL_SPI_Enable(SPI1);
	}
	CHIP_DESELECT();

	// check device
	for(int i=0; i<5; i++)
	{
		if(LPS22HH_Readbyte(WHO_AM_I) == 0xb3) break;
		if(i>=5) return 1;
	}

	// Software Reset LPS22HH
	temp_reg = LPS22HH_Readbyte(CTRL_REG2);
	temp_reg = temp_reg | 0x04;
	LPS22HH_Writebyte(CTRL_REG2, temp_reg);
	while((LPS22HH_Readbyte(CTRL_REG2)&0x04)!=0x00){
	}

	// Set Output Data Rate
	//0x00: One Shot
	//0x10: 1Hz	0x20: 10Hz	0x30: 25Hz	0x40: 50Hz
	//0x50: 75Hz	0x60: 100Hz	0x70: 200Hz
	temp_reg = LPS22HH_Readbyte(CTRL_REG1);
	temp_reg = temp_reg | 0x40;
	LPS22HH_Writebyte(CTRL_REG1, temp_reg);

	// Enable LPF, Cut-off frequency
	//0x08: ODR/9	0x0c: ODR/20
	temp_reg = LPS22HH_Readbyte(CTRL_REG1);
	temp_reg = temp_reg | 0x0c;
	LPS22HH_Writebyte(CTRL_REG1, temp_reg);

	// Enable Block Data Update
	temp_reg = LPS22HH_Readbyte(CTRL_REG1);
	temp_reg = temp_reg | 0x02;
	LPS22HH_Writebyte(CTRL_REG1, temp_reg);

	// Enable Low Noise Mode (ODR should be lower than 100Hz. This is igonored when ODR = 100Hz or 200Hz)
	temp_reg = LPS22HH_Readbyte(CTRL_REG2);
	temp_reg = temp_reg | 0x02;
	LPS22HH_Writebyte(CTRL_REG2, temp_reg);

	// Enable Data-ready signal on INT-DRDY pin
	temp_reg = LPS22HH_Readbyte(CTRL_REG3);
	temp_reg = temp_reg | 0x04;
	LPS22HH_Writebyte(CTRL_REG3, temp_reg);

	return 0;
}

/*
 * @brief 데이터 로드
 * @detail Baro 1 - LPS22H
 * @detail 데이터 로딩, 물리량 변환
 * @retval 0 : 완료
 */
int LPS22HH_GetData(void)
{
	if(dataReady() != 1) return -1;

	int32_t pressure = 0;
	int16_t temp = 0;

	getPressure(&pressure);
	getTemperature(&temp);

	msg.scaled_pressure.time_boot_ms = msg.system_time.time_boot_ms;
	msg.scaled_pressure.press_abs = (float)(pressure/4096.f);
	msg.scaled_pressure.press_diff = msg.scaled_pressure.press_abs - base_pressure;
	msg.scaled_pressure.temperature = (int16_t)(temp/100.f);
	msg.scaled_pressure.temperature_press_diff = 0;
	return 0;
}


/* Functions 2 ---------------------------------------------------------------*/
/*
 * @brief 센서 데이터 갱신 여부
 * @detail Baro 1 - LPS22H
 * @retval 1 : 갱신 됨
 * @retval 0 : 갱신 안됨
 */
int dataReady(void)
{
	return LL_GPIO_IsInputPinSet(BARO_INT_GPIO_Port, BARO_INT_Pin);
}

void getPressure(int32_t* pressure)
{
	LPS22HH_Readbytes(PRESSURE_OUT_XL, 3, (unsigned char*)pressure);
}

void getTemperature(int16_t* temperature)
{
	LPS22HH_Readbytes(TEMP_OUT_L, 2, (unsigned char*)temperature);
}



/* Functions 3 ---------------------------------------------------------------*/
inline static void CHIP_SELECT(void)
{
	LL_GPIO_ResetOutputPin(BARO_NSS_GPIO_Port, BARO_NSS_Pin);
}

inline static void CHIP_DESELECT(void)
{
	LL_GPIO_SetOutputPin(BARO_NSS_GPIO_Port, BARO_NSS_Pin);
}

uint8_t LPS22HH_Readbyte(uint8_t reg_addr)
{
	uint8_t val;

	CHIP_SELECT();
	SPI1_SendByte(reg_addr | 0x80); //Register. MSB 1 is read instruction.
	val = SPI1_SendByte(0x00); //Send DUMMY
	CHIP_DESELECT();

	return val;
}

void LPS22HH_Readbytes(unsigned char reg_addr, unsigned char len, unsigned char* data)
{
	unsigned int i = 0;

	CHIP_SELECT();
	SPI1_SendByte(reg_addr | 0x80); //Register. MSB 1 is read instruction.
	while(i < len)
	{
		data[i++] = SPI1_SendByte(0x00); //Send DUMMY
	}
	CHIP_DESELECT();
}

void LPS22HH_Writebyte(uint8_t reg_addr, uint8_t val)
{
	CHIP_SELECT();
	SPI1_SendByte(reg_addr & 0x7F); //Register. MSB 0 is write instruction.
	SPI1_SendByte(val); //Data
	CHIP_DESELECT();
}

void LPS22HH_Writebytes(unsigned char reg_addr, unsigned char len, unsigned char* data)
{
	unsigned int i = 0;
	CHIP_SELECT();
	SPI1_SendByte(reg_addr & 0x7F); //Register. MSB 0 is write instruction.
	while(i < len)
	{
		SPI1_SendByte(data[i++]); //Data
	}
	CHIP_DESELECT();
}


