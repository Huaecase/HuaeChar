#include "Charge.h"
#include "OLED.h"  //调用延时函数


UINT16 idata AdcOutStore;      //=0x0fff;													//UINT8 ifadcrun=0;
PID ChargePWM;                //结构体变量
BiFilter idata ButterFilter; // 巴特沃斯滤波
ChargeMode_E ChargeMode;    // 枚举变量 

// ---------------------用于 脉冲充电阶段的 变量定义
UINT8 idata PoscirNum;
UINT8 idata NegcirNum;
UINT8 idata Timecircles=0;  //  T0  周期计数器
UINT8 idata OldTsignal;
UINT8 idata Tsignal=0;

float BatPos_Value,BatNeg_Value; // 电池 正负极电压值；
float idata   Now_I=0;           // 当前电流值

// 用于 脉冲恒流的 参数；
PID   idata ImpulseConstI_PID; 
UINT8 idata Xorbit=0;
UINT8 idata TimeSemiCirNum=0;
UINT8 idata ImpulsePart=0;
float idata Impulse_ConstI=0.0;

// 用于 Bug 
UINT8 idata i=0, BugNum=0;

//***********************************************************************************************
//***********************************************************************************************
//***********************************************************************************************
void charge_init(void) 
{
	GetADC_Init(ADC_InterRef,8,0); //配置ADC 参考电压、 Fosc到ADC时钟的分频系数、								      // 关闭中断	
    BiFilter_LP_Init(&ButterFilter);//初始化 巴特沃斯 滤波结构体
	
	ChargePWM_PIO=0;// 充电口GPIO时 为 0，初始化时为0
	// 不启用 PWM中断
	PWMn_Out_Init(ChargePWMn,PWM_Circle,PW1M_InitDuty,DisPwmInt,ChargePWM_IO);
	PID_init(&ChargePWM,Akp,0,0);    //PID参数
	
	//配置定时器:+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+	
	PoscirNum=PoscirNumInit ;
	NegcirNum=NegcirNumInit ;
	TimeConPulseInit(Timer0,5535,TimeMod_1 , TimeIntEn);
	
	PID_SetValue(&ChargePWM,ConstI);     // 测试用 。
	ChargeMode=ConstCurrent;//ImPulse;//DisConnect;//ChargeMode=;  DisConnect;
	
	//测试打开：
	T0ENorDis(1);
	PWMn_EnorDis(ChargePWMn ,1); //直接开启 PWM+-+-+-+-+-+-+-+-+-+-+-+-+	
}
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+	
void charge_ing(void)
{
	switch(ChargeMode)
	{	
		case ConstCurrent:
		{
			//PID_SetValue(&ChargePWM,ConstI);  //  想维持的电流值。		
			//读值 调整PID：	
			BatPos_Value=2.0*GetVoltage (VBatH); 
			BatNeg_Value=GetVoltage (VBatL);
			Now_I=divider( BatNeg_Value, I_Resist );	
			PID_Inc(&ChargePWM,Now_I); 
			//执行调整：
//PWMn_ValueDuty(ChargePWMn ,PWM_Circle,ChargePWM.output);
			PWMn_ValueDuty(ChargePWMn ,PWM_Circle,70);
	
			// 安全：
//		   if( Now_I>(1.5*ConstI)||BatPos_Value>(BatFullV+0.9))
//				ChargeMode=Bug;
//			
//			else if( (BatPos_Value-BatNeg_Value)<BatexistV  )
//				ChargeMode=DisConnect;
////			
			if((BatPos_Value-BatNeg_Value)>=BatFullV)
				{
//					if(ChargePWM.SetValue==ConstI)
//					{
//						PID_SetValue(&ChargePWM,ConstI/1.6);
//						break;				
//					}
//					//else {	
//						PID_init(&ChargePWM,Akp,Aki,Akd);   //重设 ChargePWM PID 结构体 kp ,ki,kd 参数,恒流阶段的误差 也 重置为0；
//						// 开启 时钟 指示：
//		//				TimeConPulseInit(Timer0,5535,TimeMod_1 , TimeIntEn);
//		//			    T0ENorDis(1);
//						ChargeMode=ImPulse;
//		//				}
				}
						
			break;
		}

		
		case DisConnect:
		{
			charge_close();
			PWMn_EnorDis(ChargePWMn ,0); //直接 关闭 PWM	
			
			// 获取电池端 电压
			BatPos_Value=2.0*GetVoltage (VBatH); // 经过分压电阻
			BatNeg_Value=GetVoltage (VBatL);
			
			if((BatPos_Value-BatNeg_Value)>BatexistV) //电池存在判定需要多少压差？
				ChargeMode=ConnectPrimer;		
			break;
		}
		case ConnectPrimer:
		{
			// 获取电池端 电压
			BatPos_Value=2.0*GetVoltage (VBatH); // 经过分压电阻
			BatNeg_Value=GetVoltage (VBatL);
			
			if( (BatPos_Value-BatNeg_Value)>BatFullV )
			{	
				ChargeMode=Bug;
				break;
			}
			
			else if((BatPos_Value-BatNeg_Value)< BatexistV )
			{
				ChargeMode=DisConnect;
				break;
			}
			
			else if( (BatPos_Value-BatNeg_Value)==BatFullV)
			{		
		     	ChargeMode=FullCharge;	
				break;
			}
			
			else if( (BatPos_Value-BatNeg_Value)< PreChargeUp)
			{
				PID_init(&ChargePWM,Akp,Aki,Akd);   //重设 ChargePWM PID 结构体 kp ,ki,kd 参数,要调整
				ChargeMode=PreCharge;
			}
			
			else if( ((BatPos_Value-BatNeg_Value)>=PreChargeUp)&&((BatPos_Value-BatNeg_Value)<ConstV))
			{
				PID_init(&ChargePWM,Akp,Aki,Akd);   //重设 ChargePWM PID 结构体 kp ,ki,kd 参数,要调整
				PID_SetValue(&ChargePWM,ConstI);  //  想维持的电流值。
				ChargeMode=ConstCurrent;
			}
			
			else if( ((BatPos_Value-BatNeg_Value)>=ConstV)&&((BatPos_Value-BatNeg_Value)<BatFullV))
			{
				PID_init(&ChargePWM,Akp,Aki,Akd);   //重设 ChargePWM PID 结构体 kp ,ki,kd 参数,要调整
				ChargeMode= ImPulse;
			
			}		
			PWMn_EnorDis(ChargePWMn ,1); //直接 开启 PWM	
          		
			break;
		}
		
		case PreCharge:    //
		{			
			PID_SetValue(&ChargePWM,PreCharge_ConstI);  //  想维持的电流值。
			
		    // 获取电池端 电压 ， 调整 PID：
			BatPos_Value=2.0*GetVoltage (VBatH); // 经过分压电阻
			BatNeg_Value=GetVoltage (VBatL);		
			Now_I=divider( BatNeg_Value, I_Resist );
			
			PID_Inc(&ChargePWM,Now_I);

			PWMn_ValueDuty(1,PWM_Circle,ChargePWM.output);  // 执行调整;

		    //安全：
			if( (BatPos_Value-BatNeg_Value)== PreChargeUp )
			{
				PID_init(&ChargePWM,Akp,Aki,Akd);   //重设 ChargePWM PID 结构体 kp ,ki,kd 参数,要调整
				PID_SetValue(&ChargePWM,ConstI);  //  想维持的电流值。
				ChargeMode=ConstCurrent;
			
			}
				
			else if((BatPos_Value-BatNeg_Value)>=ConstV ||(Now_I > 2*PreCharge_ConstI))
				ChargeMode=Bug;
			else if((BatPos_Value-BatNeg_Value)< BatexistV )	
				ChargeMode=DisConnect;
			
			 break;
		}
			

		
		case ImPulse :
		{
			//PID_init(&ChargePWM,Akp,Aki,Akd);   //PID参 放到case外		
			//T0ENorDis(1);
						
			 if (Xorbit!=Tsignal)           // 方波Tsignal 1 - 0 变化
				{ 
					Xorbit=!Xorbit; 
					if (TimeSemiCirNum>1)      //此时应该进入 关闭充电状态；
					{
						TimeSemiCirNum-=1; 
						ImpulsePart= 0;  
					}
						
					else					// 此时应该进入 充电部分：
					{
						if (TimeSemiCirNum>0)
							TimeSemiCirNum-=1; 
						ImpulsePart=1;
					} 
				}

			if(ImpulsePart) //此时 恒流  充电。
			{	
			   if(!TimeSemiCirNum)
			   {
					if (Impulse_ConstI <0.001) // 此时 应该算是充满电了，就把模式换到FullCharge, 
					{
						ChargeMode=FullCharge;
						break;
					}
					else  //还可以继续在 ImPulse 阶段；
					{
						if((BatFullV - BatPos_Value + BatNeg_Value)>0.001)
							TimeSemiCirNum=2;
						else
							TimeSemiCirNum=2+(UINT8)((1-Impulse_ConstI)*5); //设置 脉冲 恒流为 0 阶段的定时器方波半周期数    
					}
						
			   }
			
				
				//读值 调整PID：
				BatPos_Value=2.0*GetVoltage (VBatH); 
				BatNeg_Value=GetVoltage (VBatL);
				Now_I=divider( BatNeg_Value, I_Resist );
			   
				PID_Inc(&ChargePWM,Now_I); 
				//执行调整：
				PWMn_ValueDuty(ChargePWMn ,PWM_Circle,ChargePWM.output);
			   
				// 安全：
			    if( Now_I>(2*ConstI)||BatPos_Value>(BatFullV+0.7))
				{
					ChargeMode=Bug;
				}
					
			}    //End of  恒流充
			
			else // (ImpulsePart= 0) 关闭充电，很多个 方波 半周期
			{		
				charge_close();
				BatPos_Value=2.0*GetVoltage (VBatH); 
				BatNeg_Value=GetVoltage (VBatL);
				
				Impulse_ConstI= 25*(BatFullV - BatPos_Value + BatNeg_Value);    // 或许可以用上一个  PID 控制		
				if (Impulse_ConstI>0)  //没有充满；
				{	
					if (Impulse_ConstI>1)
						Impulse_ConstI=1; //修正 电流过大
					PID_SetValue(&ChargePWM,Impulse_ConstI);
				}
				
				else if(Impulse_ConstI<0 && TimeSemiCirNum< 2 )  //经过关闭后一段延时，还这样说明满了或者过充了
				{
					ChargeMode=FullCharge;
					break;
				}

			// 安全：
			if(BatPos_Value>(BatFullV+0.3))
				ChargeMode=Bug;
				
			}
			// 安全 或 充满；	
//			if( (BatPos_Value-BatNeg_Value)<BatexistV  )
//				ChargeMode=DisConnect;
//			
			break;
		}
		
		case FullCharge:
		{
			charge_close();
			
//			BatPos_Value=2.0*GetVoltage (VBatH); 
//			BatNeg_Value=GetVoltage (VBatL);
			BugNum=0;
			for (i=0;i<5;i++)
			{
				BatPos_Value=2.0*GetVoltage (VBatH); 
				BatNeg_Value=GetVoltage (VBatL);
			
				if( BatPos_Value-BatNeg_Value<BatexistV  )
					{
						ChargeMode=DisConnect;		
						break;
					}
				else if(BatPos_Value-BatNeg_Value>BatFullV+0.01)
					{
						ChargeMode=Bug;		
						break;
					}
				
				else if(( BatPos_Value-BatNeg_Value>PreChargeUp )&&(BatPos_Value-BatNeg_Value<ConstV)&&(i>=4))
				{
					PID_init(&ChargePWM,Akp,Aki,Akd); 
					PID_SetValue(&ChargePWM,ConstI); 
					ChargeMode=ConstCurrent;
				}
				
				
				else if(( BatPos_Value-BatNeg_Value> ConstV)&&(i>=4)&&( BatPos_Value-BatNeg_Value<BatFullV))
					
				{
					PID_init(&ChargePWM,Akp,Aki,Akd); 
					ChargeMode=ImPulse;
				
				}
				
			}			
			break;
		}

  	
		case   Bug:  //UINT8 idata i, BugNum;
		{
			charge_close();
			
			if (i<200)
				i++;
			else 
			{
				i=0;
				BugNum=0;
			}

				BatPos_Value=2.0*GetVoltage (VBatH); 
				BatNeg_Value=GetVoltage (VBatL);
			
				if( BatPos_Value-BatNeg_Value<BatexistV  )
					{
						ChargeMode=DisConnect;		
						break;
					}
				else if(( BatPos_Value-BatNeg_Value>PreChargeUp )&&(BatPos_Value-BatNeg_Value<ConstV)&&(i>198)&&(BugNum==0))		
				{
					PID_init(&ChargePWM,Akp,Aki,Akd); 
					PID_SetValue(&ChargePWM,ConstI); 
					ChargeMode=ConstCurrent;
					break;
				}	
			
				else if( (BatPos_Value-BatNeg_Value==BatFullV)&&(i>198)&&(BugNum==0))
					ChargeMode=FullCharge;
				else if(BatPos_Value-BatNeg_Value>BatFullV)
					BugNum++;
				

			break;
		}
		
		case  ConstVoltage:
		{
			PID_SetValue(&ChargePWM,ConstV);  //  想维持的电压）值。
			
			//调整PID：
		    charge_close(); //关闭PWM用于测量电池电压。
			delay(500);
			
			BatPos_Value=2.0*GetVoltage (VBatH); // 经过分压电阻
			BatNeg_Value=GetVoltage (VBatL);

			PID_Inc(&ChargePWM,BatPos_Value-BatNeg_Value); //  输入 实际的（电压）值来更改PID的 output 期望值；
			
			// 执行调整：
			PWMn_ValueDuty(ChargePWMn ,PWM_Circle,ChargePWM.output);

			//安全：
//			if( (BatPos_Value-BatNeg_Value)	< PreChargeUp ||(BatPos_Value-BatNeg_Value)	>BatFullV )// 充电异常检测？？？
//				ChargeMode=Bug;		
//			else if((BatPos_Value-BatNeg_Value)	<BatexistV  )  // 怎样 判定  断开连接
//				ChargeMode=DisConnect;
			
			break;
		}
		
	default:
			break;
	}
	
}




