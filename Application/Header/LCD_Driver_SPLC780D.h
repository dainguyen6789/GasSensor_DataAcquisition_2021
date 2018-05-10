//reference page 7 http://www.newhavendisplay.com/app_notes/SPLC780D.pdf
#include "stc15f2k60s2.h"
#define Clear_Display 0x01s
#define Return_Home 0x02
#define Entry_Mode_Set 0x06
#define Function_Set_8bit 0x38
#define Function_Set_4bit	0x18
 sbit 			LCD_E	=	P1^3;	 
 sbit 			LCD_RS	=	P1^1;	   
 sbit 			LCD_RW	=	P1^2;	   
 sbit 			LCD_D4	=	P1^4;	   
 sbit 			LCD_D5	=	P1^5;	
 sbit 			LCD_D6	=	P1^6;	
 sbit 			LCD_D7	=	P1^7;	 