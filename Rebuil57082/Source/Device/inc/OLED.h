#ifndef OLED_H
#define OLED_H

#include "SN8F5708.H"
#include "GPIO.h"

//#include "Charge.h"           //用他的 divider函数  ，后面要  剪切过来
//# include <stdlib. h>    //  数字转 字符串函数？？？？？？？？？？
//#include "ASCLL.h"
// ------------------------------------------------------------
// IO口模拟I2C通信
// SCL接P1^3
// SDA接P1^2
// ------------------------------------------------------------
#define SCL  P14//串行时钟
#define SDA  P15 //串行数据    // IIC 绑定特定 GPIO口 函数 void 
#define SCL_IO  (14)
#define SDA_IO  (15)


#define high 1
#define low 0

#define	Brightness	0xCF                                //锛燂紵锛燂紵锛?
#define X_WIDTH 	128
#define Y_WIDTH 	64

void delay(unsigned int z);
void IIC_Start();
void IIC_Stop();
void Write_IIC_Byte(unsigned char IIC_Byte);
void OLED_WrDat(unsigned char IIC_Data);
void OLED_WrCmd(unsigned char IIC_Command);
void OLED_Set_Pos(unsigned char x, unsigned char y) ;
void OLED_Fill(unsigned char bmp_dat) ;
void OLED_CLS(void);
void OLED_Init(void);
void OLED_P6x8Str(unsigned char x, unsigned char y,unsigned char ch[]);
void IIC_IOConfigure(void);
void OLED_P6x8Number(unsigned char x, unsigned char y,float num,int pointlen);// 显示 一串数字
void OLED_P6x8charnum(unsigned char x, unsigned char y,unsigned char num);// 显示单个数字
unsigned int tenmi(int mi);

#endif