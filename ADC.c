/*
 * ADC.c
 *
 * Created: 5/31/2020 2:55:36 PM
 *  Author: mnaguib
 */ 
#include "ADC.h"

void	ADC_Init(void){	/* Clock */	ADC_Struct->ADCSRA_BF.ADPS = 0b111;	/* Ref -> AVcc */	ADC_Struct->ADCMUX_BF.REFS = 0b01;	/* Enable */	ADC_Struct->ADCSRA_BF.ADEN_B = 1;}INT16U	ADC_Read(INT8U u8Channel){	/* Select Channel */	ADC_Struct->ADCMUX_BF.MUX = u8Channel;	/* Start Conversion */	ADC_Struct->ADCSRA_BF.ADSC_B = 1;	/* wait util conversion completes */	while( ADC_Struct->ADCSRA_BF.ADSC_B == 1);	/* return ADC Data */	return ADC_Struct->ADC_Data;}
