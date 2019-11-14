#include "UART.h"

这个针对 570212 写的，
//	S0RELH= SOREL/256;             //计算好的值 放入相应的寄存器； S0RELH [7..2] 位保留位 赋值是否会错误？

//#define UARTEnable (1<<5)
//#define UARTDisable 0xdf
void UART_Enable(UINT8 a)  // 1 使能 0禁
{
 if (a)
	 S0CON|=UARTEnable;
 else 
  S0CON&=UARTDisable;
}
//#define UartMod0  (0)
//#define UartMod1	(1<<6)
//#define UartMod2	(2<<6)
//#define UartMod3	(3<<6)
//#define UartModClear  0x3f
void UART_Model(UINT8 UartModNum) //输入 0x00; 0x40; 0x80;0xc0; 代表 模式0  1 2 3
{
	S0CON&=UartModClear;
  S0CON |=UartModNum;
	if(UartModNum==UartMod0)  //同步模式 下 
	{
		GPIO_OUT(05);   
		GPIO_OUT(06);   // CLK    （ URX ）
	}
	else 
	{
		GPIO_OUT(05);  //UTX 
		GPIO_In(06);   //URX
	}
	P05=1;  //(UART 协议要求)
	P06=1;  //  （开发手册要求？）       ！！！！！！！！！！是否正确？？？？    ！！！！！！！！！！************
	
}

//void UART_IOInit(void)
//{
//	GPIO_In(06);    //URX 
//	GPIO_OUT(05);  //UTX
//	//P06=0;// 是否要求为0？
//	P05=1;//(UART协议要求)
//	//P0OC 开漏控制寄存器 使用默认初始值

//}
// S0CON2------
//#define VarModelCLK_T1    (0)
//#define VarModelCLK_Reg   (1<<7)
void UART_VarCLKS(UINT8 VarCLKS)//只对模式1  3，可变波特率有效  输入：VarModelCLK_Reg    VarModelCLK_T1 ；
{
	S0CON2&=VarCLKSClear;
  S0CON2|=VarCLKS;
}


//#define  FCPU_64    (0)
//#define  FCPU_32   (1<<7)
//#define  SolideCLKSClear    0x7f   
void UART_SolidCLK(UINT8 SolidCLKS) //，模式0  2    输入 FCPU_64  ，， FCPU_32 
{
	PCON&=SolideCLKSClear;
	PCON|=SolidCLKS;
}
//#define  UART_IntEn   0x90                 //开全局中断和 UART中断
//#define  UART_IntDis  0xef

void UART_IntEnorDis(UINT8 k)
{
	if (k)
	{
	  IEN0|=UART_IntEn ;
	}
	
	else
		IEN0&=UART_IntDis;
}

// 设置1 3  模式下的 目标波特率，     
UINT8 UARTBaudRate(UINT32 Fosc,UINT32 BaudRate)  // 参数1： Fosc  振荡频率， 参数2： 目标 波特率
{
 UINT32 FCPU;
 UINT32 SOREL;

	switch (CLKSEL2_0)   //CLKSEL2_0 是FOSC到 FCPU的 分频系数控制位
  {
	  case 0:
			FCPU=Fosc/128 ;
			break;
		case 1:
			FCPU=Fosc/64 ;
			break;
		case 2:
			FCPU=Fosc/32 ;
			break;
		case 3:
			FCPU=Fosc/16; 
			break;
		case 4:
			FCPU=Fosc/8; 
			break;
		case 5:
			FCPU=Fosc/4; 
			break;
		case 6:
			FCPU=Fosc/2 ;
			break;
		case 7:
	    FCPU=Fosc/1 ;
			break;
	  default:
			return 0;
		break;
	}
	if(BaudRate < (FCPU/(2^16))||BaudRate> (FCPU/(2^5)))
	   return 0;                          // 超出可设置波特率边界；	
	else	
	{
		if (BaudRate> (FCPU/(1<<7)) )//必须设置  SMOD=1； 加倍 波特率：
		{
			SMOD1;
			SOREL=1024-FCPU/(BaudRate*32);
			
		}
		else // 使 SMOD=0 来取较低范围的 波特率
		{
			SMOD0;
			SOREL=1024-FCPU/(BaudRate*64);
		}
		S0RELH= SOREL/256;             //计算好的值 放入相应的寄存器； S0RELH [7..2] 位保留位 赋值是否会错误？
		S0RELL= SOREL%256;
	  return 1;
	}
}