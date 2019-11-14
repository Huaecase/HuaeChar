#include "GPIO.h"

void GPIO_In(UINT8 Pin)     //57082 仅有：00 01 02 05 06 14 15 22 23  40 46 47 50 51 52 53 54 55 
{
 switch (Pin)
 {
// -------------------P0 口-------------------
	 case 00:
		 P0M	  &=0xfe;
		 break;
		 
	 case 01:
		 P0M	  &=0xfd;
		 break;
		 	 
	 case 02:
		 P0M	  &=0xfb;
		 break;
		 
	 case 03:
		 P0M	  &=0xf7;
		 break;
		 	 
	 case 04:
		 P0M	  &=0xef;
		 break;
		 
	 case 05:
		 P0M	  &=0xdf;
		 break;
		 
	 case 06:
		 P0M	  &=0xbf;
		 break;
		 
	 case 07:
		 P0M	  &=0x7f;
		 break;
//------------P1 口-------------------------
	 case 10:
		 P1M	  &=0xfe;
		 break;
		 
	 case 11:
		 P1M	  &=0xfd;
		 break;
		 	 
	 case 12:
		 P1M	  &=0xfb;
		 break;
		 
	 case 13:
		 P1M	  &=0xf7;
		 break;
		 	 
	 case 14:
		 P1M	  &=0xef;
		 break;
		 
	 case 15:
		 P1M	  &=0xdf;
		 break;
		 
	 case 16:
		 P1M	  &=0xbf;
		 break;
		 
	 case 17:
		 P1M	  &=0x7f;
		 break;
	//------------P2 口---------------------------------------------------	 
		 case 20:
		 P2M	  &=0xfe;
		 break;
		 
	 case 21:
		 P2M	  &=0xfd;
		 break;
		 	 
	 case 22:
		 P2M	  &=0xfb;
		 break;
		 
	 case 23:
		 P2M	  &=0xf7;
		 break;
		 	 
	 case 24:
		 P2M	  &=0xef;
		 break;
		 
	 case 25:
		 P2M	  &=0xdf;
		 break;
		 
	 case 26:
		 P2M	  &=0xbf;
		 break;
		 
	 case 27:
		 P2M	  &=0x7f;
		 break;
//-------------P3口--------------------
	 	 case 30:
		 P3M	  &=0xfe;
		 break;
		 
	 case 31:
		 P3M	  &=0xfd;
		 break;
		 	 
	 case 32:
		 P3M	  &=0xfb;
		 break;
		 
	 case 33:
		 P3M	  &=0xf7;
		 break;
		 	 
	 case 34:
		 P3M	  &=0xef;
		 break;
		 
	 case 35:
		 P3M	  &=0xdf;
		 break;
		 
	 case 36:
		 P3M	  &=0xbf;
		 break;
		 
	 case 37:
		 P3M	  &=0x7f;
		 break;
//--------------------P4口--------------------
	  case 40:
		 P4M	  &=0xfe;
		 break;
		 
	 case 41:
		 P4M	  &=0xfd;
		 break;
		 	 
	 case 42:
		 P4M	  &=0xfb;
		 break;
		 
	 case 43:
		 P4M	  &=0xf7;
		 break;
		 	 
	 case 44:
		 P4M	  &=0xef;
		 break;
		 
	 case 45:
		 P4M	  &=0xdf;
		 break;
		 
	 case 46:
		 P4M	  &=0xbf;
		 break;
		 
	 case 47:
		 P4M	  &=0x7f;
		 break;
//----------------P5口-------------------
	  case 50:
		 P5M	  &=0xfe;
		 break;
		 
	 case 51:
		 P5M	  &=0xfd;
		 break;
		 	 
	 case 52:
		 P5M	  &=0xfb;
		 break;
		 
	 case 53:
		 P5M	  &=0xf7;
		 break;
		 	 
	 case 54:
		 P3M	  &=0xef;
		 break;
		 
	 case 55:
		 P5M	  &=0xdf;
		 break;
		 
	 case 56:
		 P5M	  &=0xbf;
		 break;
		 
	 case 57:
		 P5M	  &=0x7f;
		 break;
	 
	 default:
		 break;
 }

}

