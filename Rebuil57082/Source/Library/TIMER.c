
#include "TIMER.h"

void TimeConPulseInit(UINT8 Timernum,UINT16 TCountstart,UINT8 Tmodel, UINT8 inter)
{
	// Fcpu=8M时 定时器 每+ 1 要 1.5 微秒
	// 推荐设置Tmodel 为1 ===16位向上计数
	//推荐 Timevalue 为 5535， 这样计数60000次
	// 则一个 T 周期大概60000* 1.5 us ==90 毫秒
	//
    TimerInit( Timernum,Tmodel,inter);	
	TimerValue(Timernum,TCountstart);
	
}


void T0ENorDis(UINT8 a)
{
   if(a)
	 TR0=1;
   else
	 TR0=0;
}
void T1ENorDis(UINT8 a)
{
	if(a)
		TR1=1;
	else
		TR1=0;
}

// 默认 FCPU/12 作为时 震荡源,不用设置
// 建议使用 模式 1  16 位向上 计数器。
//默认 INT 0/1 不能作为 定时器的 时钟源控制信号；
void TimerInit(UINT8 Timernum,UINT8 Tmodel,UINT8 inter)
{
     switch(Timernum)
	 {
		 case 0:
		 {	
			TMOD &=0xfc; //  清除T0 模式位 
			switch(Tmodel)
			{	
				case 0:
					// TMOD|=0x00;
					break;
					
				case 1:
					TMOD|=0x01;
				    break;
					
				case 2:
					TMOD|=0x02;
					break;
					
					
				case 3:
					TMOD|=0x03;
					break;
				default:
					break;			
			}
			 	 
			 if (inter)
				T0IntENorDis(1);
			 else
				T0IntENorDis(0);
		 }
			break;
			 
		 case 1:    //T 1 计时器
		 {	
			 TMOD &= 0xcf;
				switch(Tmodel)
			{
				
				case 0:
				    //TMOD|=0x00;
					break;
					
				case 1:
				    TMOD|=0x10;
				    break;
					
				case 2:
				    TMOD|=0x20;
					break;				
					
				case 3:
					TMOD|=0x30;
					break;
				
				default:
					break;			
			}
			 
			 if (inter)
				T1IntENorDis(1);
			 else
				T1IntENorDis(0);
			
		 }
			break;	 
	 }
}

void TimerValue(UINT8 Timernum,UINT16 TimerValue)
{
		switch(Timernum)
		{
			case 0:
			{
				TH0=(0xff00&TimerValue)>>8;
				TL0=0x00ff&TimerValue;
			}
			break;
				
			case 1:
			{
				TH1=(0xff00&TimerValue)>>8;
				TL1=0x00ff&TimerValue;
			}
			break;
		
			default:
			break;
		}
}

//-------------------------工具函数--------------------
void T0IntENorDis(UINT8 a)
{
	if(a)
	{
		EAL=1;
		ET0=1;
	}
	else
		ET0=0;
}


void T1IntENorDis(UINT8 a)
{
	if(a)
	{
		EAL=1;
		ET1=1;
	}
	else
		ET1=0;
}