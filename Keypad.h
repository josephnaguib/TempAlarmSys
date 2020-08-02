/*
 * Keypad.h
 *
 * Created: 5/21/2020 1:03:22 PM
 *  Author: mnaguib
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "board.h"

#define KEY_PORT  PORTD
#define KEY_DDR   DDRD
#define KEY_PINR  PIND
                  
#define KEY_ROWS_MSK 0X0F
#define KEY_COLS_MSK 0XF0

#define KEY_NONE	0xff
void Key_Init(void);
INT8U key_GetKey(void);




#endif /* KEYPAD_H_ */