void GPIO_Out(UINT8 Pin)
{
 switch (Pin)
 {
	 
//---------------P0口-----------------------
	 case 00:
		 P0M |=0x01;
		 break;
		 
	 case 01:
		 P0M |=0x02;
		 break;
		 	 
	 case 02:
		 P0M |=0x04;
		 break;
		 
	 case 03:
		 P0M |=0x08;
		 break;
		 	 
	 case 04:
		 P0M |=0x10;
		 break;
		 
	 case 05:
		 P0M |=0x20;
		 break;
		 
	 case 06:
		 P0M |=0x40;
		 break;
		 
	 case 07:
		 P0M |=0x80;
		 break;
//---------------P1口-----------------------		  
	 case 10:
		 P1M |=0x01;
		 break;
		 
	 case 11:
		 P1M |=0x02;
		 break;
		 	 
	 case 12:
		 P1M |=0x04;
		 break;
		 
	 case 13:
		 P1M |=0x08;
		 break;
		  
	 case 14:
		 P1M |=0x10;
		 break;
		 
	 case 15:
		 P1M |=0x20;
		 break;
		 
	 case 16:
		 P1M |=0x40;
		 break;
		 
	 case 17:
		 P1M |=0x80;
		 break;
//---------------P2口-----------------------		  
	 case 20:
		 P2M |=0x01;
		 break;
		 
	 case 21:
		 P2M |=0x02;
		 break;
		 	 
	 case 22:
		 P2M |=0x04;
		 break;
		 
	 case 23:
		 P2M |=0x08;
		 break;
		 	 
	 case 24:
		 P2M |=0x10;
		 break;
		 
	 case 25:
		 P2M |=0x20;
		 break;
		 
	 case 26:
		 P2M |=0x40;
		 break;
		 
	 case 27:
		 P2M |=0x80;
		 break;
//---------------P3口-----------------------	
	 case 30:
		 P3M |=0x01;
		 break;
		 
	 case 31:
		 P3M |=0x02;
		 break;
		 	 
	 case 32:
		 P3M |=0x04;
		 break;
		 
	 case 33:
		 P3M |=0x08;
		 break;
		 	 
	 case 34:
		 P3M |=0x10;
		 break;
		 
	 case 35:
		 P3M |=0x20;
		 break;
		 
	 case 36:
		 P3M |=0x40;
		 break;
		 
	 case 37:
		 P3M |=0x80;
		 break;

//---------------P4口-----------------------
	 case 40:
		 P4M |=0x01;
		 break;
		 
	 case 41:
		 P4M |=0x02;
		 break;
		 	 
	 case 42:
		 P4M |=0x04;
		 break;
		 
	 case 43:
		 P4M |=0x08;
		 break;
		 	 
	 case 44:
		 P4M |=0x10;
		 break;
		 
	 case 45:
		 P4M |=0x20;
		 break;
		 
	 case 46:
		 P4M |=0x40;
		 break;
		 
	 case 47:
		 P4M |=0x80;
		 break;	 
//	 
//---------------P5口-----------------------
	 	 case 50:
		 P5M |=0x01;
		 break;
		 
	 case 51:
		 P5M |=0x02;
		 break;
		 	 
	 case 52:
		 P5M |=0x04;
		 break;
		 
	 case 53:
		 P5M |=0x08;
		 break;
		 	 
	 case 54:
		 P5M |=0x10;
		 break;
		 
	 case 55:
		 P5M |=0x20;
		 break;
		 
	 case 56:
		 P5M |=0x40;
		 break;
		 
	 case 57:
		 P5M |=0x80;
		 break;
	 
	 default:
		 break;
 }
}

