#include "PWM.h"
//!!!!!!!!!!!!!!!!!!!!!!!

//设置PWM1 周期占空比的函数 强制类型转换是否正确？
//----------------------PWM1 应用函数-------------------------------------------------
void PWMn_Out_Init(UINT8 PWMn,UINT16 Circle,UINT8 Dutynum,UINT8 Intter,UINT8 io)
{
	PWMn_ValueDuty(PWMn,Circle,Dutynum);
	PWMn_Fpwm(PWMn,1);       //FPWM1=Fosc/1			
	PWMChanelPin_EnorNot(io,1);   //设置PWM输出管脚
	PWMn_IntEnableorDis(PWMn, Intter);  //控制 PWMn中断	  
}

// Function ： PWMn 使能控制 
//修改完成
void PWMn_EnorDis(UINT8 PWMn,UINT8  d)
{
	switch (PWMn)	
	{
	  case 1:
		{
			if (d)
				P1OC|=PWM1En;
			else
				P1OC&=(~PWM1En);			 
		}	
		break;
		
		case 2:
		{
			if (d)
				P1OC|=PWM2En;
			else
				P1OC&=(~PWM2En);	
		}
		break;
		
		case 3:
		{
			if (d)
				P1OC|=PWM3En;
			else
				P1OC&=(~PWM3En);		
		}
		break;
		
	}
	
}

//--------------------------------------------------------------------------------------

//void PWMn_RST(UINT8 PWMn)
//{
//	switch(PWMn)
//	{
//		case 1:
//		{
//		 PW1M=PWM_RSTVALUE;
//		}
//		break;

//		case 2:
//		{
//			PW2M=PWM_RSTVALUE;
//		}
//		break;
//		
//		case 3:
//		{
//			PW3M=PWM_RSTVALUE;	
//		}
//		break;
//	}
//  
//}
//-----------------------清除PW1MRATE 的数据位
//void PWMnRate_clear(UINT8 PWMn)
//{
//	switch(PWMn)
//	{
//		形如：1-3
//		case n :
//			PWnM &=PWMRateCLR;
//		break;
//	}
//}



// 参数 1： 1~3 代表 PWM1~PWM3, 有 1 2 8 16 32 64 128 这些分频可选
//修改完成
void PWMn_Fpwm(UINT8 PWMn,UINT8 FCPUtoFPWM_Div) // 几分频就输入几
{
	switch(PWMn)
	{
		case 1:  // PWM1
		{
				PW1M &=PWMRateCLR;
				switch (FCPUtoFPWM_Div)
				{
					case 1:
						PW1M |=Fosc_1	;
					break;

					case 2:
						PW1M |=Fosc_2;
					break;

					case 4:
						PW1M |=Fosc_4;
					break;

					case 8:
						PW1M |=Fosc_8;
					break;

					case 16:
						PW1M |=Fosc_16;
					break;

					case 32:
						PW1M |=Fosc_32;
					break;

					case 64:
						PW1M |=Fosc_64;
					break;

					case 128:
						PW1M |=Fosc_128;
					break;

					default:
						PW1M |=Fosc_1;
					break;
					}
		}
		break;

		case 2:// PWM2:
		{
				PW2M &=PWMRateCLR;
				switch (FCPUtoFPWM_Div)
				{
					case 1:
						PW2M |=Fosc_1	;
					break;

					case 2:
						PW2M |=Fosc_2;
					break;

					case 4:
						PW2M |=Fosc_4;
					break;

					case 8:
						PW2M |=Fosc_8;
					break;

					case 16:
						PW2M |=Fosc_16;
					break;

					case 32:
						PW2M |=Fosc_32;
					break;

					case 64:
						PW2M |=Fosc_64;
					break;

					case 128:
						PW2M |=Fosc_128;
					break;

					default:
						PW2M |=Fosc_1;
					break;
					}
		}
		break;

		case 3: //PWM3:		
		{
				PW3M &=PWMRateCLR;
				switch (FCPUtoFPWM_Div)
				{
					case 1:
						PW3M |=Fosc_1	;
					break;

					case 2:
						PW3M |=Fosc_2;
					break;

					case 4:
						PW3M |=Fosc_4;
					break;

					case 8:
						PW3M |=Fosc_8;
					break;

					case 16:
						PW3M |=Fosc_16;
					break;

					case 32:
						PW3M |=Fosc_32;
					break;

					case 64:
						PW3M |=Fosc_64;
					break;

					case 128:
						PW3M |=Fosc_128;
					break;

					default:
						PW3M |=Fosc_1;
					break;
					}
		}
		break;


		
	}
}

