#ifndef PWM_H
#define PWM_H
#include "SN8F5708.H"
#include "GenericTypeDefs.h"
#include "GPIO.h"  //用来快速设置 GPIO管脚 In/Out   Up/NoUp


//PWnM寄存器，控制 PWMn 震荡源分频系数/PWM输出是否反向/PWMn输出 通道   、是否是单脉冲输出
#define PWM_RSTVALUE 0x00;
#define PWMRateCLR   0x1f; //PWMnRATE 在PW1M[7..5];
#define Fosc_1    (7<<5)
#define Fosc_2    (6<<5)
#define Fosc_4    (5<<5)
#define Fosc_8    (4<<5)
#define Fosc_16   (3<<5)
#define Fosc_32   (2<<5)
#define Fosc_64   (1<<5)
#define Fosc_128  (0<<5)
	//反向位
	//通道位
#define PWMCH0    (1<<1)
#define PWMCH1    (1<<2)
	//单脉冲位
		// 默认不启用
//P1OC
#define PWM1En    (1<<5)
#define PWM2En		(1<<6)
#define PWM3En		(1<<7)

//OPM寄存器 ，是否允许比价器控制PWMn输出，

//**************************************************************************************************
//-----------------------//PWM1输出应用函数-----------------------------------------------------
void PWMn_Out_Init(UINT8 PWMn,UINT16 Circle,UINT8 Dutynum,UINT8 Intter,UINT8 io);// PWMn 、周期、占空比、中断控制、输出IO口
void PWMn_EnorDis(UINT8 PWMn,UINT8  d);
//-----------------------------------------------------------------------------
//*********************PW1M组件函数*******************************************************


//void PW1M_RST(void);    //寄存器复位状态
//void PW1rate_clear(void);

void PWMn_Fpwm(UINT8 PWMn,UINT8 FCPUtoFPWM_Div);
void PWMn_ValueDuty(UINT8 PWMn,unsigned long a,int duty);

// PW1 chanel 使能方法？ PW1Chanel |=PWM10_P05En，禁用 方法： PW1Chanel &=PWM10_P05Disable;
//
void PWMChanelPin_EnorNot(UINT8 Pin,UINT8 d);

void PWMn_IntEnableorDis(UINT8 PWMn, UINT8  c);

#endif
