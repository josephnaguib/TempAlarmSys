/*
 * TAS.c
 *
 * Created: 6/9/2020 12:07:11 PM
 *  Author: mnaguib
 */ 
#include "TAS.h"

TAS_Struct TAS={SS_MAIN,YES,0,100};
	
void TAS_Init(void){
	LCD_Init();
	BUZ_Init();
	led_Init();
	leds_Init(0xff);
	Key_Init();
	ADC_Init();
	UART_Init(UART_0,9600);
}
void TAS_DispAA(void){
	LCD_DispCharXY(Display_L1,DISP_IND_AA,TAS.AlarmAct);
}
void TAS_DispC(void){
	 LCD_DispIntXY(Display_L1,DISP_IND_C,TAS.CurrentTemp);
}
void TAS_DispT(void){
	 LCD_DispIntXY(Display_L1,DISP_IND_T,TAS.ThreshTemp);
}
void TAS_DispState(void){
	switch(TAS.SystemState){
		case SS_MAIN:
		LCD_DispStrXY(1,1,DISP_MAIN_L1);
		LCD_DispStrXY(2,1,DISP_MAIN_L2);        
		break;
		case SS_KEY_CFG:
		LCD_DispStrXY(1,1,DISP_Key_CFG_L1);
		LCD_DispStrXY(2,1,DISP_Key_CFG_L2); 
		break;
		case SS_TERM_CFG:
		LCD_DispStrXY(1,1,DISP_TERM_CFG_L1);
		LCD_DispStrXY(2,1,DISP_TERM_CFG_L2);  
		break;
		case SS_ALARM:
		LCD_DispStrXY(1,1,DISP_Alarm_L1);
		LCD_DispStrXY(2,1,DISP_Alarm_L2);
		break;
	}
}

void TAS_ToggleAA(void){
	if(TAS.AlarmAct==YES){
		TAS.AlarmAct=NO;
	}
	else{
		TAS.AlarmAct=YES;
	}
}
Bool TAS_UpdateC(void){
	Bool result=FALSE;
	INT16U temp=ADC_Read(0);
	temp=(temp*150UL)/1023; /*0:1023 to 0:150 C*/
	if(temp !=TAS.CurrentTemp){
		TAS.CurrentTemp=temp;
		result=TRUE;
	}
	return result;
}