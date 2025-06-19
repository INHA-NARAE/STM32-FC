/*
 * register_map.c
 * FC_AHRS/FC_Baro/LPS22HH/register_map.h
 *
 *  Created on: June 7, 2025
 *      Author: leecurrent04
 *      Email : leecurrent04@inha.edu
 */

#ifndef INC_FC_BARO_LPS22HH_REGISTERMAP_H_
#define INC_FC_BARO_LPS22HH_REGISTERMAP_H_


#define INTERRUPT_CFG (0x0B)          // Interrupt register	(R/W)
#define THS_P_L (0x0C)                // Pressure threshold registers	(R/W)
#define THS_P_H (0x0D)                // Pressure threshold registers	(R/W)
#define IF_CTRL (0x0E)                // Interface control register	(R/W)
#define WHO_AM_I (0x0F)               // Who am I	(R)
#define CTRL_REG1 (0x10)              // Control registers	(R/W)
#define CTRL_REG2 (0x11)              // Control registers	(R/W)
#define CTRL_REG3 (0x12)              // Control registers	(R/W)
#define FIFO_CTRL (0x13)              // FIFO configuration register	(R/W)
#define FIFO_WTM (0x14)               // FIFO threshold setting register (R/W)
#define REF_P_L (0x15)                // Reference pressure registers	(R)
#define REF_P_H (0x16)                // Reference pressure registers	(R)
#define RPDS_L (0x18)                 // Pressure offset registers	(R/W)
#define RPDS_H (0x19)                 // Pressure offset registers	(R/W)
#define INT_SOURCE (0x24)             // Interrupt register	(R)
#define FIFO_STATUS1 (0x25)           // FIFO status registers	(R)
#define FIFO_STATUS2 (0x26)           // FIFO status registers	(R)
#define STATUS (0x27)                 // Status register	(R)
#define PRESSURE_OUT_XL (0x28)        // Pressure output registers	(R)
#define PRESSURE_OUT_L (0x29)         // Pressure output registers	(R)
#define PRESSURE_OUT_H (0x2A)         // Pressure output registers	(R)
#define TEMP_OUT_L (0x2B)             // Temperature output registers	(R)
#define TEMP_OUT_H (0x2C)             // Temperature output registers	(R)
#define FIFO_DATA_OUT_PRESS_XL (0x78) // FIFO pressure output registers	(R)
#define FIFO_DATA_OUT_PRESS_L (0x79)  // FIFO pressure output registers	(R)
#define FIFO_DATA_OUT_PRESS_H (0x7A)  // FIFO pressure output registers	(R)
#define FIFO_DATA_OUT_TEMP_L (0x7B)   // FIFO temperature output registers	(R)
#define FIFO_DATA_OUT_TEMP_H (0x7C)   // FIFO temperature output registers	(R)


#endif
