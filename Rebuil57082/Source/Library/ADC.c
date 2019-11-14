#include "ADC.h"

void GetADC_Init(UINT8 ref,UINT8 speed,UINT8 inter) //  默认输入参数 3,8,0. 3 V内部，8 速率， 关闭中断
{

  //AdcOutStore=4095;   //调试用  ，仿真后删除；
  ADC_ReferSet(ref);
  //AIN_Channel(16);
  ADC_Speed (speed);
  ADC_ENorDis(1);	 
  ADC_IntEnableorDis(inter);// 1 开启中断，0 关闭中断
}	

void GetADC(UINT8 io,UINT16 * adcoutstore)
{
	//	GetADC_Init(3,8,0);             //测试用！要删除！
	  AIN_Channel(io);
   // ADC_ENorDis(1);	             //是否要放在 通道选择函数后面
  	 ADC_Start ();
	 while(!ADC_Fruit (adcoutstore));          //// 尝试 获取ADC转换结果 存储到 AdcOutStore 指针指向的位置，获取成功返回 1，反之 0
	//	 ADC_ENorDis(0);	//  关断 ADC
}




// （2 3 4 5-VDD） 8-外部参考；
void ADC_ReferSet(UINT8 v)  
{
	VREFH&=ADCReference_Inside ;      //ADC参考电压设置位清零 ，复位状态---取内部参考电压状态；
	VREFH&=ADCRef_InsideSelect_RST;   //ADC内部参考电压通道选择 位清零      
	switch(v)
	{
		case 2:
			VREFH |= ADCRef_Inside_2V ;
		break;	
		
		case 3:
			VREFH |= ADCRef_Inside_3V ;
		break;
			
		case 4:
			VREFH |= ADCRef_Inside_4V ;
		break;
			
		case 5:
			VREFH |= ADCRef_Inside_VDD ;
		break;
		// 以上为内部参考电压，case 8 是外部 参考电压；
		case 8:
			VREFH |= ADCReference_Outside	;
			GPIO_AINOnly(54);//对应 外部输入引脚 纯AIN化 函数！！！！！！！！！！！！！！！！！！！！！！！！！！！
		break;	
		default:
				VREFH |= ADCRef_Inside_3V ;
		break;
	}
}

// 输入 作为 AIN脚的 GPIO 脚, 可以输入 40 46 47 50 51 52 53
//      未曾写 AINn作为输入的代码  或者 AIN？？(AINn输入可能与IO号相重复)
//                                优先输入 IO 口 号

void AIN_Channel(UINT8 a)
{
 AINChanel &= AINChanel_RST;
	switch(a)
	{
		case 40:	
			AINChanel |=AIN0; 
			GPIO_AINOnly(40);
		break;
	
		case 46:	
			AINChanel |=AIN6;
			GPIO_AINOnly(46);
		break;
			
		case 47:
			AINChanel |=AIN7;		
			GPIO_AINOnly(47);
		break;
		
		case 50:
			AINChanel |=AIN8; 		
			GPIO_AINOnly(50);
		break;
		
		case 51:
			AINChanel |=AIN9 ;		
			GPIO_AINOnly(51);
		break;
		
		case 52:
			AINChanel |=	AIN10;		
			GPIO_AINOnly(52);
		break;
		
		case 53:
			AINChanel |=	AIN11;		
			GPIO_AINOnly(53);
		break;
//		
//		case AIN:
//			AINChanel |=	AIN ;		
//			GPIO_AINOnly();
//		break;
		
		default :		
		break;	
	}		
}
//***********************ADC转换速率选择函数***********************
//*****************************************************************

void ADC_Speed  (UINT8  s)
{
	ADR&=ADCSpeedRST; //清零代码位置*/
	switch (s)
	{
		case 1:
				ADR |=ADC_Fosc_1;
				break;
			
			case 2:
				ADR |=ADC_Fosc_2;
				break;
			
			case 8:
				ADR |=ADC_Fosc_8;
				break;
			
			case 16:
				ADR |=ADC_Fosc_16;
				break;
			
			default:
				ADR |=ADC_Fosc_1;
				break;
	}
}


//**************************ADC全局使能控制函数*****************************************
//******************************************************************************
//1:使能 ADC ，0: 禁用ADC

void ADC_ENorDis(UINT8 a)
{
  if (a)
	{
		ADM|=ADCEnable;
		ADR|=ADCInputEn;
	}
	else
	{
		ADM &=ADCDisable;
		ADR &=ADCInputDis;
	}
}

//****************ADC中断控制函数********************************************************
//***************************************************************************************
//1：开启中断， 0：关闭中断

void ADC_IntEnableorDis(UINT8  c)
{
	if (c)
	{
        IEN2 |= (1<<3);	 // ADC中断使能	
				//IRCON2 &=ADCIntFlag_Clear;//开启 ADC中断 使能 需要 清除中断标志位么	
        IEN0 |= 0x80;     // 开启全局中断
	}
  else   //试图 关闭中断
	{   
				IEN2   &=0xf7 ;		 // 清除ADC中断使能
				IRCON2 &=0xfb;		  // 清除ADC中断溢出位 
	}
}
//***************ADC开始函数*******************************************************
//*********************************************************************************

void ADC_Start (void)
{
	ADM|=ADCStart;    //转换结束后 ，硬件自动清零该位；
}

//*************获取ADC转换结果函数**************************************************
//**********************************************************************************

UINT8 ADC_Fruit (UINT16 * AdcOutStore)
{
	if(ADCStatus==ADC_TransOk) 
	{
		*AdcOutStore=(ADCFruit11_4+ADCFruit3_0);
		ADM &=ADCStatus_Clear;//清除EOC位			
		return 1;
	}
	else //转换未完成
		return 0;	
}




//GPIO 口纯 AIN化函数：  // 24-27 30-37 40-47 50-55

void GPIO_AINOnly(UINT8 Pin)
{
		GPIO_In(Pin);   //输入模式
		GPIO_NoUp(Pin); //非上拉   
  switch(Pin)
	{
		case 40:
			GPIO_P4_AINOnly |=P0_AIN;
//			 GPIO_In(40); //输入模式
//		   GPIO_NoUp(40); //非上拉     输入管脚由Pin 决定，所以放到switch外
		break;
		
		case 46:			
			GPIO_P4_AINOnly |=P6_AIN; 
		break;		
		
		case 47:
			GPIO_P4_AINOnly |=P7_AIN;
		break;
			
		case 50:
			GPIO_P5_AINOnly |=P0_AIN;
		break;
		
		case 51:
			GPIO_P5_AINOnly |=P1_AIN;
		break;
	
		case 52:		
			GPIO_P5_AINOnly |=P2_AIN;
		break;
		
		case 53:		
			GPIO_P5_AINOnly |=P3_AIN;
		break;
		
		default:			
		break;	
	}
}