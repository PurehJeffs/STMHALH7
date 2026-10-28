#include "VL6180X.h"

static const uint8_t ContToggle = 0x03;
static const uint8_t SingToggle = 0x01;
static const uint8_t ClearInt = 0x07;

static const VL6180X_RegisterConfig_t private_settings[] =
{
    {0x0207, 0x01}, {0x0208, 0x01},
    {0x0096, 0x00}, {0x0097, 0xFD},
    {0x00E3, 0x01}, {0x00E4, 0x03},
    {0x00E5, 0x02}, {0x00E6, 0x01},
    {0x00E7, 0x03}, {0x00F5, 0x02},
    {0x00D9, 0x05}, {0x00DB, 0xCE},
    {0x00DC, 0x03}, {0x00DD, 0xF8},
    {0x009F, 0x00}, {0x00A3, 0x3C},
    {0x00B7, 0x00}, {0x00BB, 0x3C},
    {0x00B2, 0x09}, {0x00CA, 0x09},
    {0x0198, 0x01}, {0x01B0, 0x17},
    {0x01AD, 0x00}, {0x00FF, 0x05},
    {0x0100, 0x05}, {0x0199, 0x05},
    {0x01A6, 0x1B}, {0x01AC, 0x3E},
    {0x01A7, 0x1F}, {0x0030, 0x00},
    {0x0011, 0x10}, // Enable polling for new sample ready
    {0x010A, 0x30}, // Set averaging sample period
    {0x003F, 0x46}, // Set light and dark gain
    {0x0031, 0xFF}, // Set range measurements before auto calibration
    {0x0040, 0x63}, // Set ALS integration time to 100 ms
    {0x002E, 0x01}, // Perform single temperature calibration
    {0x0014, 0x24}
};


HAL_StatusTypeDef VL6180X_Poll(VL6180X_HandleTypeDef *dev){
    
  HAL_StatusTypeDef status = HAL_OK;
  uint16_t result = 0x00;
  // initial read to get the interrupt status
  status = HAL_I2C_Mem_Read(dev->hi2c, dev->addr, VL6180X_REG_RESULT_INTERRUPT_STATUS,
                                       I2C_MEMADD_SIZE_16BIT, (uint8_t *)&result, 1, 10);
  if(status != HAL_OK)
       return status;  

  result = result & 0x07;  

  // loop until the interrupt status indicates that the measurement is complete
  while(result != 0x04){
    
    status = HAL_I2C_Mem_Read(dev->hi2c, dev->addr, VL6180X_REG_RESULT_INTERRUPT_STATUS,
                                       I2C_MEMADD_SIZE_16BIT, (uint8_t *)&result, 1, 10);
    if(status != HAL_OK)
       return status;

    result = result & 0x07;

    } 
  
  return status;
}                              


HAL_StatusTypeDef VL6180X_Init(VL6180X_HandleTypeDef *dev){

  	HAL_StatusTypeDef status = HAL_OK;
    uint8_t fresh = 0;
    uint16_t data[2];
    data[1]= 0x00;
    data[0]= 0x00;

    // HAL_StatusTypeDef s1 = HAL_I2C_Mem_Read(dev->hi2c, dev->addr,
    //         VL6180X_REG_IDENTIFICATION_MODEL_ID, I2C_MEMADD_SIZE_16BIT, &id, 1, 10);
    status = HAL_I2C_Mem_Read(dev->hi2c, dev->addr,VL6180X_REG_SYSTEM_FRESH_OUT_OF_RESET,
             I2C_MEMADD_SIZE_16BIT, &fresh, 1, 10);

    if(status != HAL_OK)
       return status;

    status = HAL_I2C_Mem_Read(dev->hi2c, dev->addr, VL6180X_REG_SYSTEM_FRESH_OUT_OF_RESET ,
                                       I2C_MEMADD_SIZE_16BIT, (uint8_t *)&data[0], 1, 3);
    if(status != HAL_OK)
       return status;

    if(fresh == 0x01){
        if(data[0] != 0x01)
            return HAL_ERROR;
        }

    for(uint8_t i = 0; i < sizeof(private_settings)/sizeof(VL6180X_RegisterConfig_t); i++){
         uint8_t value = private_settings[i].value;
        status = HAL_I2C_Mem_Write(dev->hi2c, dev->addr, private_settings[i].reg, I2C_MEMADD_SIZE_16BIT, (uint8_t *)&value, 1, 3);
                                       
        if(status != HAL_OK)
            return status;
      
    }

    status = HAL_I2C_Mem_Write(dev->hi2c, dev->addr, VL6180X_REG_SYSTEM_FRESH_OUT_OF_RESET, 
                                            I2C_MEMADD_SIZE_16BIT, (uint8_t *)&data[1], 1, 3);

    if(status != HAL_OK)
            return status;        
    printf("VL6180X Initialized\n");    
    return status;
}