//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
float GetVoltage (UINT8 io)
{
	UINT8 i;
	float Voltage;
//	float MeanADC=0;
	
	for (i=0;i<30;i++)        //前些部分 ，用来读取上一个通道的  残留 ADC 值；
		{
			GetADC(io,&AdcOutStore);	
		}  
//	for (i=0;i<40;i++)        //40个采样点IIR滤波；
//		{
//			GetADC(io,&AdcOutStore);	
//			 MeanADC+=AdcOutStore/40.0;
//		}
	 Voltage=ADC_InterRef *divider(AdcOutStore,4095);   //内部参考电压* ADC的百分比
//	  Voltage=ADC_InterRef *divider(MeanADC,4095); 
	return Voltage;
}

double divider(double adc,double div)   // 除法函数
{
 double num=-1;
 if (div!=0)
    num=adc/div;
 return num;
}


void charge_close(void)
{
	// 0 占空比的PWM：
	PWMn_ValueDuty(ChargePWMn,PWM_Circle,0);
}

//***********************************************************************************************
//***********************************************************************************************

//-------------T 0 中断服务函数： 用于脉冲充电阶段  ----------------
void T0Interrupt(void) interrupt ISRTimer0 //0x0B
{ //TF0 clear by hardware

	if(Timecircles<(PoscirNum+NegcirNum))
		Timecircles+=1;
	else
		Timecircles=0;
		
	OldTsignal=Tsignal;
		
	if(Timecircles<PoscirNum)
		
		Tsignal=1;

	else
		Tsignal=0;	
}

