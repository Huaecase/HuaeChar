#include "Systemclk.h"



void System_Init(void)
{
//	CKCON  =0x70 ;      //仿照 PDF加上去的 
//	CLKSEL = 0x05;			// Fcpu = Fosc(original system clock)32 / 4 = 8M
//	CLKCMD = 0x69; 			// Apply setting command
//	CKCON  = 0x00;			// IROM  fetch =fcpu/1
//	WDTR   = 0x5A;      // Clear watchdog if watchdog enable(enable in option file)
	CKCON  =0x70 ;      //仿照 PDF加上去的 
	CLKSEL = 0x07;			// Fcpu = Fosc/1;  32M
	CLKCMD = 0x69; 			// Apply setting command
	CKCON  = 0x33;			// IROM  fetch =fcpu/1  ,XRAM 8M
	WDTR   = 0x5A;      // Clear watchdog if watchdog enable(enable in option file)
	
//	 CLKSEL  ——》设置 fosc 到 fcpu的分频系数，
//	 CLKCMD  ——》设置为 0x69就是 接受 CLKSEL的设置；
//
//----------------------------------------------------------
//CKCON = 0x70; // For change safely the system clock
	
//CLKSEL = 0x05; // set fcpu = fosc/4
//CLKCMD = 0x69; // Apply CLKSEL’s setting    CLKSEL 和 CLKCMD协同设置fosc到fcpu的分频系数
	
	//CKCON = 0x00; // IROM fetch = fcpu / 1       CKCON  设置的是  CPU  读取IROM 在 1*fcpu基础上 增加的周期，
	//计算公式为   IROM fetching cycle= fcpu/(pwsc[2:0]+1) ,对于低速ROM ，需要读取速度在8MHz以下
	
	// PSWSC【2：0】属于CKCON寄存器
//-----------------------------------------------------------
}
