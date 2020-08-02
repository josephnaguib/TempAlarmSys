/*
* interfacingproject.c
*
* Created: 5/20/2020 10:19:02 AM
*  Author: mnaguib
*/
#include "TAS.h"
extern TAS_Struct TAS;
int main(void)
{
	System_State	prevState = SS_NONE;
	INT8U			key = 0;
	INT8U			digitInd = 0;
	INT8U			data = 0;
	INT32U			delayCount = 0;
	INT8U			threshTemp = 0;
INT8U			digits[3]={0};
INT8U			ind = 0;

TAS_Init();

while(1){
	
	switch (TAS.SystemState)
	{
		case SS_MAIN:
		/* for each entry */
		if(prevState != SS_MAIN){
			prevState = SS_MAIN;
			TAS_DispState();
			TAS_DispT();
			TAS_DispAA();
			TAS_DispC();
			
			if (TAS.CurrentTemp >= TAS.ThreshTemp && TAS.AlarmAct == YES)
			{
				TAS.SystemState = SS_ALARM;
			}
			
		}
		/* C */
		if(TAS_UpdateC()){
			TAS_DispC();
			if (TAS.CurrentTemp >= TAS.ThreshTemp && TAS.AlarmAct == YES)
			{
				TAS.SystemState = SS_ALARM;
			}
		}
		/* Keys */
		key = key_GetKey();
		if (key == 15)
		{
			TAS.SystemState = SS_KEY_CFG;
		}
		else if (key == 13)
		{
			TAS_ToggleAA();
			TAS_DispAA();
			if (TAS.CurrentTemp >= TAS.ThreshTemp && TAS.AlarmAct == YES)
			{
				TAS.SystemState = SS_ALARM;
			}
		}
		/* Term */
		if (UART_ReceiveByte_Unblock(UART_0,&data))
		{
			if(data == 'G'){
				TAS.SystemState = SS_TERM_CFG;
			}
		}
		break;
		case SS_KEY_CFG:
		/* for each entry */
		if(prevState != SS_KEY_CFG){
			prevState = SS_KEY_CFG;
			TAS_DispState();
			digitInd = 0;
		}
		/* Keys */
		key = key_GetKey();
		if (key == 12)
		{
			TAS.SystemState = SS_MAIN;
		}
		else if (key == 15)
		{
			TAS.SystemState = SS_MAIN;
			threshTemp = 0;
			for (ind = 0; ind < digitInd;ind++)
			{
				threshTemp = threshTemp*10 + digits[ind];
			}
			TAS.ThreshTemp = threshTemp;
		}
		else if (key >= 1 && key <= 10 && digitInd < 3)
		{
			if(key == 10){
				key = 0;
			}
			LCD_DispCharXY(Display_L1,DISP_IND_T+digitInd,key+'0');
			digits[digitInd]=key;
			digitInd++;
		}
		break;
		case SS_TERM_CFG:
		/* for each entry */
		if(prevState != SS_TERM_CFG){
			prevState = SS_TERM_CFG;
			TAS_DispState();
			digitInd = 0;
		}
		/* Keys */
		
		if(UART_ReceiveByte_Unblock(UART_0,&data)){
			if (data == 'C')
			{
				TAS.SystemState = SS_MAIN;
			}
			else if (data == 'O')
			{
				TAS.SystemState = SS_MAIN;
				threshTemp = 0;
				for (ind = 0; ind < digitInd;ind++)
				{
					threshTemp = threshTemp*10 + digits[ind];
				}
				TAS.ThreshTemp = threshTemp;
			}
			else if (data >= '0' && data <= '9' && digitInd < 3)
			{
				LCD_DispCharXY(Display_L1,DISP_IND_T+digitInd,data);
				digits[digitInd] = data - '0';
				digitInd++;
			}
		}

		break;
		case SS_ALARM:
		/* for each entry */
		if(prevState != SS_ALARM){
			prevState = SS_ALARM;
			TAS_DispState();
		}
		/* Alarm Scenario */
		if (delayCount >= 500)
		{
			delayCount = 0;
			BUZ_Toggle();
			led_Toggle();
			leds_Toggle(0XFF);
		}
		_delay_ms(50);
		delayCount += 50;
		
		/* C */
		if(TAS_UpdateC()){
			if (TAS.CurrentTemp < TAS.ThreshTemp)
			{
				TAS.SystemState = SS_MAIN;
			}
		}
		/* Keys */
		key = key_GetKey();
		if (key == 12)
		{
			TAS.SystemState = SS_MAIN;
			TAS.AlarmAct = NO;
		}
		/* Term */
		if (UART_ReceiveByte_Unblock(UART_0,&data))
		{
			if(data == 'S'){
				TAS.SystemState = SS_MAIN;
				TAS.AlarmAct = NO;
			}
		}
		/* Turn buzzer off before state transition */
		if(TAS.SystemState != SS_ALARM){
			BUZ_Off();
			led_Off();
			leds_Off(0xff);
			delayCount = 0;
		}
		break;
	}
	
}
}