//void CharModChange(ChargeMode_E* ChargeMode,float PosV,float NegV,PID *ChargePWM )
//{
//	switch (ChargeMode)
//	{
//		case  DisConnect:
//		{
//			if((BatPos_Value-BatNeg_Value)>BatexistV) //电池存在判定需要多少压差？
//				ChargeMode=ConnectPrimer;	
//		}
//		break;
//		
//		case ConnectPrimer:
//		{
//			if( (BatPos_Value-BatNeg_Value)>BatFullV )
//			{	
//				ChargeMode=Bug;
//			}
//			
//			else if((BatPos_Value-BatNeg_Value)< BatexistV )
//			{
//				ChargeMode=DisConnect;
//			}
//			
//			else if( (BatPos_Value-BatNeg_Value)< PreChargeUp)
//			{
//				PID_init(&ChargePWM,Akp,Aki,Akd);   //重设 ChargePWM PID 结构体 kp ,ki,kd 参数,要调整
//				ChargeMode=PreCharge;
//			}
//			
//			else if( ((BatPos_Value-BatNeg_Value)>PreChargeUp)&&((BatPos_Value-BatNeg_Value)<BatFullV  ))
//			{
//				PID_init(&ChargePWM,Akp,Aki,Akd);   //重设 ChargePWM PID 结构体 kp ,ki,kd 参数,要调整
//				ChargeMode=ConstCurrent;
//			}
//			
//			else if( (BatPos_Value-BatNeg_Value)==BatFullV)
//			{		
//		     	ChargeMode=FullCharge;	
//			}
//			
//			PWMn_EnorDis(ChargePWMn ,1); //直接 开启 PWM	
//		}
//		break;
//		
//		
//		case PreCharge:
//		{
//			if( (BatPos_Value-BatNeg_Value)== PreChargeUp )
//				ChargeMode=ConstCurrent;
//			else if( (BatPos_Value-BatNeg_Value)==ConstV )
//				ChargeMode=Bug;
//		}
//		break;
//		
//		
//		case ConstCurrent,
//		{
//			charge_close();
//			BatPos_Value=2.0*GetVoltage (VBatH); 
//			BatNeg_Value=GetVoltage (VBatL);
//			
//			if( IBat>(1.2*ConstI))
//				*ChargeMode=Bug;
//			
//			else if( (BatPos_Value-BatNeg_Value)<BatexistV  )
//				*ChargeMode=DisConnect;
//			
//			else if( (BatPos_Value-BatNeg_Value)==ConstV )
//			{
//				PID_init(ChargePWM,Vkp,Vki,Vkd);   //重设 ChargePWM PID 结构体 kp ,ki,kd 参数,恒流阶段的误差 也 重置为0；
//		   	 	// 开启 时钟 指示：
//				TimeConPulseInit(Timer0,5535,TimeMod_1 , TimeIntEn);
//			    T0ENorDis(1);
//				*ChargeMode=ImPulse;
//			}
//						
//		}
//		break; 
//		 
//		 
//		case ImPulse:
// 		{
//		
//		}
//		break;
//		 
//		case FullCharge: 
//		{
//		
//		}
//		break;
//		
//	   case Bug:
//		{
//			if( BatPos_Value-BatNeg_Value<BatexistV  )
//				ChargeMode=DisConnect;	
//			else if(( BatPos_Value-BatNeg_Value>PreChargeUp )&&(BatPos_Value-BatNeg_Value<ConstV))
//				ChargeMode=ConstCurrent;
//			else if( BatPos_Value-BatNeg_Value==BatFullV)
//			    ChargeMode=FullCharge;
//			else if(BatPos_Value-BatNeg_Value>BatFullV)
//				ChargeMode=Bug;
//		}
//		break;
//		 
//	   case  ConstVoltage :
//		{
//		
//		}
//		break; 
//		
//	   default :
//		   break;
//		
//	}	
//  
//}

