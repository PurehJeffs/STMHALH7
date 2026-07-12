/*
 * AS5600.h
 *
 *  Created on: Jul 9, 2026
 *      Author: ubern
 */

#ifndef INC_AS5600_H_
#define INC_AS5600_H_
#include "main.h"

#define AS5600_ADDR 0x36

//   Configuration Registers
#define AS5600_ZMCO  0x00
#define AS5600_ZPOS1 0x01
#define AS5600_ZPOS2 0x02
#define AS5600_MPOS1 0x03
#define AS5600_MPOS2 0x04
#define AS5600_MANG1 0x05
#define AS5600_MANG2 0x06
#define AS5600_CONF1 0x07
#define AS5600_CONF2 0x08

//     Output Registers
#define AS5600_RAWANGLE1 0x0C
#define AS5600_RAWANGLE2 0x0D
#define AS5600_ANGLE1 	 0x0E
#define AS5600_ANGLE2 	 0x0F

//       Status Registers
#define AS5600_STATUS 	  0x0B
#define AS5600_AGC 		  0x1A
#define AS5600_MAGNITUDE1 0x1B
#define AS5600_MAGNITUDE2 0x1C

#define AS5600_STATUS_MH 0x08
#define AS5600_STATUS_ML 0x10
#define AS5600_STATUS_MD 0x20
//       Burn Command
#define AS5600_BURN 0xFF

typedef struct
{
    I2C_HandleTypeDef *hi2c;
    uint8_t addr;
    uint8_t reg;
    GPIO_TypeDef *DirPort;
    uint16_t DirPin;
    uint8_t Hysteresis;
    uint16_t angle;

} AS5600_HandleTypeDef;

HAL_StatusTypeDef AS5600_Init(AS5600_HandleTypeDef *dev, I2C_HandleTypeDef *hi2c, uint8_t addr,
								GPIO_TypeDef *DirPort, uint16_t DirPin, uint8_t HYST);

HAL_StatusTypeDef AS5600_Read(AS5600_HandleTypeDef *dev, uint8_t reg, uint16_t *angle);

HAL_StatusTypeDef AS5600_Status_MagnetDetect(AS5600_HandleTypeDef *dev, bool *detect);
#endif /* INC_AS5600_H_ */
