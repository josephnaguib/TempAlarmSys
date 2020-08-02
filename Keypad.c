/*
 * Keypad.c
 *
 * Created: 5/21/2020 1:03:37 PM
 *  Author: mnaguib
 */ 
#include"Keypad.h"
void Key_Init(void){
	setBits(KEY_DDR,KEY_ROWS_MSK);//ROWS out
	clearBits(KEY_DDR,KEY_COLS_MSK);//COLS In
	setBits(KEY_PORT,KEY_ROWS_MSK);//deactivate all rows
	setBits(KEY_PORT,KEY_COLS_MSK);//Pullup Cols
	
}
INT8U key_GetKey(void){
	INT8U key=KEY_NONE;
	INT8U Row=0;
	INT8U Col=0;
	INT8U keys[4][4]={'7','8','9','/','4','5','6','*','1','2','3','-','C','0','=','+'};
	for(Row=0;Row<4;Row++){
		clearBit(KEY_PORT,Row);	
		_delay_ms(1); // To Ensure that the signal is sent to keypad
		for(Col=0;Col<4;Col++){
			if(!readBit(KEY_PINR,Col+4)){
				while(!readBit(KEY_PINR,Col+4));
				//key=Col+(Row*4)+1;
				key=keys[Row][Col];
				return key;
			}			
		}
		setBit(KEY_PORT,Row);
	}
	return KEY_NONE;
}