/*
* TAS.h
*
* Created: 6/9/2020 12:06:48 PM
*  Author: mnaguib
*/


#ifndef TAS_H_
#define TAS_H_


#include "board.h"
#include "uart.h"
#include "Keypad.h"
#include "ADC.h"
#include "lcd.h"
typedef enum{
	SS_NONE,SS_MAIN,SS_KEY_CFG,SS_TERM_CFG,SS_ALARM
}System_State;

typedef enum{
	YES='Y', NO='N'
}Alarm_Act;

typedef struct{
	System_State SystemState;	/*SS*/
	Alarm_Act AlarmAct;			/*AA*/
	INT8U CurrentTemp;			/*C*/
	INT8U ThreshTemp;			/*T*/
}TAS_Struct;

#define DISP_MAIN_L1		"C:    T:    AA: "
#define DISP_MAIN_L2		"K:15 T:G  AAC:13"

#define DISP_Alarm_L1		"    Alarming    "
#define DISP_Alarm_L2		"  KAD:12 TAD:S  "

#define DISP_Key_CFG_L1		"       T:       "
#define DISP_Key_CFG_L2 	"  OK:15  CN:12  "

#define DISP_TERM_CFG_L1	"       T:       "
#define DISP_TERM_CFG_L2 	"   OK:O CN:C    "

#define DISP_IND_C			3
#define DISP_IND_T			9
#define DISP_IND_AA			16
#define Display_L1			1
#define Display_L2			2

void TAS_Init(void);
void TAS_DispAA(void);
void TAS_DispC(void);
void TAS_DispT(void);
void TAS_DispState(void);

Bool TAS_UpdateC(void);
void TAS_ToggleAA(void);

#endif /* TAS_H_ */