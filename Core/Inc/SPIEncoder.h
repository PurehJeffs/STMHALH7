#ifndef INC_SPIENCODER_H_

#define INC_SPIENCODER_H_
#include "main.h"


typedef struct
{
    SPI_HandleTypeDef *hspi;

    GPIO_TypeDef *cs_port;
    uint16_t cs_pin;

    uint8_t device_count;

    uint16_t *data;

} SPI_Encoder_HandleTypeDef;

HAL_StatusTypeDef Bourns_Encoder_Init(SPI_Encoder_HandleTypeDef *dev, SPI_HandleTypeDef *hspi,
                                   GPIO_TypeDef *cs_port, uint16_t cs_pin, uint8_t device_count);

HAL_StatusTypeDef Bourns_Encoder_ReadAll(SPI_Encoder_HandleTypeDef *dev);

HAL_StatusTypeDef Bourns_Encoder_Read(SPI_Encoder_HandleTypeDef *dev);
#endif /* INC_SPIENCODER_H_ */