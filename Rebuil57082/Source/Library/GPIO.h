#ifndef _GPIO_H_
#define _GPIO_H_

#include "SN8F5708.H"
#include "GenericTypeDefs.h"

//#define GPIO_RT_curt		P07				// GPIO to set rated current output 

//extern void GPIO_Init(void);
//extern UINT8 Rated_current_set(void);
void GPIO_In(UINT8 Pin);       //  P0-P5 ，0-7 pin，当前模式为 PxM 某位位0 ，对应Pin位 输入模式
void GPIO_Out(UINT8 Pin);      //  P0-P5 ，0-7 pin，当前模式为 PxM 某位位1 ，对应Pin位 输出模式
void GPIO_Up(UINT8  Pin);
void GPIO_NoUp(UINT8 Pin);

#endif
