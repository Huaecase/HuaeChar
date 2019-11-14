#ifndef LED_H
#define LED_H
#include "SN8F5708.H"
#include "PWM.h"
#include "GenericTypeDefs.h"

#define LEDPWMnum  1 // 用PWM 3 1 通道 !!!!!!
           //改动这里 中断函数的伪代码也要改动
#define LEDPWM_IOPin     (46)    //P46输出
#define LEDPWMcircle     (4095)
#define LEDPWMInitDuty   (10)
#define LEDIncreamentstep   (5)
#define LEDBreathModel   jumpup   // 设置
#define LedsameDutyRepeat  (6000)
//呼吸模式 为 jumpup,Dutystep必须大于0，
//呼吸模式为 jumpdown,Dutystep必须小于0//circle模式无所谓

typedef enum
{
	jumpdown,
	jumpup,
	circle
}Model;

extern int DutyNum;   //方波占空比
void Breathled_init(void);
void LED_BreathStart(UINT8 a);


#endif 