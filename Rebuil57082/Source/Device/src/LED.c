#include "LED.h"
//#include "Charge.h"

int DutyNum;   //方波占空比
UINT8 Dutystep;  //方波占空比 步进值
Model LedRSTModel;
UINT16 SameRepet=LedsameDutyRepeat;
 
void Breathled_init(void)
{
	DutyNum=LEDPWMInitDuty ;
	PWMn_Out_Init(LEDPWMnum ,LEDPWMcircle ,LEDPWMInitDuty,1,LEDPWM_IOPin);
 	  	
	Dutystep=LEDIncreamentstep;
	LedRSTModel=LEDBreathModel; 
}

void LED_BreathStart(UINT8 a)
{
  if(a)
	PWMn_EnorDis(LEDPWMnum,1);
  else
	PWMn_EnorDis(LEDPWMnum,0);
}


 //呼吸灯 LED中断函数  PWM1 中断
void PW1Interrupt(void) interrupt ISRPwm1 //
{ 
	if ((IEN4&0x08)==0x08) 
	{		
			IEN4 &= 0xf7; //Clear PWM1F
				
			if (!SameRepet)
				{		//P07=~P07;	
					SameRepet=LedsameDutyRepeat; //同一个占空比PWM1输出重复		
							if (LedRSTModel==circle &&DutyNum>100)
							{
								DutyNum=80;
								Dutystep=-2;												
							}
							else if (LedRSTModel==circle &&DutyNum<0)
							{
								DutyNum=0;
								Dutystep=2;
						}	
							else if(LedRSTModel==jumpdown && DutyNum<=0)
							{
								DutyNum=100;
							}
							else if(LedRSTModel==jumpup && DutyNum>=100)
							{
								DutyNum=0;
							}
						DutyNum+=Dutystep;	
							
					 //PWMn_ValueDuty(LEDPWMnum ,PWM_Circle,DutyNum);			
						//P07=~P07;
				}	
			else 
				SameRepet-=1;	

      PWMn_ValueDuty(LEDPWMnum ,LEDPWMcircle,DutyNum);							
	 }	
	
}