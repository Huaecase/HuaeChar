
#include "OLED.h"


const unsigned char code F6x8[][6] =
{
0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
0x00, 0x00, 0x42, 0x7F, 0x40, 0x00,// 1
0x00, 0x42, 0x61, 0x51, 0x49, 0x46,// 2
0x00, 0x21, 0x41, 0x45, 0x4B, 0x31,// 3
0x00, 0x18, 0x14, 0x12, 0x7F, 0x10,// 4
0x00, 0x27, 0x45, 0x45, 0x45, 0x39,// 5
0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
0x00, 0x01, 0x71, 0x09, 0x05, 0x03,// 7
0x00, 0x36, 0x49, 0x49, 0x49, 0x36,// 8
0x00, 0x06, 0x49, 0x49, 0x29, 0x1E,// 9
//0x00,0xE0,0xA0,0xA0,0xF0,0xA0,
//0xA0,0xA0,0xE0,0x00,0x00,0x00,
//0x00,0x07,0x04,0x04,0x1F,0x14,
//0x14,0x14,0x17,0x08,0x00,0x00,/*"电",0*/
//0x40,0xB0,0x20,0xA0,0x60,0x30,
//0xB0,0xE0,0xA0,0x20,0x00,0x00,
//0x10,0x0E,0x10,0x0E,0x01,0x1F,
//0x00,0x1E,0x11,0x19,0x00,0x00,/*"流",2*/
0x00,0x00,0x30,0x30,0x00,0x00,  //  . 
0x00,0x00,0xff,0xff,0x00,0x00,// I 
0x00,0x00,0x63,0x63,0x00,0x00,  // :

};

/***************功能描述：显示6*8一组标准ASCII字符串	显示的坐标（x,y），y为页范围0～7****************/
void OLED_P6x8Str(unsigned char x, unsigned char y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-48;
		if(x>126)
			{x=0;y++;}
		OLED_Set_Pos(x,y);
			
		for(i=0;i<6;i++)
			OLED_WrDat(F6x8[c][i]);
		x+=6;
		j++;
	}
}
void OLED_P6x8Number(unsigned char x, unsigned char y,float num,int pointlen)
{
 unsigned int num1=num;
 UINT8 prelen=0;
 UINT8 top;
// printf("开始时候的 num1： %d\n",num1);
 while(num1/tenmi(prelen)>0)
    prelen++;               // 小数前 的位数
  
 //当小数点前为 0 时小数点前的数字：
 if(!prelen)      //--------显示0
 {
	 OLED_P6x8charnum(x,y,0); // OLED 显示字符函数： // printf(" %d",top);
	 x+=6;
 }
 for(;prelen>0;prelen--)
 {
    top=num1/tenmi(prelen-1);
    num1=num1%tenmi(prelen-1);
	 
   OLED_P6x8charnum(x,y,top); // OLED 显示字符函数： // printf(" %d",top);
   x+=6;
 }

 //printf(".");  //小数点
  OLED_P6x8charnum(x,y,10);        //  F6x8 【10】是 。号的 码字；
  x+=6;

 //小数点后的数字：
num1=num;     //  利用 numl是整数，自己 舍弃 小数部分
num1=num*tenmi(pointlen)-num1*tenmi(pointlen);

for(;pointlen>0;pointlen--)
 {
    top=num1/tenmi(pointlen-1);
    num1=num1%tenmi(pointlen-1);
   OLED_P6x8charnum(x,y,top); // OLED 显示字符函数：//printf("%d ",top);
	 x+=6;
 }

}	

// 显示 字符 函数：
void OLED_P6x8charnum(unsigned char x, unsigned char y,unsigned char num)
{
	UINT8 i;
		if(x>126)
			{x=0;y++;}
		OLED_Set_Pos(x,y);		
		for(i=0;i<6;i++)
			OLED_WrDat(F6x8[num][i]);  // 打印num
		//x+=6;                      // X + 的 由函数外来控制吧
	}


unsigned int tenmi(int mi)
{
    unsigned int num=1;
    for(;mi>0;mi--)
    {
        num*=10;
    }
    return  num;
}


/*********************OLED驱动程序用的延时程序************************************/

void delay(unsigned int z)
{
	unsigned int x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

/**********************************************
//IIC Start
**********************************************/
void IIC_IOConfigure(void)
{
	GPIO_Out(SCL_IO);
	GPIO_Out(SDA_IO);
	GPIO_Up (SCL_IO);
    GPIO_Up (SDA_IO);
}


void IIC_Start()
{
   SCL = high;		
   SDA = high;
   SDA = low;
   SCL = low;
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{
   SCL = low;
   SDA = low;
   SCL = high;
   SDA = high;
}

/**********************************************
// 通过I2C总线写一个字节
**********************************************/
void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(IIC_Byte & 0x80)
			SDA=high;
		else
			SDA=low;
		SCL=high;
		SCL=low;
		IIC_Byte<<=1;
	}
	SDA=1;
	SCL=1;
	SCL=0;
}

/*********************OLED写数据************************************/ 
void OLED_WrDat(unsigned char IIC_Data)
{
	IIC_Start();
	Write_IIC_Byte(0x78);
	Write_IIC_Byte(0x40);			//write data
	Write_IIC_Byte(IIC_Data);
	IIC_Stop();
}
/*********************OLED写命令************************************/
void OLED_WrCmd(unsigned char IIC_Command)
{
	IIC_Start();
	Write_IIC_Byte(0x78);            //Slave address,SA0=0
	Write_IIC_Byte(0x00);			//write command
	Write_IIC_Byte(IIC_Command);
	IIC_Stop();
}
/*********************OLED 设置坐标************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WrCmd(0xb0+y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x01);
} 
/*********************OLED全屏************************************/
void OLED_Fill(unsigned char bmp_dat) 
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(bmp_dat);
	}
}
/*********************OLED复位************************************/
void OLED_CLS(void)
{
	unsigned char y,x;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++)
		OLED_WrDat(0);
	}
}
/*********************OLED初始化************************************/
void OLED_Init(void)
{
	delay(500);//初始化之前的延时很重要！ 原来是500
	OLED_WrCmd(0xae);//--turn off oled panel
	OLED_WrCmd(0x00);//---set low column address
	OLED_WrCmd(0x10);//---set high column address
	OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WrCmd(0x81);//--set contrast control register
	OLED_WrCmd(Brightness); // Set SEG Output Current Brightness
	OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WrCmd(0xa6);//--set normal display
	OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
	OLED_WrCmd(0x3f);//--1/64 duty
	OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WrCmd(0x00);//-not offset
	OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WrCmd(0xd9);//--set pre-charge period
	OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WrCmd(0xda);//--set com pins hardware configuration
	OLED_WrCmd(0x12);
	OLED_WrCmd(0xdb);//--set vcomh
	OLED_WrCmd(0x40);//Set VCOM Deselect Level
	OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WrCmd(0x02);//
	OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
	OLED_WrCmd(0x14);//--set(0x10) disable
	OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
	OLED_WrCmd(0xaf);//--turn on oled panel
	OLED_Fill(0x00); //初始清屏
	OLED_Set_Pos(0,0);
} 