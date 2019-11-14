#ifndef IIC_H
#define IIC_H
//I2CCON 的 ENS1位是不是需要写 1才能访问 IIC相关寄存器？
#include "SN8F5708.H"
#include "GenericTypeDefs.h"
#include "GPIO.h" 
			
// I2CSTA  寄存器--------------------- 
//[7..3] :IIC status code
//[2..0] :SMBus status code
// IIC和SMBus共用资源这里不启用SMBus	

#define   IIC_STA      (I2CSTA&0xf8)  //避免 SMBus状态字的影响
//-----------------主机发送模式-------------------
#define   MasStartT_SlaR        0x08
#define   MasReStartT_SlaRW  0x10

#define   MasSlaWTAck_WData     0x18   
#define   MasSlaWTNAck_WData    0x20
#define   MasDATTAck_WData      0x28
#define   MasDATTNAck_WData     0x30

#endif
