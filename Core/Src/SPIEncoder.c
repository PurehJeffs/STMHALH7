#include "SPIEncoder.h"

HAL_StatusTypeDef Bourns_Encoder_Init(SPI_Encoder_HandleTypeDef *dev, SPI_HandleTypeDef *hspi,
                                   GPIO_TypeDef *cs_port, uint16_t cs_pin, uint8_t device_count)
{
  HAL_StatusTypeDef status = HAL_OK;
  dev->hspi = hspi;
  dev->cs_port = cs_port;
  dev->cs_pin = cs_pin;
  dev->device_count = device_count;
  dev->data = (uint16_t *)malloc(device_count * sizeof(uint16_t));
  if (dev->data == NULL)
  {
    status = HAL_ERROR;
  }
  return status;

}

HAL_StatusTypeDef Bourns_Encoder_ReadAll(SPI_Encoder_HandleTypeDef *dev){
  
  HAL_StatusTypeDef status = HAL_OK;
  uint16_t tx[dev->device_count];
  uint16_t rx[dev->device_count];

  for (uint8_t i = 0; i < dev->device_count; i++)
{
    tx[i] = 0x0000;
    rx[i] = 0x0000;
}

  //uint16_t position[dev->device_count]= {0, 0};
    HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_RESET);
    status = HAL_SPI_TransmitReceive(dev->hspi,(uint8_t *)&tx,
                                     (uint8_t *)&rx,dev->device_count,150);
    if (status != HAL_OK)
    {
      printf("SPI Read Error: %d\r\n", status);
      return status;
    }

    HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);

    dev->data[0] = rx[0] & 0x7FE0;//0xFFE0
    dev->data[1] = rx[1] & 0x3FF0;
    dev->data[0] = (dev->data[0] >> 5);
    dev->data[1] = (dev->data[1] >> 4);

  return status;
};

HAL_StatusTypeDef Bourns_Encoder_Read(SPI_Encoder_HandleTypeDef *dev){
  HAL_StatusTypeDef status = HAL_OK;
  uint16_t tx[1] = {0x0000};
  uint16_t rx[1] = {0};
  //uint16_t position[dev->device_count]= {0, 0};
    HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_RESET);
    status = HAL_SPI_TransmitReceive(dev->hspi,(uint8_t *)&tx,
                                     (uint8_t *)&rx,1,150);
    if (status != HAL_OK)
    {
      printf("SPI Read Error: %d\r\n", status);
      return status;
    }

    HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);
    dev->data[0] = rx[0];
  return status;

}

HAL_StatusTypeDef AS5048A_ReadPosition(SPI_Encoder_HandleTypeDef *dev){
    HAL_StatusTypeDef status = HAL_OK;
    uint16_t tx= 0xFFFF;
    uint16_t rx;
    HAL_GPIO_WritePin(dev->cs_port,
                      dev->cs_pin,
                      GPIO_PIN_RESET);

    status =  HAL_SPI_TransmitReceive(dev->hspi,
                        (uint8_t *)&tx,
                        (uint8_t *)&rx,
                        1,
                        HAL_MAX_DELAY);

    if (status != HAL_OK)
    {
      printf("SPI Read Error: %d\r\n", status);
      return status;
    }  

    HAL_GPIO_WritePin(dev->cs_port,
                      dev->cs_pin,
                      GPIO_PIN_SET);

    dev->position = rx & 0x3FFF;

    return status;
}




/*  old code from main for ems encoder
uint16_t EMS22_2_ReadPosition(void)
{

    uint16_t tx[2] = {0x0000,0x0000};
    uint16_t rx[2] = {0,0};
    HAL_GPIO_WritePin(EMS22_2_CS_GPIO_Port,
                      EMS22_2_CS_Pin,
                      GPIO_PIN_RESET);

    HAL_SPI_TransmitReceive(&hspi4,
                        (uint8_t *)&tx,
                        (uint8_t *)&rx,
                        2,
                        150);
      

    HAL_GPIO_WritePin(EMS22_2_CS_GPIO_Port,
                      EMS22_2_CS_Pin,
                      GPIO_PIN_SET);

      uint16_t position = rx[0] & 0x7FE0;//0xFFE0
      uint16_t position2 = rx[1] & 0x3FF0;
      position = (position >> 5);
      position2 = (position2 >> 4);

    printf("RAW1: 0x%04X Position1: %u RAW2: 0x%04X Position2: %u Binary: ", rx[0], position, rx[1], position2);

    for (int i = 15; i >= 0; i--)
    {
        printf("%d", (rx[0] >> i) & 1);
    }
    for (int i = 15; i >= 0; i--)
    {
        printf("%d", (rx[1] >> i) & 1);
    }
    printf("\r\n");
    return rx[0];
}
*/