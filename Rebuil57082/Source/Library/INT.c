#include "INT.h"


void Global_INT(UINT8 a)
{
	if (a)
		EAL=1;
	else 
		EAL=0;
}	


void Timer0_INT(UINT8 a)
{
	if(a)
		ET0=1;
	else
		ET0=0;

}

void Timer1_INT(UINT8 a)
{
	if(a)
		ET1=1;
	else
		ET1=0;

}

void Timer2_INT(UINT8 a)
{
	if(a)
		ET2=1;
	else
		ET2=0;
}

void ADC_INT(UINT8 a)
{
	if(a)
		IEN2|= 0x08;
	else 
		IEN2&= 0xf7;
}
void PWM1_INT(UINT8 a)
{
	if(a)
		IEN4|= 0x80;
	else
		IEN4&= 0x7f;
}

void PWM2_INT(UINT8 a)
{
	if(a)
		IEN2|= 0x02;
	else
		IEN2&= 0xfd;
}

void PWM3_INT(UINT8 a)
{
	if(a)
		IEN2|= 0x04;
	else
		IEN2&= 0xfb;
}


void IIC_INT(UINT8 a)
{
	if (a)
		EI2C=1;
	else
		EI2C=0;
}
void UART_INT(UINT8 a)
{
  if(a)
	  ES0=1;
  else
	  ES0=0;
}
void SPI_INT(UINT8 a)
{
	if(a)
		ESPI=1;
	else 
		ESPI=0;
}