// 该函数 失效 死区控制，仅仅输入 用来控制PWMn的 周期 以及占空比 的 数值；
//修改完成
void PWMn_ValueDuty(UINT8 PWMn,unsigned long a,int duty) //导入 PWMn	的初始值 以及占空比；
{		
	switch(PWMn)
	{
		case 1:
		{
			 PW1YH = (unsigned char)(a/256);
			 PW1YL = (unsigned char)(a%256);
			 if (duty<=0)
				{
					PW1DH=0;
					PW1DL=0;
				}
			 else if (duty>=100)
				{
					PW1DH=PW1YH;
					PW1DL=PW1YL;
				}
			 else
			 {
				  PW1DH=(unsigned char )(a*duty/100/256);
				  PW1DL=(unsigned char )((unsigned long)(a*duty/100)%256);
				 }
				PW1BH = PW1DH;						    // The dead band control : B point > A point (Must)
			PW1BL = PW1DL;           			// B point dead band control  PW1B控制保留输出的 PW1D	 
			PW1A  = 0x00;            			// A point dead band control PW1A 减少 PW1B 时间
			}
		break;
	
		case 2:
		{
			 PW2YH = (unsigned char)(a/256);
			 PW2YL = (unsigned char)(a%256);
			 if (duty<=0)
					{
							PW2DH=0;
							PW2DL=0;
					}
			 else if (duty>=100)
					{
							PW2DH=PW2YH;
							PW2DL=PW2YL;
					}
			 else
			 {
						PW2DH=(unsigned char )(a*duty/100/256);
						PW2DL=(unsigned char )((unsigned long)(a*duty/100)%256);
			 }
			PW2BH = PW2DH;						    // The dead band control : B point > A point (Must)
			PW2BL = PW2DL;           			// B point dead band control  PW1B控制保留输出的 PW1D	 
			PW2A  = 0x00;            			// A point dead band control PW1A 减少 PW1B 时间
		}
		break;
		
		case 3:
		{
			 PW3YH = (unsigned char)(a/256);
			 PW3YL = (unsigned char)(a%256);
			 if (duty<=0)
					{
							PW3DH=0;
							PW3DL=0;
					}
			 else if (duty>=100)
					{
							PW3DH=PW3YH;
							PW3DL=PW3YL;
					}
			 else
			 {
						PW3DH=(unsigned char )(a*duty/100/256);
						PW3DL=(unsigned char )((unsigned long)(a*duty/100)%256);
			 }
			PW3BH = PW3DH;						    // The dead band control : B point > A point (Must)
			PW3BL = PW3DL;           			// B point dead band control  PW1B控制保留输出的 PW1D	 
			PW3A  = 0x00;            			// A point dead band control PW1A 减少 PW1B 时间
		}
		break;
	}	  
}


// 开启 或关闭 PWMn 的中断使能   // 1 开启中断， 0  关闭中断
//修改完成
void PWMn_IntEnableorDis(UINT8 PWMn, UINT8  c)
{
	
	switch(PWMn)
	{
		case 1:   // 控制 PWM1 中断
		{
				if (c)
				{	
						IEN4 |= 0x80;			
						IEN0 |= 0x80;
				} 
			else   //试图 关闭中断
				{   		
						IEN4 &= 0x7f;     // 清除PW1中断使能位	
				}    
		}
		break;
	
		case 2: // 控制 PWM2 中断
		{
			if (c)
				{	
						IEN2 |= 0x02;			
						IEN0 |= 0x80;
				} 
			else   //试图 关闭中断
				{   		
						IEN2 &= 0xfd;     // 清除PW2中断使能位	
				}   
		}
		break;
		
		case 3:  // 控制 PWM3 中断
		{
			if (c)
				{	
						IEN2 |= 0x04;			
						IEN0 |= 0x80;
				} 
			else   //试图 关闭中断
				{   		
						IEN2 &= 0xfb;     // 清除PW3中断使能位	
				}  
		}
		break;
	}

}
// *******************通道选择 函数：  自己用语句打开通道吧 *******************************
		// PW1 chanel 使能方法？ PW1Chanel |=PWM10_P05En，禁用 方法： PW1Chanel &=PWM10_P05Disable;
//**********************************************************************************************

// PW1 chanel 使能方法？ PW1Chanel |=PWM10_P05En，禁用 方法： PW1Chanel &=PWM10_P05Disable;
//   d 为1 启用 
//修改完成
void PWMChanelPin_EnorNot(UINT8 Pin,UINT8 d)
{
	switch(Pin)
	{
		case 46:
			if(d)
			{PW1M |=PWMCH0 ; GPIO_Out(46);  }//添加GPIO口为输出端口
			else
			{PW1M &= (~PWMCH0);}
		break;

		case 47:
			if(d)
			{PW1M |=PWMCH1 ;  GPIO_Out(47);  }
			else
			{PW1M &=(~PWMCH1);}			
		break;
				
		case 50:
			if(d)
			{PW2M |=PWMCH0  ;  GPIO_Out(50);  }
			else
			{PW2M &=(~PWMCH0);}
		break;
		
		case 51:
			if(d)
			{PW2M |=PWMCH1 ; GPIO_Out(51);  }
			else
			{PW2M &= (~PWMCH1);}
		break;
			
		case 52:
			if(d)
			{PW3M |=PWMCH0 ;  GPIO_Out(52);  }
			else
			{PW3M &= (~PWMCH0);}
		break;
			
		case 53:
			if(d)
			{PW3M |= PWMCH1 ;  GPIO_Out(53);  }
			else
			{PW3M &=(~PWMCH1) ;}
		break;
		
	  default:
			break;
	}
}


