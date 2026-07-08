#ifndef I2CLCD_H
#define I2CLCD_H

#include "main.h"

#define PCF8574_add  0x4E
#define LCDStartup	0x30
#define LCD4BitMode	0x20
#define LCDClear 0x01
#define LCDEntryMode 0x06
#define LCD4Bit2Line 0x28
#define LCDDisplayOn 0x0C


void SendLCD(uint8_t byte, uint8_t rs);
void LCD4BitSend(uint8_t data, uint8_t rs);
void LCDInit();
void PrintLCD(char *str);
void LCD_SetCursor(uint8_t row, uint8_t col);

#endif
