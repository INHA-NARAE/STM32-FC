/*
 * BMI323.c (Work In Progress!)
 * FC_AHRS/FC_IMU/BMI323/BMI323.c
 *
 *  Created on: June 19, 2025
 *      Author: leecurrent04
 *      Email : leecurrent04@inha.edu
 */

#include <FC_AHRS/FC_IMU/BMI323/BMI323.h>


/* Functions -----------------------------------------------------------------*/
/*
 * @brief 초기 설정
 * @detail SPI 연결 수행, 감도 설정, offset 제거
 * @retval 0 : 완료
 * @retval 1 : 센서 없음
 */
int BMI323_Initialization(void)
{
//	uint8_t who_am_i = 0;
//	int16_t accel_raw_data[3] = {0};  // To remove offset
//	int16_t gyro_raw_data[3] = {0};   // To remove offset
//
//	if(!LL_SPI_IsEnabled(SPI3)){
//		LL_SPI_Enable(SPI3);
//	}
//	CHIP_DESELECT();
//
//	// Check
//	who_am_i = BMI323_Readbyte(WHO_AM_I);
//	if(who_am_i != 0x47)
//	{
//		return 1;
//	}
//
//	// PWR_MGMT0
//	BMI323_Writebyte(PWR_MGMT0, 0x0F); // Temp on, ACC, GYRO LPF Mode
//	HAL_Delay(50);
//
//	// GYRO_CONFIG0
//	BMI323_Writebyte(GYRO_CONFIG0, 0x26); // Gyro sensitivity 1000 dps, 1kHz
//	HAL_Delay(50);
//	BMI323_Writebyte(GYRO_CONFIG1, 0x00); // Gyro temp DLPF 4kHz, UI Filter 1st, 	DEC2_M2 reserved
//	HAL_Delay(50);
//
//	BMI323_Writebyte(ACCEL_CONFIG0, 0x46); // Acc sensitivity 4g, 1kHz
//	HAL_Delay(50);
//	BMI323_Writebyte(ACCEL_CONFIG1, 0x00); // Acc UI Filter 1st, 	DEC2_M2 reserved
//	HAL_Delay(50);
//
//	BMI323_Writebyte(GYRO_ACCEL_CONFIG0, 0x11); // LPF default max(400Hz,ODR)/4
//	HAL_Delay(50);
//
//	// Enable Interrupts when data is ready
////	BMI323_Writebyte(INT_ENABLE, 0x01); // Enable DRDY Interrupt
////	HAL_Delay(50);
//
//
//	// Remove Gyro X offset
//	return 0; //OK
}


/*
 * @brief 데이터 로드
 * @detail 자이로, 가속도 및 온도 데이터 로딩, 물리량 변환
 * @retval 0 : 완료
 */
int BMI323_GetData(void)
{
	BMI323_Get6AxisRawData();

	BMI323_ConvertGyroRaw2Dps();
	BMI323_ConvertAccRaw2G();

	return 0;
}


/* Functions 1 ---------------------------------------------------------------*/
/*
 * @brief 6축 데이터를 레지스터 레벨에서 로딩
 * @retval None
 */
void BMI323_Get6AxisRawData()
{
//	uint8_t data[14];
//
//	BMI323_Readbytes(TEMP_DATA1, 14, data);
//
//	raw_imu.time_usec = system_time.time_unix_usec;
//	raw_imu.temperature = (data[0] << 8) | data[1];
//	raw_imu.xacc = (data[2] << 8) | data[3];
//	raw_imu.yacc = (data[4] << 8) | data[5];
//	raw_imu.zacc = ((data[6] << 8) | data[7]);
//	raw_imu.xgyro = ((data[8] << 8) | data[9]);
//	raw_imu.ygyro = ((data[10] << 8) | data[11]);
//	raw_imu.zgyro = ((data[12] << 8) | data[13]);
//
	return;
}


/*
 * @brief GYRO RAW를 mdps로 변환
 * @detail SCALED_IMU에 저장.
 * 			m degree/s
 * @parm none
 * @retval none
 */
