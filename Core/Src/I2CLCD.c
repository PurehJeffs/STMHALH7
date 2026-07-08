#include "I2CLCD.h"
#include <stdio.h>

void SendLCD(uint8_t byte, uint8_t rs){ // data byte , register select config 0 - command 1 - data

	uint8_t buf[4];
	uint8_t upper;
	uint8_t lower;
	HAL_StatusTypeDef status;

	upper = (byte & 0xF0);
	lower= ((byte & 0x0F) << 4);

	if(rs){			//set to Write mode and enable Back light
		upper|=0x09;
		lower|=0x09;
	}
	else{           //set to read mode and enable back light
		upper|=0x08;
		lower|=0x08;
	}
	buf[0]= upper | 0x04; //EN High
	buf[1]= upper;

	buf[2]= lower | 0x04; //EN High
	buf[3]= lower;

	 status = HAL_I2C_Master_Transmit(&hi2c2, PCF8574_add, buf, 4, HAL_MAX_DELAY);

	if(status != HAL_OK)
		    {
		        printf("I2C TX Error: %d\r\n", status);
		    }

}
void LCD4BitSend(uint8_t data, uint8_t rs){

	 uint8_t command;
	 HAL_StatusTypeDef status;

	    command = data;

	    if(rs)
	        command |= 0b00000001;  // RS

	    uint8_t buf[2];

	    buf[0] = command | 0b00000100;  // E=1
	    buf[1] = command;               // E=0

	    status = HAL_I2C_Master_Transmit(&hi2c2, PCF8574_add, buf, 2, HAL_MAX_DELAY);

	    if(status != HAL_OK)
	    {
	        printf("I2C TX Error: %d\r\n", status);
	    }

}
void LCDInit(){

	HAL_Delay(50);					// Initialize LCD into Into 4 bit mode
	LCD4BitSend(LCDStartup,0);
	HAL_Delay(6);
	LCD4BitSend(LCDStartup, 0);
	HAL_Delay(2);
	LCD4BitSend(LCDStartup, 0);
	HAL_Delay(2);
	LCD4BitSend(LCD4BitMode, 0);


	HAL_Delay(2);
	SendLCD(LCD4Bit2Line, 0);
	SendLCD(LCDDisplayOn, 0);
	SendLCD(LCDClear, 0);
	HAL_Delay(2);
	SendLCD(LCDEntryMode, 0);
	HAL_Delay(2);
	SendLCD('G', 1);

}

void PrintLCD(char *str){

	 while(*str)
	    {
	        SendLCD((uint8_t)*str,1);
	        str++;
	    }

}

void LCD_SetCursor(uint8_t row, uint8_t col)
{
    uint8_t addr;

    if(row == 0)
    {
        addr = col;
    }
    else
    {
        addr = 0x40 + col;
    }

    SendLCD(0x80 | addr, 0);
}
