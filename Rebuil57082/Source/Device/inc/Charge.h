#ifndef CHARGE_H
#define CHARGE_H
#include "SN8F5708.H"
#include "PWM.h"
#include "ADC.h"
#include "PID.h"
#include "FILTER.h"
#include "TIMER.h"

#define BatexistV     (0.5)    //电池接入电路 时 两端应有的电压值
#define PreChargeUp   (3.5)  // 低于此电压要涓流预充电  
#define PreCharge_ConstI  (ConstI/10.0)  
#define ConstI        (0.4)    //电池恒流时想维持的 电流大小
			// 涓流充电呢
#define BatFullV     (4.18)   // 电池 满电最大电压
#define IBat         (GetVoltage (VBatL)/I_Resist)   // 除以 电流 电阻 数值；
#define BugI         (2)     // 恒流阶段 电流上限值
#define ConstV       (4.1)     //电池充电想维持的电压值；
#define I_Resist     (0.1)

//-------------------PID--------------------------------------
//************************************************************
#define Akp   (12)
#define Aki   (20)
#define Akd   (1.8)

#define Vkp   (0.6)    // 恒流 恒压 阶段的  PID参数 ，要调整。
#define Vki   (0)
#define Vkd   (0)

//----------------ADC---------------------------------------
//**********************************************************
#define ADC_InterRef   (3)
#define VBatH   (53)      // P13
#define VBatL   (52)     // P20

//----------------PWM----------------------------------------
//***********************************************************
#define ChargePWMn     (1)     //  1~3代表 使用PWM1~3 来控制充电
#define PWM_Circle     (2000)  //PW1M的周期
          //测试不允许PWM中断，改变 起始——永久 的占空比：
#define DisPwmInt      (0)
#define PW1M_InitDuty  (0)   // 充电起始 PWM占空比，  要防止 更新为  PID中的  0 占空比值，好像0 就停止输出PWM
#define ChargePWM_IO   (47)   // 充电 控制PWM输出  IO口
#define ChargePWM_PIO   P47
//----------------- T0 时钟周期数 ，每周期大概90ms
          //-----------改变Tsignal
#define PoscirNumInit  (40)      // 10*90/4 ms?
#define NegcirNumInit  (40)

	
typedef enum
{
 DisConnect,
 ConnectPrimer,
	
 PreCharge,            ///低于3 V 低压预充
 ConstCurrent,
 ImPulse,
 FullCharge, 
	
 Bug,
 ConstVoltage          // 7 是 恒压
}ChargeMode_E;

extern UINT16 idata AdcOutStore;
extern UINT8 idata Tsignal;
extern float BatPos_Value,BatNeg_Value;
extern ChargeMode_E ChargeMode;


float GetVoltage (UINT8 io); // 获取指定IO口的 电压值； 要 在 define指令中设置好 （内/外部）参考电压值，使用前要初始化GetADC_Init(ADC_InterRef,8,0); 
double divider(double adc,double div);   // 除法函数

void charge_init(void);

void charge_ing(void);

void charge_close(void);

// 根据当前的 model 及相关的状态，安全监测以及、切换模式；

#endif