HAL_StatusTypeDef VL6180X_Read(VL6180X_HandleTypeDef *dev){

  HAL_StatusTypeDef status = HAL_OK;

  switch(dev->mode){

          case RANGE_SINGLE:  // Start a single range measurement
              status = HAL_I2C_Mem_Write(dev->hi2c, dev->addr, VL6180X_REG_SYSRANGE_START,
                                        I2C_MEMADD_SIZE_16BIT, (uint8_t *)&SingToggle, 1, 3);
              if(status != HAL_OK)
                  return status;
            // Wait for the measurement to complete
              VL6180X_Poll(dev);
              if(status != HAL_OK)
                    return status;
            // Read the range value from the sensor
              status = HAL_I2C_Mem_Read(dev->hi2c, dev->addr, VL6180X_REG_RESULT_RANGE_VAL,
                                       I2C_MEMADD_SIZE_16BIT, (uint8_t *)&dev->range_mm, 2, 3);
              if(status != HAL_OK)
                  return status;
            // Clear the interrupt status
              status = HAL_I2C_Mem_Write(dev->hi2c, dev->addr, VL6180X_REG_SYSTEM_INTERRUPT_CLEAR,
                                        I2C_MEMADD_SIZE_16BIT, (uint8_t *)&ClearInt, 1, 3);  
              if(status != HAL_OK)
                    return status;
              break;

          case RANGE_CONTINUOUS:
            int i=0;
            status = HAL_I2C_Mem_Write(dev->hi2c, dev->addr, VL6180X_REG_SYSRANGE_START,
                                        I2C_MEMADD_SIZE_16BIT, (uint8_t *)&ContToggle, 1, 3);
            if(status != HAL_OK)
                return status;
            while(i<5){
                status = VL6180X_Poll(dev);
                if(status != HAL_OK)
                    return status;
                status = HAL_I2C_Mem_Read(dev->hi2c, dev->addr, VL6180X_REG_RESULT_RANGE_VAL,
                                       I2C_MEMADD_SIZE_16BIT, (uint8_t *)&dev->range_mm, 2, 3);
                if(status != HAL_OK)
                    return status;
                status = HAL_I2C_Mem_Write(dev->hi2c, dev->addr, VL6180X_REG_SYSTEM_INTERRUPT_CLEAR,
                                        I2C_MEMADD_SIZE_16BIT, (uint8_t *)&ClearInt, 1, 3);  
                if(status != HAL_OK)
                    return status;
                i++;
            }
            status = HAL_I2C_Mem_Write(dev->hi2c, dev->addr, VL6180X_REG_SYSRANGE_START,
                                        I2C_MEMADD_SIZE_16BIT, (uint8_t *)&SingToggle, 1, 3);
              break;

          case ALS_SINGLE:
          case ALS_CONTINUOUS:
              break;

          case INTERLEAVED:
              break;
          default:
              return HAL_ERROR;
      };

      return status;
};


