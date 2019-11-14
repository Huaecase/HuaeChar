#include "IIC.h"

//I2CCON 的 ENS1位是不是需要写 1才能访问 IIC相关寄存器？
// IIC_INTRate 仅仅支持部分 数值！！！！！！！！！！！！！！
// 设置相对应的SDA、SCL  IO口为输入模式、上拉！！要上拉么？

void  IIC_IO_SEL(UINT8 SCL,UINT8 SDA)  
{
	// 硬件IIC
	GPIO_In(SCL);
	GPIO_In(SDA);
	//硬件IIC
	
	GPIO_Up(SCL);
	GPIO_Up(SDA);
}
void IIC_EnDis(UINT8 b)
{
	if (b)
		I2CCON |=0x40;
	else
		I2CCON &=bf;	
}

UINT8 IIC_INTRate(UIN16 FcpuDiv)//如果选择 Timer1 溢出率/8将最高 2的16次方再乘8 个时钟周期，
//避免麻烦这里仅仅用
//FCPU 分频产生 IIC的中断周期

{
	I2CCON &=0x7c;
	switch(FcpuDiv)
	{
		case 256:
		{
			I2CCON |=0;
			return 1;
			
		}
		case 224:
		{
			I2CCON |=1;
			return 1;
		}
		case 192:
		{
			I2CCON |=2;
			return 1;
		}
		case 160:
		{
			I2CCON |=3;
			return 1;
		}
		case 960:
		{
			I2CCON |=8;
			return 1;
		}
		case 120:
		{
			I2CCON |=9;
			return 1;
		}
		case 60:
		{
			I2CCON |=10;
            return 1;			
		}
		default:
		return 0;		
	}
}


void IIC_Interr_EnDis(UINT8 b)
{
	if(b)
	{		
		EAL=1;  //全局中断控制
		EI2C=1; //IIC中断控制
	}
	else
	{
		EI2C=0;		
	}
	
}

void IIC_Interrupt(void) interrupt ISRI2c   //0x43
{
//#define   IIC_STA      (I2CSTA&0xf8)  //避免 SMBus状态字的影响
//-----------------主机发送模式-------------------
//#define   MasStartT_SlaR        0x08
//#define   MasReStartTran_SlaRW  0x10
//#define   MasSlaWTAck_WData     0x18 

  
//#define   MasSlaWTNAck_WData    0x20
//#define   MasDATTAck_WData      0x28
//#define   MasDATTNAck_WData     0x30
switch(IIC_STA)
	{
		case  MasStartT_SlaR:
		{
			
		}
		break;
		
		case MasReStartT_SlaRW:
		{
			
		}
		break;
		
		case MasSlaWTAck_WData :
		{
			
		}
		break;
		
		case  MasSlaWTNAck_WData :
		{
			
		}
		break;
		
		case MasDATTAck_WData :
		{
			
		}
		break;
		
		case MasDATTNAck_WData
		{
			
		}
		break;
	}
}


//未测试可用与否：
//void IIC_WR_SMBusTimOutReg_DataEnDis(UINT8 SMBusRegNum,UINT8 Data,UINT8 c)
//{
//	if(c)
//	{
//		if(0<=SMBusRegNum&&SMBusRegNum<=7)
//		{
//			SMBSEL|=(0x80|SMBusRegNum);
//			SMBDST=Data;			
//		}		
//	}
//	else
//	{
//		SMBSEL&=0x7f;	
//	}	
//}