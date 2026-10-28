#ifndef VL6180X_H_
#define VL6180X_H_
#include "main.h"

#define VL6180X_DEFAULT_ADDRESS                0x52 //(0x29 << 1) 

#define VL6180X_REG_SYSRANGE_START             0x0018U
#define VL6180X_REG_SYSALS_START               0x0038U

#define VL6180X_REG_IDENTIFICATION_MODEL_ID    0x0000U
#define VL6180X_REG_SYSTEM_FRESH_OUT_OF_RESET  0x0016U

#define VL6180X_REG_SYSTEM_INTERRUPT_CLEAR     0x0015U
#define VL6180X_REG_RESULT_INTERRUPT_STATUS    0x004FU
#define VL6180X_REG_RESULT_RANGE_STATUS        0x004DU
#define VL6180X_REG_RESULT_RANGE_VAL           0x0062U



typedef struct
{
    uint16_t reg;
    uint8_t value;
} VL6180X_RegisterConfig_t;


typedef enum {
    RANGE_SINGLE     = 1,
    RANGE_CONTINUOUS = 2,
    ALS_SINGLE       = 3,
    ALS_CONTINUOUS   = 4,
    INTERLEAVED      = 5
} MODEType_t;

typedef struct
{
    I2C_HandleTypeDef *hi2c;
    uint16_t addr;
    uint16_t range_mm;
    MODEType_t mode;

} VL6180X_HandleTypeDef;

HAL_StatusTypeDef VL6180X_Poll(VL6180X_HandleTypeDef *dev);
HAL_StatusTypeDef VL6180X_Init(VL6180X_HandleTypeDef *dev);
HAL_StatusTypeDef VL6180X_Read(VL6180X_HandleTypeDef *dev);
#endif /* VL6180X_H_ */