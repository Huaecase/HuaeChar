/*--------------------------------------------------------------------------
SN8F5708.H

Header file for SNOiX SN8F5708, SN8F5707, SN8F5705 microcontrollers.
Copyright (c) 2015 SONiX Technology Co., Ltd.

Version 1.0    2014-08-06
Version 1.6    2015-09-09
Version 1.7    2015-10-14
--------------------------------------------------------------------------*/

#ifndef __SN8F5708_H__
#define __SN8F5708_H__

/*      Register      */
sfr     P0       = 0x80;
  sbit  P07      = P0^7;
  sbit  P06      = P0^6;
  sbit  P05      = P0^5;
  sbit  P04      = P0^4;
  sbit  P03      = P0^3;
  sbit  P02      = P0^2;
  sbit  P01      = P0^1;
  sbit  P00      = P0^0;
sfr     SP       = 0x81;
sfr     DPL      = 0x82;
sfr     DPH      = 0x83;
sfr     DPL1     = 0x84;
sfr     DPH1     = 0x85;
sfr     WDTR     = 0x86;
sfr     PCON     = 0x87;
sfr     TCON     = 0x88;
  sbit  TF1      = TCON^7;
  sbit  TR1      = TCON^6;
  sbit  TF0      = TCON^5;
  sbit  TR0      = TCON^4;
  sbit  IE1      = TCON^3;
  sbit  IE0      = TCON^1;
sfr     TMOD     = 0x89;
sfr     TL0      = 0x8A;
sfr     TL1      = 0x8B;
sfr     TH0      = 0x8C;
sfr     TH1      = 0x8D;
sfr     CKCON    = 0x8E;
sfr     PEDGE    = 0x8F;
sfr     P1       = 0x90;
  sbit  P17      = P1^7;
  sbit  P16      = P1^6;
  sbit  P15      = P1^5;
  sbit  P14      = P1^4;
  sbit  P13      = P1^3;
  sbit  P12      = P1^2;
  sbit  P11      = P1^1;
  sbit  P10      = P1^0;
sfr     P1W      = 0x91;
sfr     DPS      = 0x92;
sfr     DPC      = 0x93;
sfr     PECMD    = 0x94;
sfr16   PEROM    = 0x95;
sfr     PEROML   = 0x95;
sfr     PEROMH   = 0x96;
sfr     PERAM    = 0x97;
sfr     S0CON    = 0x98;
  sbit  SM0      = S0CON^7;
  sbit  SM1      = S0CON^6;
  sbit  SM20     = S0CON^5;
  sbit  REN0     = S0CON^4;
  sbit  TB80     = S0CON^3;
  sbit  RB80     = S0CON^2;
  sbit  TI0      = S0CON^1;
  sbit  RI0      = S0CON^0;
sfr     S0BUF    = 0x99;
sfr     IEN2     = 0x9A;
sfr     OPM      = 0x9B;
sfr     CMP0M    = 0x9C;
sfr     CMP1M    = 0x9D;
sfr     P2CON    = 0x9E;
sfr     P3CON    = 0x9F;
sfr     P2       = 0xA0;
  sbit  P27      = P2^7;
  sbit  P26      = P2^6;
  sbit  P25      = P2^5;
  sbit  P24      = P2^4;
  sbit  P23      = P2^3;
  sbit  P22      = P2^2;
  sbit  P21      = P2^1;
  sbit  P20      = P2^0;
sfr     PW2M     = 0xA1;
sfr16   PW2Y     = 0xA2;
sfr     PW2YL    = 0xA2;
sfr     PW2YH    = 0xA3;
sfr16   PW2B     = 0xA4;
sfr     PW2BL    = 0xA4;
sfr     PW2BH    = 0xA5;
sfr16   PW2D     = 0xA6;
sfr     PW2DL    = 0xA6;
sfr     PW2DH    = 0xA7;
sfr     IEN0     = 0xA8;
  sbit   EAL     = IEN0^7;
  sbit   ET2     = IEN0^5;
  sbit   ES0     = IEN0^4;
  sbit   ET1     = IEN0^3;
  sbit   EX1     = IEN0^2;
  sbit   ET0     = IEN0^1;
  sbit   EX0     = IEN0^0;
