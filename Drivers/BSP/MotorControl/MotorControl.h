#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_
#include "main.h"




typedef enum {
    MOTOR_TYPE_DC,
    MOTOR_TYPE_STEP,
    MOTOR_TYPE_BLDC
} MotorType_t;

typedef struct {
    MotorType_t type;
    PIDController *pid;
		TIM_HandleTypeDef *htim;
		uint32_t channel;
		GPIO_TypeDef *In1Port;
		uint16_t In1Pin;
		GPIO_TypeDef *In2Port;
		uint16_t In2Pin;
		GPIO_TypeDef *STBYPort;
		uint16_t STBYPin;
    UART_HandleTypeDef *huart;
		GPIO_TypeDef *DirPort;
		uint16_t DirPin;
		GPIO_TypeDef *EnPort;
		uint16_t EnPin;

}PIDMOTOR_HandleTypeDef;

#define DCMotor(PID_, TIM_, CH_, IN1_PORT, IN1_PIN, IN2_PORT, IN2_PIN, STBY_PORT, STBY_PIN) \
{                                       \
  .type     = MOTOR_TYPE_DC,            \
  .pid      = (PID_),                   \
  .htim     = (TIM_),                   \
  .channel  = (CH_),                    \
  .In1Port  = (IN1_PORT),               \
  .In1Pin   = (IN1_PIN),                \
  .In2Port  = (IN2_PORT),               \
  .In2Pin   = (IN2_PIN),                \
  .STBYPort = (STBY_PORT),              \
  .STBYPin  = (STBY_PIN),               \
}


#define StepMotor(PID_, TIM_, CH_, DIR_PORT, DIR_PIN, EN_PORT, EN_PIN) \
{                                                                               \
  .type = MOTOR_TYPE_STEP,                                                       \
  .pid = (PID_),                                                                 \
  .htim = (TIM_),                                                                \
  .channel = (CH_),                                                              \
  .DirPort = (DIR_PORT),                                                         \
  .DirPin = (DIR_PIN),                                                           \
  .EnPort = (EN_PORT),                                                           \
  .EnPin = (EN_PIN),                                                             \
}



#define BLDCMotor(PID_, TIM_, CH_, DIR_PORT, DIR_PIN, EN_PORT, EN_PIN) \
{                                                                               \
  .type = MOTOR_TYPE_BLDC,                                                       \
  .pid = (PID_),                                                                 \
  .htim = (TIM_),                                                                \
  .channel = (CH_),                                                              \
  .DirPort = (DIR_PORT),                                                         \
  .DirPin = (DIR_PIN),                                                           \
  .EnPort = (EN_PORT),                                                           \
  .EnPin = (EN_PIN),                                                             \
}


void  DCMotor_PID1(PIDMOTOR_HandleTypeDef *motor, float setpoint, float measurement);
void  DCMotor_Init1(PIDMOTOR_HandleTypeDef *motor);

#endif /* MOTOR_CONTROL_H_ */