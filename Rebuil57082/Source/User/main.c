#include "SN8F5708.H"
#include "Systemclk.h"
#include "OLED.h"
#include "Charge.h"


void main ()
{
	System_Init();
			
//---------------OLED-----------------
	IIC_IOConfigure();
	OLED_Init();
//---------------充电初始化---------------------------
    charge_init( )  ;
	
	while (1)
  {  
	 charge_ing(); //有限状态机 充电 模式控制
	 P55=Tsignal; 
	  
     OLED_P6x8Number(10,1,(BatPos_Value-BatNeg_Value),4);
     OLED_P6x8Number(10,3,2.0*GetVoltage (VBatH),4);
	  
	 OLED_P6x8Number(100,1,ChargeMode,1);   // 阶段指示
	  
	 OLED_P6x8charnum(50,7,11);   // I
	 OLED_P6x8charnum(58,7,12);  // :  
	 OLED_P6x8Number(68,7, IBat,4); //充电电流；
	 //delay(2000);		
  }	
}

	  //	//
//	  if(reapet)
//		  reapet--;
//	  else
//	  {
//		reapet=20;
//		if(pwmdutynumbers>0)
//			pwmdutynumbers--;
//		else 
//			pwmdutynumbers=100;
//	  }
//	
//	  
//	PWMn_ValueDuty(1,PWM_Circle,pwmdutynumbers);
////	
//	delay(100);	
//---------------呼吸灯-------------------
//	Breathled_init();
//	LED_BreathStart(1);	
//-------------- 串口----------------------
//	UART_Enable(1);
//	UARTBaudRate(32000000,9600);