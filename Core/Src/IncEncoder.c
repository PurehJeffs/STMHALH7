/*
 * BournsIncEncoder.c
 *
 *  Created on: Jul 24, 2026
 *      Author: ubern
 */
#include "IncEncoder.h"



void ReadEncPoll(IncEnc_HandleTypeDef *dev)
{

    GPIO_PinState currentA;
    GPIO_PinState currentB;

    currentA = HAL_GPIO_ReadPin(dev->portA, dev->pinA);

    // Detect rising edge on A
    if (dev->EncA == GPIO_PIN_RESET &&
        currentA == GPIO_PIN_SET)
    {
        currentB = HAL_GPIO_ReadPin(dev->portB, dev->pinB);

        if (currentB == GPIO_PIN_RESET)
        {
            dev->Pos++;      // Clockwise
        }
        else
        {
            dev->Pos--;      // Counter-clockwise
        }
    };

    dev->EncA = currentA;
};