void GPIO_Up(UINT8  Pin)
{
 switch (Pin)
 {
//-------------P0 口-------------------
	 case 00:
		 P0UR|=0x01;
		 break;
		 
	 case 01:
		 P0UR |=0x02;
		 break;
		 	 
	 case 02:
		 P0UR |=0x04;
		 break;
		 
	 case 03:
		 P0UR |=0x08;
		 break;
		 	 
	 case 04:
		 P0UR|=0x10;
		 break;
		 
	 case 05:
		 P0UR |=0x20;
		 break;
		 
	 case 06:
		 P0UR |=0x40;
		 break;
		 
	 case 07:
		 P0UR |=0x80;
		 break;
//-------------P1 口-------------------		  
	 case 10:
		 P1UR |=0x01;
		 break;
		 
	 case 11:
		 P1UR |=0x02;
		 break;
		 	 
	 case 12:
		 P1UR |=0x04;
		 break;
		 
	 case 13:
		 P1UR |=0x08;
		 break;
		  
	 case 14:
		 P1UR |=0x10;
		 break;
		 
	 case 15:
		 P1UR |=0x20;
		 break;
		 
	 case 16:
		 P1UR |=0x40;
		 break;
		 
	 case 17:
		 P1UR |=0x80;
		 break;
//-------------P2 口-------------------		  
	 case 20:
		 P2UR|=0x01;
		 break;
		 
	 case 21:
		 P2UR |=0x02;
		 break;
		 	 
	 case 22:
		 P2UR |=0x04;
		 break;
		 
	 case 23:
		 P2UR |=0x08;
		 break;
		 	 
	 case 24:
		 P2UR|=0x10;
		 break;
		 
	 case 25:
		 P2UR |=0x20;
		 break;
		 
	 case 26:
		 P2UR |=0x40;
		 break;
		 
	 case 27:
		 P2UR |=0x80;
		 break;
//-------------P3 口-------------------		
	 case 30:
		 P3UR|=0x01;
		 break;
		 
	 case 31:
		 P3UR |=0x02;
		 break;
		 	 
	 case 32:
		 P3UR |=0x04;
		 break;
		 
	 case 33:
		 P3UR |=0x08;
		 break;
		 	 
	 case 34:
		 P3UR|=0x10;
		 break;
		 
	 case 35:
		 P3UR |=0x20;
		 break;
		 
	 case 36:
		 P3UR |=0x40;
		 break;
		 
	 case 37:
		 P3UR |=0x80;
		 break;
//-------------P4 口-------------------	
	 case 40:
		 P4UR|=0x01;
		 break;
		 
	 case 41:
		 P4UR |=0x02;
		 break;
		 	 
	 case 42:
		 P4UR |=0x04;
		 break;
		 
	 case 43:
		 P4UR |=0x08;
		 break;
		 	 
	 case 44:
		 P4UR|=0x10;
		 break;
		 
	 case 45:
		 P4UR |=0x20;
		 break;
		 
	 case 46:
		 P4UR |=0x40;
		 break;
		 
	 case 47:
		 P4UR |=0x80;
		 break;
//-------------P5 口-------------------		 	 
	 case 50:
		 P5UR|=0x01;
		 break;
		 
	 case 51:
		 P5UR |=0x02;
		 break;
		 	 
	 case 52:
		 P5UR |=0x04;
		 break;
		 
	 case 53:
		 P5UR |=0x08;
		 break;
		 	 
	 case 54:
		 P5UR|=0x10;
		 break;
		 
	 case 55:
		 P5UR |=0x20;
		 break;
		 
	 case 56:
		 P5UR |=0x40;
		 break;
		 
	 case 57:
		 P5UR |=0x80;
		 break;
	 
	 default:
		 break;
 }
}