sfr     IP0      = 0xA9;
sfr     S0RELL   = 0xAA;
sfr     PW1M     = 0xAB;
sfr16   PW1Y     = 0xAC;
sfr     PW1YL    = 0xAC;
sfr     PW1YH    = 0xAD;
sfr16   PW1B     = 0xAE;
sfr     PW1BL    = 0xAE;
sfr     PW1BH    = 0xAF;
sfr     P3       = 0xB0;
  sbit  P37      = P3^7;
  sbit  P36      = P3^6;
  sbit  P35      = P3^5;
  sbit  P34      = P3^4;
  sbit  P33      = P3^3;
  sbit  P32      = P3^2;
  sbit  P31      = P3^1;
  sbit  P30      = P3^0;
sfr     PW3M     = 0xB1;
sfr16   PW3Y     = 0xB2;
sfr     PW3YL    = 0xB2;
sfr     PW3YH    = 0xB3;
sfr16   PW3B     = 0xB4;
sfr     PW3BL    = 0xB4;
sfr     PW3BH    = 0xB5;
sfr16   PW3D     = 0xB6;
sfr     PW3DL    = 0xB6;
sfr     PW3DH    = 0xB7;
sfr     IEN1     = 0xB8;
  sbit  ET2RL    = IEN1^7;
  sbit  ET2C3    = IEN1^5;
  sbit  ET2C2    = IEN1^4;
  sbit  ET2C1    = IEN1^3;
  sbit  ET2C0    = IEN1^2;
  sbit  ESPI     = IEN1^1;
  sbit  EI2C     = IEN1^0;
sfr     IP1      = 0xB9;
sfr     S0RELH   = 0xBA;
sfr16   PW1D     = 0xBB;
sfr     PW1DL    = 0xBB;
sfr     PW1DH    = 0xBC;
sfr     PW1A     = 0xBD;
sfr     PW2A     = 0xBE;
sfr     IRCON2   = 0xBF;
sfr     IRCON    = 0xC0;
  sbit   TF2RL   = IRCON^7;
  sbit   TF2     = IRCON^6;
  sbit   TF2C3   = IRCON^5;
  sbit   TF2C2   = IRCON^4;
  sbit   TF2C1   = IRCON^3;
  sbit   TF2C0   = IRCON^2;
sfr     CCEN     = 0xC1;
sfr     CCL1     = 0xC2;
sfr     CCH1     = 0xC3;
sfr     CCL2     = 0xC4;
sfr     CCH2     = 0xC5;
sfr     CCL3     = 0xC6;
sfr     CCH3     = 0xC7;
sfr     T2CON    = 0xC8;
  sbit  T2PS     = T2CON^7;
  sbit  I3FR     = T2CON^6;
  sbit  GF1      = T2CON^5;
  sbit  T2R1     = T2CON^4;
  sbit  T2R0     = T2CON^3;
  sbit  T2CM     = T2CON^2;
  sbit  T2I1     = T2CON^1;
  sbit  T2I0     = T2CON^0;
sfr     CRCL     = 0xCA;
sfr     CRCH     = 0xCB;
sfr     TL2      = 0xCC;
sfr     TH2      = 0xCD;
sfr     CMPT     = 0xCE;
sfr     PW3A     = 0xCF;
sfr     PSW      = 0xD0;
  sbit  CY       = PSW^7;
  sbit  AC       = PSW^6;
  sbit  F0       = PSW^5;
  sbit  RS1      = PSW^4;
  sbit  RS0      = PSW^3;
  sbit  OV       = PSW^2;
  sbit  F1       = PSW^1;
  sbit  P        = PSW^0;
sfr     IEN4     = 0xD1;
sfr     ADM      = 0xD2;
sfr     ADB      = 0xD3;
sfr     ADR      = 0xD4;
sfr     VREFH    = 0xD5;
sfr     P4CON    = 0xD6;
sfr     P5CON    = 0xD7;
sfr     S0CON2   = 0xD8;
  sbit  BD       = S0CON2^7;
