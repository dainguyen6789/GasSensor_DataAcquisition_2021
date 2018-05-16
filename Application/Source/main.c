
#include "stc15f2k60s2.h"
#include "a25lc040.h"
#include <stdio.h>
#include <stdlib.h>
 //#include "hc595.h"
#include "PCF85063BTL.h"
//#include "UART1.h"
#include "KeyPad.h"
#include <REG51F.H>

#define FOSC 18432000L 	 
#define T1MS (65536-FOSC/1000)

void Delay_ms(unsigned int ms);
void SendString(char *s);
void SendUART1(unsigned char dat);
void initUART1(void);
unsigned char BCDtoDec(unsigned char BCD);
unsigned char ten(unsigned char BCD);
unsigned char unit(unsigned char BCD);
unsigned char SPI_ReadTime(unsigned char addr);
void SPI_WriteTime(unsigned char val,unsigned char addr);
unsigned char ASCIItoBCD(unsigned char ascii[2]); // time format hh:mm:ss
void SendUART1(unsigned char dat);
void SPI_Init(void);
void WriteData(unsigned char dat);
void LCD_Init(void);
void DisplayLCD(unsigned char BCD);
void Display_time(unsigned char *months,unsigned char *days,unsigned char *hours,unsigned char *mins,unsigned char *seconds);
void LCD_return_home(void);
void Key_Process(void);
void Display_Line(int line);

bit busy;
unsigned char Rec_data_hour[]="hh",Rec_data_min[]="mm",hour_count,min_count;
int RX_Data_Uart_Cnt=0;
int st_time=0;
static int KeyCount=0;
static unsigned char KeyNum_Old,KeyNum,PressedKey[4]="hhmm";

void tm0_isr() interrupt 1 using 1
{
	//Display_time(&months,&days,&hours,&mins,&seconds);
}

void main(void)
{
	unsigned char seconds,mins, hours,days,months;
	static int KeyCount=0;
	static unsigned char KeyNum_Old,KeyNum,PressedKey[4]="hhmm";	
//	unsigned char KeyNum;
	int count=0;
	char numStr[5];
	LCD_Init();
	SPI_Init();
	KeyPad_IO_Init();
	initUART1();
	//Timer0===================================
	AUXR |=0x80;
	TL0=T1MS;
	TH0=T1MS>>8;
	TMOD=0x00;
	TR0=1;
	ET0=1;
	//========================================
	EA=1; 			// each interrupt source will be enable or disable by setting its interrupt bit	   
	SPI_WriteTime(0x12,Hours);		// data , register address
	Delay_ms(500);
	SPI_WriteTime(0x12,Minutes);
	Delay_ms(500);
	//LCD_clear();
	while(1)
	{

		
		//Delay_ms(300);
		Key_Process();
		/*KeyNum_Old=KeyNum;
		
		KeyNum=Key_Scan();
		//if( (KeyNum=Key_Scan())!=0 )  	//����Ƿ��м�����
		if(KeyNum_Old==Unpress && KeyNum!=Unpress)
		{
			PressedKey[KeyCount]=KeyNum;
			KeyCount++;
			if(KeyCount==4)
			{
				KeyCount=0;
				hour_count=(PressedKey[0]<<4)|PressedKey[1];
				min_count=(PressedKey[2]<<4)|PressedKey[3];
				SPI_WriteTime(hour_count,Hours);
				SPI_WriteTime(min_count,Minutes);
			}
			
		}*/
		count++;
		if (count==500)
		{
			Display_Line(2);
			DisplayLCD(hours);
			WriteData(0x3A);//display ":"
			DisplayLCD(mins);
			WriteData(0x3A);//display ":"
			DisplayLCD(seconds&0x7f);
			WriteData(0x3B);//display ";"
			DisplayLCD(months);
			WriteData(0x2D);//display "-"
			DisplayLCD(days);				
			
			count=0;
			//LCD_clear();
		//WriteData(0x20);
			LCD_return_home();
			
			
		}
		Display_time(&months,&days,&hours,&mins,&seconds);
		//==================================================		
		// This is for UART to set the time		
		//==================================================				
		if(st_time)
		{
			SPI_WriteTime(hour_count,Hours);		// data , register address
			SPI_WriteTime(min_count,Minutes);
			st_time=0;
			SendUART1(hour_count);
			SendUART1(min_count);
		}	
		else
		{
			//UART
			//Delay_ms(1200);
		}
	}
	
} 




void Uart() interrupt 4 using 1
{
	if(RI) 
	{
		RX_Data_Uart_Cnt++;
		RI=0;
		if (RX_Data_Uart_Cnt<=2)
		Rec_data_hour[RX_Data_Uart_Cnt-1]=SBUF;
		else if (RX_Data_Uart_Cnt>=3)
		{
			//RI=0; //SW clear
			//P0=Rec_data;
			Rec_data_min[RX_Data_Uart_Cnt-3]=SBUF;
			if (RX_Data_Uart_Cnt==4)
			{
				RX_Data_Uart_Cnt=0;
				hour_count=ASCIItoBCD(Rec_data_hour);
				min_count=ASCIItoBCD(Rec_data_min);
				st_time=1;
				//SendUART1(hour_count);
				//SendUART1(min_count);
				//SPI_WriteTime(hour_count,Hours);		// data , register address
				//SPI_WriteTime(min_count,Minutes);
			}
		}

		
	}
	if(TI)
	{
		TI=0;
		busy=0;
	}
}


void SendUART1(unsigned char dat)
{
	while(busy);
	busy=1;
	ACC=dat;
	SBUF=ACC;
}
