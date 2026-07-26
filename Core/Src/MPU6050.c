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

	 data[0] = 0x01;
	 data[1] = 0x00;

	    status = HAL_I2C_Mem_Write(dev->hi2c,dev->addr,PWR_MGMT_1,I2C_MEMADD_SIZE_8BIT, data,1,HAL_MAX_DELAY);


	    if(status == HAL_OK)
	        printf("MPU6050 Awake\r\n");

	    // AFS_SEL Register 0-2g  1-4g  2-8g 3-16g
	    data[0] = 0b01000;
	    status = HAL_I2C_Mem_Write(dev->hi2c,dev->addr,ACCEL_CONFIG,I2C_MEMADD_SIZE_8BIT, data,1,HAL_MAX_DELAY);
	    if(status != HAL_OK)
	    		    {
	    		        printf("I2C TX Error: %d\r\n", status);
	    		    }
	    //
	    data[0] = 0b01000;
	    status = HAL_I2C_Mem_Write(dev->hi2c,dev->addr,GYRO_CONFIG,I2C_MEMADD_SIZE_8BIT, data,1,HAL_MAX_DELAY);
	    if(status != HAL_OK)
	    	    	{
	    				printf("I2C TX Error: %d\r\n", status);
	    	    	}
};
void MPU6050Config();
void MPU6050ReadGyro();
HAL_StatusTypeDef MPU6050ReadAccelGyro(MPU6050_HandleTypeDef *dev){
		uint8_t data[14];


		HAL_StatusTypeDef status;

		status =HAL_I2C_Mem_Read(dev->hi2c, dev->addr, ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT, data, 14, HAL_MAX_DELAY);

				if(status != HAL_OK)
					{
						printf("I2C TX Error: %d\r\n", status);
					}
				else{
					dev->XACCEL = (int16_t)(((uint16_t)data[0] << 8) | data[1]);
					dev->YACCEL = (int16_t)(((uint16_t)data[2] << 8) | data[3]);
					dev->ZACCEL = (int16_t)(((uint16_t)data[4] << 8) | data[5]);
					dev->XGYRO = (int16_t)(((uint16_t)data[8] << 8) | data[9]);
					dev->YGYRO = (int16_t)(((uint16_t)data[10] << 8) | data[11]);
					dev->ZGYRO = (int16_t)(((uint16_t)data[12] << 8) | data[13]);
								}
				//printf("Za=%f  Ya=%f  Xa=%f  Zg=%f  Yg=%f  Xg=%f \r\n",((dev->ZACCEL)/8192.0f),((dev->YACCEL)/8192.0f),((dev->XACCEL)/8192.0f),
				//														((dev->ZGYRO)/65.5f),((dev->YGYRO)/65.5f),((dev->XGYRO)/65.5f));
//				printf("%02X %02X %02X %02X %02X %02X\r\n",
//				       (unsigned)data[0],
//				       (unsigned)data[1],
//				       (unsigned)data[2],
//				       (unsigned)data[3],
//				       (unsigned)data[4],
//				       (unsigned)data[5]);
				return status;
};
void MPU6050ReadTemp();
