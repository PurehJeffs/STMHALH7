/*
 * BournsIncEncoder.h
 *
 *  Created on: Jul 24, 2026
 *      Author: ubern
 */

#ifndef INC_INCENCODER_H_
#define INC_INCENCODER_H_
#include "main.h"


typedef struct{
	GPIO_TypeDef *portA;
	uint16_t pinA;

	GPIO_TypeDef *portB;
	uint16_t pinB;

	GPIO_PinState EncA;
	GPIO_PinState EncB;

	int16_t Pos;

}IncEnc_HandleTypeDef;

#define TWOPINGPIO(PortA,PinA,PortB,PinB) \
{                                     \
    .portA = (PortA),              \
    .pinA = (PinA),                \
	.portB = (PortB),              \
	.pinB = (PinB),                 \
	.Pos = 0               			  \
}

#define TWOPININT(portA,pinA,portB,pinB) \
{                                     \
    .DirPortA = (portA),              \
    .DirPinA = (pinA),                \
	.DirPortB = (portB),              \
	.DirPinB = (pinB)                 \
	.Pos = 0             			  \
}

//void ReadEnc(IncEnc_HandleTypeDef *dev){
//	//code for reading enc polling
//	if((dev->EncA = HAL_GPIO_ReadPin(dev->PortA, dev->PinA)) == GPIO_PIN_SET){
//
//	}
//}

void ReadEnc(IncEnc_HandleTypeDef *dev);

#endif /* INC_INCENCODER_H_ */