void GPIO_NoUp(UINT8 Pin)
{
 switch (Pin)
 {
//-------------P0 口-------------------		
	 case 00:
		 P0UR  &=0xfe;
		 break;
		 
	 case 01:
		 P0UR   &=0xfd;
		 break;
		 	 
	 case 02:
		 P0UR 	  &=0xfb;
		 break;
		 
	 case 03:
		 P0UR   &=0xf7;
		 break;
		 	 
	 case 04:
		 P0UR   &=0xef;
		 break;
		 
	 case 05:
		 P0UR 	  &=0xdf;
		 break;
		 
	 case 06:
		 P0UR 	  &=0xbf;
		 break;
		 
	 case 07:
		 P0UR 	  &=0x7f;
		 break;
//-------------P1 口-------------------		
	 case 10:
		 P1UR   &=0xfe;
		 break;
		 
	 case 11:
		 P1UR 	  &=0xfd;
		 break;
		 	 
	 case 12:
		 P1UR 	  &=0xfb;
		 break;
		 
	 case 13:
		 P1UR 	  &=0xf7;
		 break;
		 	 
	 case 14:
		 P1UR 	  &=0xef;
		 break;
		 
	 case 15:
		 P1UR 	  &=0xdf;
		 break;
		 
	 case 16:
		 P1UR   &=0xbf;
		 break;
		 
	 case 17:
		 P1UR 	  &=0x7f;
		 break;
//-------------P2 口-------------------				 
	 case 20:
		 P2UR  &=0xfe;
		 break;
		 
	 case 21:
		 P2UR   &=0xfd;
		 break;
		 	 
	 case 22:
		 P2UR 	  &=0xfb;
		 break;
		 
	 case 23:
		 P2UR   &=0xf7;
		 break;
		 	 
	 case 24:
		 P2UR   &=0xef;
		 break;
		 
	 case 25:
		 P2UR 	  &=0xdf;
		 break;
		 
	 case 26:
		 P2UR 	  &=0xbf;
		 break;
		 
	 case 27:
		 P2UR 	  &=0x7f;
		 break;
//-------------P3 口-------------------		
	 case 30:
		 P3UR  &=0xfe;
		 break;
		 
	 case 31:
		 P3UR   &=0xfd;
		 break;
		 	 
	 case 32:
		 P3UR 	  &=0xfb;
		 break;
		 
	 case 33:
		 P3UR   &=0xf7;
		 break;
		 	 
	 case 34:
		 P3UR   &=0xef;
		 break;
		 
	 case 35:
		 P3UR 	  &=0xdf;
		 break;
		 
	 case 36:
		 P3UR 	  &=0xbf;
		 break;
		 
	 case 37:
		 P3UR 	  &=0x7f;
		 break;
//-------------P4 口-------------------
	 case 40:
		 P4UR  &=0xfe;
		 break;
		 
	 case 41:
		 P4UR   &=0xfd;
		 break;
		 	 
	 case 42:
		 P4UR 	  &=0xfb;
		 break;
		 
	 case 43:
		 P4UR   &=0xf7;
		 break;
		 	 
	 case 44:
		 P4UR   &=0xef;
		 break;
		 
	 case 45:
		 P4UR 	  &=0xdf;
		 break;
		 
	 case 46:
		 P4UR 	  &=0xbf;
		 break;
		 
	 case 47:
		 P4UR 	  &=0x7f;
		 break;
//-------------P5 口-------------------	
	 case 50:
		 P5UR  &=0xfe;
		 break;
		 
	 case 51:
		 P5UR   &=0xfd;
		 break;
		 	 
	 case 52:
		 P5UR 	  &=0xfb;
		 break;
		 
	 case 53:
		 P5UR   &=0xf7;
		 break;
		 	 
	 case 54:
		 P5UR   &=0xef;
		 break;
		 
	 case 55:
		 P5UR 	  &=0xdf;
		 break;
		 
	 case 56:
		 P5UR 	  &=0xbf;
		 break;
		 
	 case 57:
		 P5UR 	  &=0x7f;
		 break;
	 
	 default:
		 break;
 }

}



//void GPIO_Init(void)
//{
////	P0 = P1 = P2 = 0;
////	
////	P0M = P1M = P2M = 0;
////	P0UR = P1UR = P2UR = 0xff;			
//P0M	  |= 0xa0;			      //    P 07  05  output  no up;  0 inPut  1,output	 
//P0UR  &= 0x5f;						//  0 ban up, 1 enable up; 
////	
//	P0M	  &=
////P1M   |= 0x40;						// P16 ouput	
////P1UR  &= 0xbf;						

//P2M   |= 0x01;           //  P20 input  no up
//P2UR  &= 0xfe;
//	
////	P2UR  = 0xfe;						// P10 as extern cap pin
//		
////	P1M   = 0x30;						// P14, P15 as PWM_PIN
////	P1CON = 0x4c;						// close schmidt trigger
////	P2CON = 0x01;
//}