void BMI323_ConvertGyroRaw2Dps(void)
{
//	uint8_t gyro_reg_val = BMI323_Readbyte(GYRO_CONFIG0);
//	uint8_t gyro_fs_sel = (gyro_reg_val >> 5) & 0x07;
//
//	float sensitivity;
//
//	switch (gyro_fs_sel)
//	{
//	case 0: sensitivity = 16.4f; break;       // ±2000 dps
//	case 1: sensitivity = 32.8f; break;       // ±1000 dps
//	case 2: sensitivity = 65.5f; break;       // ±500 dps
//	case 3: sensitivity = 131.0f; break;      // ±250 dps
//	case 4: sensitivity = 262.0f; break;      // ±125 dps
//	case 5: sensitivity = 524.3f; break;      // ±62.5 dps
//	case 6: sensitivity = 1048.6f; break;     // ±31.25 dps
//	case 7: sensitivity = 2097.2f; break;     // ±15.625 dps
//	default: sensitivity = 16.4f; break;      // fallback: ±2000 dps
//	}
//
//	msg.scaled_imu.time_boot_ms = msg.system_time.time_boot_ms;
//
//	// m degree
//	msg.scaled_imu.xgyro = (float)raw_imu.xgyro / sensitivity * 1000;
//	msg.scaled_imu.ygyro = (float)raw_imu.ygyro / sensitivity * 1000;
//	msg.scaled_imu.zgyro = (float)raw_imu.zgyro / sensitivity * 1000;
//
//	return;
}


/*
 * @brief Acc RAW를 mG로 변환
 * @detail SCALED_IMU에 저장.
 * 			mG (Gauss)
 * @parm none
 * @retval none
 */
void BMI323_ConvertAccRaw2G(void)
{
//	uint8_t acc_reg_val = BMI323_Readbyte(ACCEL_CONFIG0);
//	uint8_t acc_fs_sel = (acc_reg_val >> 5) & 0x07;
//
//	float sensitivity;
//
//	switch (acc_fs_sel)
//	{
//	case 0: sensitivity = 2048.0f; break;    // ±16g
//	case 1: sensitivity = 4096.0f; break;    // ±8g
//	case 2: sensitivity = 8192.0f; break;    // ±4g
//	case 3: sensitivity = 16384.0f; break;   // ±2g
//	default: sensitivity = 2048.0f; break;   // fallback: ±16g
//	}
//
//	// mG
//	scaled_imu.xacc = (float)raw_imu.xacc / sensitivity * 1000;
//	scaled_imu.yacc = (float)raw_imu.yacc / sensitivity * 1000;
//	scaled_imu.zacc = (float)raw_imu.zacc / sensitivity * 1000;
//
//	return;
}


/* Functions 2 ---------------------------------------------------------------*/
inline static void CHIP_SELECT(void)
{
//	LL_GPIO_ResetOutputPin(GYRO1_NSS_GPIO_Port, GYRO1_NSS_Pin);
}

inline static void CHIP_DESELECT(void)
{
//	LL_GPIO_SetOutputPin(GYRO1_NSS_GPIO_Port, GYRO1_NSS_Pin);
}


unsigned char SPI3_SendByte(unsigned char data)
{
//	while(LL_SPI_IsActiveFlag_TXE(SPI3)==RESET);
//	LL_SPI_TransmitData8(SPI3, data);
//
//	while(LL_SPI_IsActiveFlag_RXNE(SPI3)==RESET);
//	return LL_SPI_ReceiveData8(SPI3);
}

uint8_t BMI323_Readbyte(uint8_t reg_addr)
{
//	uint8_t val;
//
//	CHIP_SELECT();
//	SPI3_SendByte(reg_addr | 0x80); //Register. MSB 1 is read instruction.
//	val = SPI3_SendByte(0x00); //Send DUMMY to read data
//	CHIP_DESELECT();
//
//	return val;
}

void BMI323_Readbytes(unsigned char reg_addr, unsigned char len, unsigned char* data)
{
//	unsigned int i = 0;
//
//	CHIP_SELECT();
//	SPI3_SendByte(reg_addr | 0x80); //Register. MSB 1 is read instruction.
//	while(i < len)
//	{
//		data[i++] = SPI3_SendByte(0x00); //Send DUMMY to read data
//	}
//	CHIP_DESELECT();
}

void BMI323_Writebyte(uint8_t reg_addr, uint8_t val)
{
//	CHIP_SELECT();
//	SPI3_SendByte(reg_addr & 0x7F); //Register. MSB 0 is write instruction.
//	SPI3_SendByte(val); //Send Data to write
//	CHIP_DESELECT();
}

void BMI323_Writebytes(unsigned char reg_addr, unsigned char len, unsigned char* data)
{
//	unsigned int i = 0;
//	CHIP_SELECT();
//	SPI3_SendByte(reg_addr & 0x7F); //Register. MSB 0 is write instruction.
//	while(i < len)
//	{
//		SPI3_SendByte(data[i++]); //Send Data to write
//	}
//	CHIP_DESELECT();
}


/*
int BMI323_DataReady(void)
{
	return LL_GPIO_IsInputPinSet(BMI323_INT_PORT, BMI323_INT_PIN);
}
*/
