#ifndef ADC_H
#define ADC_H

#include "SN8F5708.H"
#include "GPIO.h"
#include "GenericTypeDefs.h"
//------------ADM 寄存器:-------复位状态 0x00 ---------// 作用： 使能 ADC    ADC转换开始位   转换状态位  输入通道选择
#define ADCEnable  (8<<4)
#define ADCDisable 0x7f
#define ADCStart   (1<<6)         //ADC 转换结束后硬件自动清零
#define ADCStatus  (ADM&0x20)    //第5位 ，EOC，0 ：转换中，1：转换结束(需要固件清零)
#define ADC_TransOk      0x20   //EOC位 为1
#define ADCStatus_Clear  0xDF  // 清除 EOC 位， 表示 ADC转换未完成   

#define AINChanel   ADM
#define AINChanel_RST   0xe0     // bit4-bit0 是通道选择位
#define AIN0      (0)
#define AIN1			(1)
#define AIN2			(2)
#define AIN3			(3)
#define AIN4			(4)
#define AIN5			(5)
#define AIN6			(6)
#define AIN7			(7)
#define AIN8			(8)
#define AIN9			(9)
#define AIN10			(10)
#define AIN11			(11)
#define AIN12			(24)
#define AIN13			(25)
#define AIN14     (26)

//ADR寄存器：------复位状态0x00-------------全局通道控制位，ADC时钟源选择位，ADR[3..0]==ADC结果位[3..0]
     //GCHS  bit 6       1：使能AIN通道  0：禁止AIN通道 
#define ADCFruit3_0      (ADR&0x0f)
#define ADCInputEn  (4<<4)     // ADC chanel enable 全局通道使能
#define ADCInputDis  0xBF
		//ADCKS  bit[5..4]   00: Fosc/16   01: Fosc/8     10:Fosc/1   11: Fosc/2
#define ADCSpeedRST   0xCF // &=0xCF 重置ADC转化速率
#define ADC_Fosc_16   (0)
#define ADC_Fosc_8		(1<<4)
#define ADC_Fosc_1		(2<<4)
#define ADC_Fosc_2		(3<<4)
		
//ADB 寄存器： ADC转换结果的 [11:4]位
#define ADCFruit11_4      (ADB<<4)
//VREFH寄存器:-----复位状态：0x00------ 控制ADC参考电压为内部/外部  内部参考电压类型  PWM1使能位是否可以开启 ADC转换  
//                            禁止PW1M 使能ADC/   启用内部参考电压且为2.0V
  
				//ADPWS   bit 4    0:禁止PWM触发ADC开始   1：使能PWM触发ADC开始
#define PW1EnADC_En             (1<<4)
				//EVHENB bit 8   0:使用内部参考电压，P10仍然为 GPIO口   1：使用外部参考电压，AVREFH （P10） 接上外部的参考电压
#define ADCReference_Outside    (8<<4)
#define ADCReference_Inside     0x7f      
				//VHS[2]     bit 2    0:由VHS选择内部参考高压选择 位（AIN10 ） 这里AIN10指的是什么？
				// 使其为初始值0 ，这样参考电压可以让 VHS[1..0]全权控制
				//VHS[1..0]      00: 2V  01: 3V 10:4V  11:VDD
#define  ADCRef_InsideSelect_RST  0xf8    //清零 VHS【2..0】
#define  ADCRef_Inside_2V   (0)
#define  ADCRef_Inside_3V		(1)
#define  ADCRef_Inside_4V		(2)	
#define  ADCRef_Inside_VDD	(3)


//PnCON寄存器--------复位：0x00---------P2CON【1..0】  复位：0x0 ,--------0：GPIO口同时作为AIN脚 1：引脚单纯作为 AIN
//# define GPIO_P1_AINOnly  P1CON
# define GPIO_P2_AINOnly  P2CON
# define GPIO_P3_AINOnly  P3CON
# define GPIO_P4_AINOnly  P4CON
# define GPIO_P5_AINOnly  P5CON

# define P0_AIN     (1<<0)
# define P1_AIN		  (1<<1)
# define P2_AIN		  (1<<2)
# define P3_AIN		  (1<<3)
# define P4_AIN			(1<<4)
# define P5_AIN			(1<<5)
# define P6_AIN			(1<<6)
# define P7_AIN			(1<<7)

//IEN2 寄存器 复位：0-------ADC中断使能位 
//#define ADCInt_EN  (1<<3)
#define ADCInt_Dis  0xfd

//IRCON2 寄存器  复位 ：0------------bit 0----------0：无 ADC中断请求 1：ADC中断请求

#define ADCInt_Flag  (IRCON2&0x04) 
#define ADCIntFlag_Over 0x01
// ---------------------------应用函数-------------
void GetADC_Init(UINT8 ref,UINT8 speed,UINT8 inter);  // 设置 ADC 参考电压， 转换速率， 是否允许中断；
void GetADC(UINT8 io,UINT16* adcoutstore);          // 在 GetADC-init 后 获取 指定 io口的ADC 转换 值 12 位 。
//----------------------------部件函数：----------------

void ADC_ReferSet(UINT8 v);   //// （2 3 4 5-VDD） 8-外部参考；
void AIN_Channel(UINT8 a);   // 直接输入 IO口 数字号，如 P10输入 10；
void ADC_Speed  (UINT8 s);// 可以输入 1 ，2 ，8 ，16，就是FADC=Fosc/相同的值
void ADC_ENorDis(UINT8 a); //1 使能，0 禁用

// 开启 或关闭 ADC 的中断使能，// 1 开启中断， 0 中断标志位无 溢出 时  关闭中断
void ADC_IntEnableorDis(UINT8 c);  //1：开启中断， 0：关闭中断
void ADC_Start (void);             // ADC转化结束后相应位 自动重置，下次 开始ADC转换前重新 调用

UINT8 ADC_Fruit (UINT16 * AdcOutStore);// 尝试 获取ADC转换结果 存储到 AdcOutStore 指针指向的位置，获取成功返回 1，反之 0

//GPIO 口纯 AIN化函数：  // 10~17  20~21 对应 GPIO口 P10..P17 P20..P21
void GPIO_AINOnly(UINT8 Pin);
#endif