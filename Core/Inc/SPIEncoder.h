#ifndef INC_SPIENCODER_H_

#define INC_SPIENCODER_H_
#include "main.h"

#define AS5048A_ADDR
#define AS5048A_CFlag 0x0001
#define AS5048A_ProgCtrl 0x0003
#define AS5048A_OTP0PHI 0x0016
#define AS5048A_OTP0PLO 0x0017
#define AS5048A_DiagAGC 0x3FFD
#define AS5048A_Magnitude 0x3FFE
#define AS5048A_Angle 0x3FFF
#define AS5048A_Parity 0x4000
#define AS5048A_NOP 0x0000


typedef struct
{
    SPI_HandleTypeDef *hspi;

    GPIO_TypeDef *cs_port;
    uint16_t cs_pin;

    uint8_t device_count;

    uint16_t *data;
    uint16_t position;
    
} SPI_Encoder_HandleTypeDef;



HAL_StatusTypeDef Bourns_Encoder_Init(SPI_Encoder_HandleTypeDef *dev, SPI_HandleTypeDef *hspi,
                                   GPIO_TypeDef *cs_port, uint16_t cs_pin, uint8_t device_count);

HAL_StatusTypeDef Bourns_Encoder_ReadAll(SPI_Encoder_HandleTypeDef *dev);

HAL_StatusTypeDef Bourns_Encoder_Read(SPI_Encoder_HandleTypeDef *dev);

HAL_StatusTypeDef AS5048A_ReadPosition(SPI_Encoder_HandleTypeDef *dev);
#endif /* INC_SPIENCODER_H_ */