////充电器 PW1M 中断函数------------------------------------更改 PWM 占空比，控制输出的 电流 ，电压；
//void PW1Interrupt(void) interrupt ISRPwm1 //   
//{ 
////	#if ChargePWMn==1    // 用PWM1 来控制
//	if ((IEN4&0x08)==0x08) 
//	{		
//			IEN4 &= 0xf7; //Clear PWM1F
//	  PWMn_ValueDuty(ChargePWMn,PWM_Circle,ChargePWM.output);
//	 }	
//	
////	#elif ChargePW Mn==2  // 用PWM2来控制
////	 if ((IRCON2&0x01)==0x01) 
////	{		
////			IRCON2 &= 0xfe; //Clear PWM2F
////		  PWMn_ValueDuty(2,PWM_Circle,ChargePWM.output);					
////	 }	
////	 
////	#elif ChargePWMn==3  // 用PWM3来控制
////	 if ((IRCON2&0x02)==0x02) 
////	{		
////			IRCON2 &= 0xfd; //Clear PWM3F
////		  PWMn_ValueDuty(3,PWM_Circle,ChargePWM.output);					
////	 }	
////	#endif
//}





//void ADCInterrupt(void) interrupt ISRAdc
//{
//	if((IRCON2&0x04)==0x04)      //ADC转换完成  ，有中断
//	{	
//		IRCON2 &= 0xfb ; //Clear ADCF
//  	ADC_Fruit (&AdcOutStore);  // 内部已经有ADM&= ADCStatus_Clear;读取 数值后软件重置	
//		ADC_Start ();
//	}
//}