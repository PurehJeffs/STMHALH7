#include "MotorPID.h"

void PIDController_Init(PIDController *pid) {

	/* Clear controller variables */
	pid->integrator = 0.0f;
	pid->prevError  = 0.0f;

	pid->differentiator  = 0.0f;
	pid->prevMeasurement = 0.0f;

	pid->out = 0.0f;

}

float PIDController_Update(PIDController *pid, float setpoint, float measurement) {


	// Error signal

    float error = setpoint - measurement;

	//Proportional
	
    float proportional = pid->Kp * error;

	// Integral
	
    pid->integrator = pid->integrator + 0.5f * pid->Ki * pid->T * (error + pid->prevError);

	/* Anti-wind-up via integrator clamping */
    if (pid->integrator > pid->limMaxInt) {

        pid->integrator = pid->limMaxInt;

    } else if (pid->integrator < pid->limMinInt) {

        pid->integrator = pid->limMinInt;

    }

	// Derivative (band-limited differentiator)
		
    pid->differentiator = -(2.0f * pid->Kd * (measurement - pid->prevMeasurement)	/* Note: derivative on measurement, therefore minus sign in front of equation! */
                        + (2.0f * pid->tau - pid->T) * pid->differentiator)
                        / (2.0f * pid->tau + pid->T);

//Compute output and apply limits

    pid->out = proportional + pid->integrator + pid->differentiator;

    if (pid->out > pid->limMax) {

        pid->out = pid->limMax;

    } else if (pid->out < pid->limMin) {

        pid->out = pid->limMin;

    }

	/* Store error and measurement for later use */
    pid->prevError       = error;
    pid->prevMeasurement = measurement;

	/* Return controller output */
    return pid->out;

}

void  DCMotor_PID(PIDController *pid, PIDDCMotor_HandleTypeDef *motor, float setpoint, float measurement)  {

	float pidOutput = PIDController_Update(pid, setpoint, measurement);

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
void  DCMotor_Init(PIDDCMotor_HandleTypeDef *motor) {
	
	HAL_GPIO_WritePin(motor->In1Port, motor->In1Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(motor->In2Port, motor->In2Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(motor->STBYPort, motor->STBYPin, GPIO_PIN_SET);
	HAL_TIM_PWM_Start(motor->htim, motor->channel);
}
void  StepMotor_PID(PIDController *pid, StepperMotor_HandleTypeDef *motor, float setpoint, float measurement) {
}