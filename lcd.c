/*
* lcd.c
*
* Created: 5/22/2020 4:23:48 PM
*  Author: mnaguib
*/
#include "lcd.h"

static void LCD_SendCmd(INT8U u8Cmd);
static void LCD_SendData(INT8U u8Data);
static void LCD_GotoXY(INT8U x, INT8U y);

static void LCD_SendCmd(INT8U u8Cmd){
	clearBit(LCD_CTRL_PORT,LCD_RS);
	LCD_DATA_PORT =u8Cmd;
	setBit(LCD_CTRL_PORT,LCD_EN);
	clearBit(LCD_CTRL_PORT,LCD_EN);
	_delay_us(50);
}
static void LCD_SendData(INT8U u8Data){
	setBit(LCD_CTRL_PORT,LCD_RS);
	LCD_DATA_PORT=u8Data;
	setBit(LCD_CTRL_PORT,LCD_EN);
	clearBit(LCD_CTRL_PORT,LCD_EN);
	_delay_us(50);
	
}
static void LCD_GotoXY(INT8U x, INT8U y){
	/* get address of DDRAM using x,y */
	if(x == 1){
		LCD_SendCmd((0x80|0x00) + y-1); /* Eqn */
	}
	else{
		LCD_SendCmd((0x80|0x40) + y-1); /* Eqn */
	}
}

void LCD_Init(void){
	_delay_ms(20);
	setALLBits(LCD_DATA_DDR);
	setBit(LCD_CTRL_DDR,LCD_RS);
	setBit(LCD_CTRL_DDR,LCD_RW);
	setBit(LCD_CTRL_DDR,LCD_EN);
	clearBit(LCD_CTRL_PORT,LCD_RW);
	/*Back Light*/
	setBit(LCD_BL_DDR,LCD_BL_PIN);
	setBit(LCD_BL_PORT,LCD_BL_PIN);
	_delay_ms(20);
	LCD_SendCmd(CMD_CFG);
	LCD_SendCmd(CMD_DISP_ON);
	LCD_SendCmd(CMD_ENTRY_MODE);
	LCD_Clear();
}
void LCD_Clear(void){
	LCD_SendCmd(CMD_CLEAR);
	_delay_ms(5);
}
void LCD_DispChar(INT8U u8Char){
	LCD_SendData(u8Char);
}
void LCD_DispStr(INT8U* pu8Str){
	int i;
	for(i=0;pu8Str[i]!='\0';i++){
		LCD_SendData(pu8Str[i]);
	}
}

void LCD_DispCharXY(INT8U x, INT8U y, INT8U u8Char){
	LCD_GotoXY(x,y);
	LCD_SendData(u8Char);
}
void LCD_DispStrXY(INT8U x, INT8U y, INT8U* pu8Str){
	LCD_GotoXY(x,y);
	LCD_DispStr(pu8Str);
}
void LCD_DispInt(int intNum){char a_bufferString[17]={0};sprintf(a_bufferString, "%3d", intNum);LCD_DispStr(a_bufferString);}void LCD_DispIntXY(INT8U x, INT8U y, int intNum){	LCD_GotoXY(x,y);	LCD_DispInt(intNum);}

	