#ifndef _TIME_H_
#define _TIME_H_

#include "SN8F5708.H"
#include "GenericTypeDefs.h"
//#include "INT.h"

//---------------要结合 需要的 值来设置----------------
//#define Postime        3000         // 赋值1 的 时间，单位 毫秒
//#define Negtime        1500         // 赋值为  0 的时间

# define  TimeMod_1      (1)
# define  Timer0        (0)
# define  Timer1        (1)
# define  TimeIntEn     (1)
#define   TimeIntDis    (0)
//---------------------------------------------------------------------------------------------
// TMOD寄存器
#define T0Mode0 		(0 << 0) 				// T0 mode0, 13-bit counter
#define T0Mode1 		(1 << 0) 				// T0 mode1, 16-bit counter
#define T0Mode2 		(2 << 0) 				// T0 mode2, 8-bit auto-reload counter
#define T0Mode3 		(3 << 0) 				// T0 mode3, T0 two 8-bit counter / T1 no flag
#define T0Gate 			(8 << 0) 				// T0 gating clock by INT0
#define T0ClkExt 		(4 << 0) 				// T0 clock source from Fosc or FRTC  //公式 Ftime0=fosc/T0RATE
// 这是哪个寄存器？？
#define T0ClkFcpu	 	(0 << 0) 				// T0 clock source from Fcpu/12
//--------------------------------

// IEN0中的ET0
#define T0EnIrq			(2 << 0)				// T0 interrupt enable
// TCON寄存器中
#define T0FunEn			(1 << 4)				// T0 function control enable
//TCON0  寄存器控制：（fosc作为时钟源时 设fosc的分频系数）
#define T0Rate			(7 << 4)				// T0 extern clock prescale


//----------------------------------------------------------------------------------------------
//------------------- T1计时器 模式-------------------------------------------------------------
// TMOD 寄存器设置：
//   
#define T1Mode0 		(0 << 4) 				// T1 mode0, 13-bit counter
#define T1Mode1 		(1 << 4) 				// T1 mode1, 16-bit counter
#define T1Mode2 		(2 << 4) 				// T1 mode2, 8-bit auto-reload counter
#define T1Mode3 		(3 << 4) 				// T1 mode3, T1 stop

#define T1ClkExt 		(4 << 4) 				// T1 clock source from Fosc or FRTC
#define T1ClkFcpu 	    (0 << 4) 				// T1 clock source from Fcpu/12
//--------------------------------------
#define T1Gate 			(8 << 4) 				// T1 gating clock by INT1

// TCON寄存器中 TR1 位
#define T1FunEn			(4 << 4)				// T1 function control enable
//IEN0 寄存器：
#define T1EnIrq			(8 << 0)				// T1 interrupt enable
//TCON0寄存器：：
#define T1Rate			(4 << 0)				// T1 extern clock prescale
//--------------------------------------------------------------------------------





// 使用  Fosc 作为 计时器 的默认 时钟源；
// 建议使用 模式 1  16 位向上 计数器。
void TimeConPulseInit(UINT8 Timernum,UINT16 TCountstart,UINT8 Tmodel, UINT8 inter);
	
void TimerInit(UINT8 Timernum,UINT8 Tmodel,UINT8 inter);
void TimerValue(UINT8 Timernum,UINT16 TimerValue);
void T0ENorDis(UINT8 a);
void T1ENorDis(UINT8 a);



void T0IntENorDis(UINT8 a);
void T1IntENorDis(UINT8 a);

#endif
