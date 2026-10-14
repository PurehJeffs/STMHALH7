#include "MotorControl.h"
void  DCMotor_PID1(PIDMOTOR_HandleTypeDef *motor, float setpoint, float measurement)  {

	float pidOutput = PIDController_Update(motor->pid, setpoint, measurement);

	if(((measurement - setpoint)<= 10) && ((measurement - setpoint) >= -10)){
    	__HAL_TIM_SET_COMPARE(motor->htim, motor->channel, 0);
    }
	else{
		if (pidOutput > 0.0f) {

		HAL_GPIO_WritePin(motor->In1Port, motor->In1Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(motor->In2Port, motor->In2Pin, GPIO_PIN_RESET);
		} 
		else {

			HAL_GPIO_WritePin(motor->In1Port, motor->In1Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(motor->In2Port, motor->In2Pin, GPIO_PIN_SET);
		}
		__HAL_TIM_SET_COMPARE(motor->htim, motor->channel, fabsf(pidOutput));
	}
	
}