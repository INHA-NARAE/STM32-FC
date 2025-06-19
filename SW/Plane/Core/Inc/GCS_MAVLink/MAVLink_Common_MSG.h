/*
 * MAVLink_Common_MSG.h
 *
 *  Created on: Mar 29, 2025
 *      Author: leecurrent04
 *      Email : leecurrent04@inha.edu
 */

#ifndef INC_GCS_MAVLINK_MAVLINK_COMMON_MSG_H_
#define INC_GCS_MAVLINK_MAVLINK_COMMON_MSG_H_


/*
 * SYSTEM_TIME (2)
 * The system time is the time of the master clock, typically the computer clock of the main onboard computer.
 */
typedef struct __attribute__((packed)){
	uint64_t time_unix_usec;	// Timestamp (UNIX epoch time). (us)
	uint32_t time_boot_ms;		// Timestamp (time since system boot). (ms)
} SYSTEM_TIME;


/*
 * SCALED_IMU (26)
 * The RAW IMU readings for the usual 9DOF sensor setup. This message should contain the scaled values to the described units
 */
typedef struct __attribute__((packed)){
	uint32_t time_boot_ms;		// Timestamp (time since system boot). (ms)
	int16_t xacc;			// X acceleration (mG)
	int16_t yacc;			// Y acceleration (mG)
	int16_t zacc;			// Z acceleration (mG)
	int16_t xgyro;			// Angular speed around X axis (mrad/s)
	int16_t ygyro;			// Angular speed around Y axis (mrad/s)
	int16_t zgyro;			// Angular speed around Z axis (mras/s)
	int16_t xmag;			// X Magnetic field (mgauss)
	int16_t ymag;			// Y Magnetic field (mgauss)
	int16_t zmag;			// Z Magnetic field (mgauss)
	int16_t temperature;	// Temperature, 0: IMU does not provide temperature values. If the IMU is at 0C it must send 1 (0.01C).
} SCALED_IMU;


/*
 * RAW_IMU (27)
 * The RAW IMU readings for a 9DOF sensor, which is identified by the id (default IMU1).
 * This message should always contain the true raw values without any scaling to allow data capture and system debugging.
 */
typedef struct __attribute__((packed)){
	uint64_t time_usec;		// Timestamp (UNIX Epoch time or time since system boot). The receiving end can infer timestamp format (since 1.1.1970 or since system boot) by checking for the magnitude of the number.
	int16_t xacc;			// X acceleration (raw)
	int16_t yacc;			// Y acceleration (raw)
	int16_t zacc;			// Z acceleration (raw)
	int16_t xgyro;			// Angular speed around X axis (raw)
	int16_t ygyro;			// Angular speed around Y axis (raw)
	int16_t zgyro;			// Angular speed around Z axis (raw)
	int16_t xmag;			// X Magnetic field (raw)
	int16_t ymag;			// Y Magnetic field (raw)
	int16_t zmag;			// Z Magnetic field (raw)
	uint8_t id;				// Ids are numbered from 0 and map to IMUs numbered from 1 (e.g. IMU1 will have a message with id=0). Messages with same value are from the same source (instance).
	int16_t temperature;	// Temperature, 0: IMU does not provide temperature values. If the IMU is at 0C it must send 1 (0.01C).
} RAW_IMU;


/*
 * SCALED_PRESSURE (29)
 * The pressure readings for the typical setup of one absolute and differential pressure sensor.
 * The units are as specified in each field.
 */
typedef struct __attribute__((packed)){
	uint32_t time_boot_ms;			// Timestamp (time since system boot). (ms)
	float press_abs;				// Absolute pressure (hPa)
	float press_diff;				// Differential pressure 1 (hPa)
	int16_t temperature;			// Absolute pressure temperature (cdegC)
	int16_t temperature_press_diff;	// Differential pressure temperature (0, if not available). Report values of 0 (or 1) as 1 cdegC. (cdegC)
} SCALED_PRESSURE;


/*
 * SERVO_OUTPUT_RAW (36)
 * Superseded by ACTUATOR_OUTPUT_STATUS.
 * The RAW values of the servo outputs (for RC input from the remote, use the RC_CHANNELS messages).
 * The standard PPM modulation is as follows: 1000 microseconds: 0%, 2000 microseconds: 100%.
*/
typedef struct __attribute__((packed)){
	uint32_t time_usec;		// Timestamp (UNIX Epoch time or time since system boot). The receiving end can infer timestamp format (since 1.1.1970 or since system boot) by checking for the magnitude of the number.
	uint8_t port;			// Servo output port (set of 8 outputs = 1 port). Flight stacks running on Pixhawk should use: 0 = MAIN, 1 = AUX.
	uint16_t servo_raw[16];	// Servo output value
} SERVO_OUTPUT_RAW;


/*
 * RC_CHANNELS (65)
 * The PPM values of the RC channels received.
 * The standard PPM modulation is as follows: 1000 microseconds: 0%, 2000 microseconds: 100%.
 * A value of UINT16_MAX implies the channel is unused.
 * Individual receivers/transmitters might violate this specification.
 */
typedef struct __attribute__((packed)){
	uint32_t time_boot_ms;	// Timestamp (time since system boot).
	uint8_t chancount;		// Total number of RC channels being received. This can be larger than 18, indicating that more channels are available but not given in this message. This value should be 0 when no RC channels are available.
	uint16_t value[18];		// RC channel value.
	uint8_t rssi;			// Receive signal strength indicator in device-dependent units/scale. Values: [0-254], UINT8_MAX: invalid/unknown.
} RC_CHANNELS;


/*
 * SCALED_IMU2 (116)
 * The RAW IMU readings for secondary 9DOF sensor setup. This message should contain the scaled values to the described units
 */
typedef struct __attribute__((packed)){
	uint32_t time_boot_ms;		// Timestamp (time since system boot). (ms)
	int16_t xacc;			// X acceleration (mG)
	int16_t yacc;			// Y acceleration (mG)
	int16_t zacc;			// Z acceleration (mG)
	int16_t xgyro;			// Angular speed around X axis (mrad/s)
	int16_t ygyro;			// Angular speed around Y axis (mrad/s)
	int16_t zgyro;			// Angular speed around Z axis (mras/s)
	int16_t xmag;			// X Magnetic field (mgauss)
	int16_t ymag;			// Y Magnetic field (mgauss)
	int16_t zmag;			// Z Magnetic field (mgauss)
	int16_t temperature;	// Temperature, 0: IMU does not provide temperature values. If the IMU is at 0C it must send 1 (0.01C).
} SCALED_IMU2;


/*
 * ACTUATOR_OUTPUT_STATUS (375)
 * The raw values of the actuator outputs (e.g. on Pixhawk, from MAIN, AUX ports).
 * This message supersedes SERVO_OUTPUT_RAW.
typedef struct __attribute__((packed)){
	uint64_t time_usec;		// Timestamp (since system boot). (us)
	uint32_t active;		// Active outputs
	float actuator[32];		// Servo / motor output array values. Zero values indicate unused channels.
} ACTUATOR_OUTPUT_STATUS;
 */



#endif /* INC_GCS_MAVLINK_MAVLINK_COMMON_MSG_H_ */
