/*
 * lcd.h
 *
 * Created: 5/22/2020 4:24:09 PM
 *  Author: mnaguib
 */ 


#ifndef LCD_H_
#define LCD_H_


#define  F_CPU 8000000UL
#include "avr/io.h"
#include "data_types.h"
#include "bit_math.h"
#include "util/delay.h"

#define LCD_DATA_PORT		PORTC
#define LCD_DATA_DDR		DDRC
#define LCD_BL_DDR			DDRE /*LCD Back light(BL)*/

#define LCD_CTRL_PORT		PORTB
#define LCD_CTRL_DDR		DDRB
#define LCD_BL_PORT			PORTE

#define	LCD_RS				PB5
#define LCD_RW				PB6
#define	LCD_EN				PB7
#define LCD_BL_PIN			PE4

#define CMD_CLEAR			0x01
#define CMD_ENTRY_MODE		0x06
#define CMD_DISP_ON			0x0C
#define CMD_CFG				0x38

/* x (1-2 line), y (1-16) cols */
void LCD_Init(void);
void LCD_Clear(void);
void LCD_DispChar(INT8U u8Char);
void LCD_DispStr(INT8U* pu8Str);
void LCD_DispCharXY(INT8U x, INT8U y, INT8U u8Char);
void LCD_DispStrXY(INT8U x, INT8U y, INT8U* pu8Str);
void LCD_DispInt(int intNum);
void LCD_DispIntXY(INT8U x, INT8U y, int intNum);

#endif /* LCD_H_ */