sfr     ADT      = 0xD9;
sfr     I2CDAT   = 0xDA;
sfr     I2CADR   = 0xDB;
sfr     I2CCON   = 0xDC;
sfr     I2CSTA   = 0xDD;
sfr     SMBSEL   = 0xDE;
sfr     SMBDST   = 0xDF;
sfr     ACC      = 0xE0;
sfr     SPSTA    = 0xE1;
sfr     SPCON    = 0xE2;
sfr     SPDAT    = 0xE3;
sfr     P1OC     = 0xE4;
sfr     CLKSEL   = 0xE5;
sfr     CLKCMD   = 0xE6;
sfr     TCON0    = 0xE7;
sfr     P4       = 0xE8;
  sbit  P47      = P4^7;
  sbit  P46      = P4^6;
  sbit  P45      = P4^5;
  sbit  P44      = P4^4;
  sbit  P43      = P4^3;
  sbit  P42      = P4^2;
  sbit  P41      = P4^1;
  sbit  P40      = P4^0;
sfr     MD0      = 0xE9;
sfr     MD1      = 0xEA;
sfr     MD2      = 0xEB;
sfr     MD3      = 0xEC;
sfr     MD4      = 0xED;
sfr     MD5      = 0xEE;
sfr     ARCON    = 0xEF;
sfr     B        = 0xF0;
sfr     P0UR     = 0xF1;
sfr     P1UR     = 0xF2;
sfr     P2UR     = 0xF3;
sfr     P3UR     = 0xF4;
sfr     P4UR     = 0xF5;
sfr     P5UR     = 0xF6;
sfr     SRST     = 0xF7;
sfr     P5       = 0xF8;
  sbit  P55      = P5^5;
  sbit  P54      = P5^4;
  sbit  P53      = P5^3;
  sbit  P52      = P5^2;
  sbit  P51      = P5^1;
  sbit  P50      = P5^0;
sfr     P0M      = 0xF9;
sfr     P1M      = 0xFA;
sfr     P2M      = 0xFB;
sfr     P3M      = 0xFC;
sfr     P4M      = 0xFD;
sfr     P5M      = 0xFE;
sfr     PFLAG    = 0xFF;

/*      Interrupt Vector      */
#define ISRInt0    0
#define ISRTimer0  1
#define ISRInt1    2
#define ISRTimer1  3
#define ISRUart    4
#define ISRTimer2  5
#define ISRI2c     8
#define ISRSpi     9
#define ISRCom0    10
#define ISRCom1    11
#define ISRCom2    12
#define ISRCom3    13
#define ISRPwm1    16
#define ISRPwm2    17
#define ISRPwm3    18
#define ISRAdc     19
#define ISRCmp0    20
#define ISRCmp1    21
#define ISRInt2    29

/*      C51 Macros      */
#ifdef __C51__
#include <intrins.h>
#define IDLE() {unsigned char data var_idle=PCON; var_idle |= 0x01; PCON = var_idle; }
#define STOP() {if (EAL == 0) {PCON |= 0x02;} else {EAL = 0; PCON |= 0x02; EAL = 1;}}
#define ISP(ROM_ADDRESS, RAM_ADDRESS) {PERAM = (RAM_ADDRESS); PEROM = ((ROM_ADDRESS) & 0xFFE0 | 0x0A); if (EAL == 0) {PECMD = 0x5A; _nop_(); _nop_();} else {EAL = 0; PECMD = 0x5A; _nop_(); _nop_(); EAL = 1;} PEROML = 0x00;}
#endif  // __C51__

#ifndef uint8_t
#define uint8_t unsigned char
#endif  // uint8_t

#ifndef uint16_t
#define uint16_t unsigned int
#endif  // uint16_t

#ifndef uint32_t
#define uint32_t unsigned long
#endif  // uint32_t

#endif  // __SN8F5708_H__
