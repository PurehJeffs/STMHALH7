/*
 * AS5600.c
 *
 *  Created on: Jul 9, 2026
 *      Author: ubern
 */
#include "AS5600.h"

HAL_StatusTypeDef AS5600_Init(AS5600_HandleTypeDef *dev, I2C_HandleTypeDef *hi2c, uint8_t addr,
								GPIO_TypeDef *DirPort, uint16_t DirPin, uint8_t HYST){

		HAL_StatusTypeDef status = HAL_OK;
		dev->hi2c = hi2c;
	    dev->addr = addr<<1;
	    dev->DirPort = DirPort;
	    dev->DirPin = DirPin;
	    dev->Hysteresis = HYST;

	    return status;
};

HAL_StatusTypeDef AS5600_Read(AS5600_HandleTypeDef *dev, uint8_t reg, uint16_t *angle){

	HAL_StatusTypeDef status = HAL_OK;
	uint8_t data[2];

	status = HAL_I2C_Mem_Read(dev->hi2c, dev->addr, reg, I2C_MEMADD_SIZE_8BIT, data, 2, HAL_MAX_DELAY);
	if(status != HAL_OK)
	        return status;

	*angle = ((uint16_t)data[0] << 8) | data[1];
	*angle &= 0x0FFF;

	return status;
};

HAL_StatusTypeDef AS5600_Write(AS5600_HandleTypeDef *dev){
	HAL_StatusTypeDef status = HAL_OK;
};

HAL_StatusTypeDef AS5600_Config(AS5600_HandleTypeDef *dev){
	HAL_StatusTypeDef status = HAL_OK;
};

//int AS5600_Status(AS5600_HandleTypeDef *dev, uint8_t reg, uint8_t statReg){
//	HAL_StatusTypeDef status = HAL_OK;
//	uint8_t statusReg;
//	switch(reg){
//	case AS5600_STATUS_MH:
//		if((status = HAL_I2C_Mem_Read(dev->hi2c, dev->addr, AS5600_STATUS, I2C_MEMADD_SIZE_8BIT, &statusReg, 1, HAL_MAX_DELAY))!= HAL_OK){
//			status = HAL_ERROR;
//		}
//		statReg=(statusReg & AS5600_STATUS_MH);
//		return statReg;
//		break;
//	case AS5600_STATUS_ML:
//		break;
//	case AS5600_STATUS_MD:
//		break;
//	default:
//	}
//}
HAL_StatusTypeDef AS5600_Status_MagnetDetect(AS5600_HandleTypeDef *dev, bool *detect){
	HAL_StatusTypeDef status = HAL_OK;
	uint8_t regStatus;
	if((status=HAL_I2C_Mem_Read(dev->hi2c,dev->addr,AS5600_STATUS, I2C_MEMADD_SIZE_8BIT, &regStatus, 1, HAL_MAX_DELAY))!=HAL_OK){
		return status;
	}

	*detect = (regStatus & AS5600_STATUS_MD) != 0;

	return status;
};
//HAL_StatusTypeDef AS5600_Status_MagnetWeak(AS5600_HandleTypeDef *dev, bool *detect){
//	HAL_StatusTypeDef status = HAL_OK;
//	uint8_t regStatus;
//		if((status=HAL_I2C_Mem_Read(dev->hi2c,dev->addr,AS5600_STATUS, I2C_MEMADD_SIZE_8BIT, &regStatus, 1, HAL_MAX_DELAY))!=HAL_OK){
//			return status;
//		}
//		*detect = (regStatus & AS5600_STATUS_ML) != 0;
//
//		return status;
//};
//HAL_StatusTypeDef AS5600_Status_MagnetStrong(AS5600_HandleTypeDef *dev,  bool *detect){
//	HAL_StatusTypeDef status = HAL_OK;
//	uint8_t regStatus;
//		if((status=HAL_I2C_Mem_Read(dev->hi2c,dev->addr,AS5600_STATUS, I2C_MEMADD_SIZE_8BIT, &regStatus, 1, HAL_MAX_DELAY))!=HAL_OK){
//			return status;
//		}
//		*detect = (regStatus & AS5600_STATUS_MH) != 0;
//
//		return status;
//};

