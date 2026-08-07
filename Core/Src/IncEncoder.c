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

void IncEncoder_EXTI(IncEnc_HandleTypeDef *dev)
{
    uint8_t A = HAL_GPIO_ReadPin(dev->portA, dev->pinA);
    uint8_t B = HAL_GPIO_ReadPin(dev->portB, dev->pinB);

  //  printf("%d%d\r\n", A, B);

    uint8_t currState = (A << 1) | B;

    static const int8_t table[16] =
    {
         0, -1,  1,  0,
         1,  0,  0, -1,
        -1,  0,  0,  1,
         0,  1, -1,  0
    };

    uint8_t index = (dev->PrevState << 2) | currState;

    dev->Pos += table[index];

    dev->PrevState = currState;

}
