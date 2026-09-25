#ifndef MOTOR_PID_CONTROLLER_H_
#define MOTOR_PID_CONTROLLER_H_
#include "main.h"

typedef struct {

	/* Controller gains */
	float Kp;
	float Ki;
	float Kd;

	/* Derivative low-pass filter time constant */
	float tau;

	/* Output limits */
	float limMin;
	float limMax;
	
	/* Integrator limits */
	float limMinInt;
	float limMaxInt;

	/* Sample time (in seconds) */
	float T;

	/* Controller "memory" */
	float integrator;
	float prevError;			/* Required for integrator */
	float differentiator;
	float prevMeasurement;		/* Required for differentiator */

	/* Controller output */
	float out;

} PIDController;

typedef struct {

		TIM_HandleTypeDef *htim;
		uint32_t channel;
		GPIO_TypeDef *In1Port;
		uint16_t In1Pin;
		GPIO_TypeDef *In2Port;
		uint16_t In2Pin;
		GPIO_TypeDef *STBYPort;
		uint16_t STBYPin;

} PIDDCMotor_HandleTypeDef;

typedef struct {

		TIM_HandleTypeDef *htim;
		UART_HandleTypeDef *huart;
		uint32_t channel;
		GPIO_TypeDef *DirPort;
		uint16_t DirPin;
		GPIO_TypeDef *EnPort;
		uint16_t EnPin;

} StepperMotor_HandleTypeDef;

void  PIDController_Init(PIDController *pid);
float PIDController_Update(PIDController *pid, float setpoint, float measurement);
void  DCMotor_Init(PIDDCMotor_HandleTypeDef *motor);
void  DCMotor_PID(PIDController *pid, PIDDCMotor_HandleTypeDef *motor, float setpoint, float measurement);
void  StepMotor_PID(PIDController *pid, StepperMotor_HandleTypeDef *motor, float setpoint, float measurement);
#endif