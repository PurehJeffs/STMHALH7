/*
 * MPU6050.c
 *
 *  Created on: Jul 12, 2026
 *      Author: ubern
 */
#include "MPU6050.h"

void MPU6050CInit(MPU6050_HandleTypeDef *dev, I2C_HandleTypeDef *hi2c, uint8_t addr){
	uint8_t data[2];
	HAL_StatusTypeDef status;

	dev->hi2c=hi2c;
	dev->addr=addr<<1;

	status =HAL_I2C_Mem_Read(hi2c, dev->addr, WHO_AM_I, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
	if(status != HAL_OK)
		    {
		        printf("I2C TX Error: %d\r\n", status);
		    }
	else{
		printf("MPU Init \r\n");
		printf("MPU ADDR =0x%02X \r\n", data[0]);
		}

}
void MPU6050Config();
void MPU6050ReadGyro();
HAL_StatusTypeDef MPU6050ReadAccel(MPU6050_HandleTypeDef *dev){

}
void MPU6050ReadTemp();
