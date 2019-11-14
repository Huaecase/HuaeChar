#ifndef UART_H
#define UART_H
#include "SN8F5702.H"
#include "GenericTypeDefs.h"
#include "GPIO.h" 
//注意事项：：：：：：：：：：：：：：
//void UART_SolidCLK(UINT8 SolidCLKS);  //输入 FCPU_64  FCPU_32 ， 模式   2   （模式0 是否受控？）



//S0CON --------
#define UARTEnable (1<<5)
#define UARTDisable 0xdf


#define UartMod0  (0)
#define UartMod1	(1<<6)
#define UartMod2	(2<<6)
#define UartMod3	(3<<6)
#define UartModClear  0x3f

// IENO ----------
#define  UART_IntEn   0x90                 //开全局中断和 UART中断
#define  UART_IntDis  0xef
// S0CON2------
#define VarModelCLK_T1    (0)
#define VarModelCLK_Reg   (1<<7)
#define VarCLKSClear       0x7f
// PCON ------------------模式  0  2 时 设置波特率
#define  FCPU_64    (0)
#define  FCPU_32   (1<<7)
#define  SolideCLKSClear    0x7f  

///系统时钟相关定时器  CLKSEL  R/W

#define CLKSEL2_0  (CLKSEL&0x07)

//  PCON --寄存器  
   //SMOD  ：bit7  波特率加倍与否
	 
#define SMOD0  (PCON&=0x7f)
#define SMOD1  (PCON|=0x80)

void UART_Enable(UINT8 a);               // 1 使能 0禁用
void UART_Model(UINT8 UartModNum);     //输入 UartMod0 UartMod1 UartMod2 UartMod3  代表 模式0  1 2 3
//-----------------------------------------------------------------------------------------
void UART_SolidCLK(UINT8 SolidCLKS);  //输入 FCPU_64  FCPU_32 ，               模式   2   （模式0 是否受控？）
																			//  模式  0 的 波特率固定为 FCPU/12 
void UART_VarCLKS(UINT8 VarCLKS);    //输入：VarModelCLK_Reg    VarModelCLK_T1 ； 只对模式1  3，可变波特率有效

//     ************************!!!!!!!!!!!!!!!!!!                    针对 模式 1  3 设置 波特率函数

UINT8 UARTBaudRate(UINT32 Fosc,UINT32 BaudRate);

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//--------------------------------------------------------------------------
void UART_IntEnorDis(UINT8 k);

//--------------------------------------------------------------------------
//void UART_IOInit(void);	// 工具函数
//--------------------------------------------------------------------------

#endif