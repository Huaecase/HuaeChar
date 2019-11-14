// 中断控制
#ifndef _INT_H
#define _INT_H

#include "SN8F5708.H"
#include "GenericTypeDefs.h"

void Global_INT(UINT8 a);
void Timer0_INT(UINT8 a);
void Timer1_INT(UINT8 a);
void Timer2_INT(UINT8 a);


void PWM1_INT(UINT8 a);
void PWM2_INT(UINT8 a);
void PWM3_INT(UINT8 a);

void ADC_INT(UINT8 a);
void IIC_INT(UINT8 a);
void UART_INT(UINT8 a);
void SPI_INT(UINT8 a);

#endif
