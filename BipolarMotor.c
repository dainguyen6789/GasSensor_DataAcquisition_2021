#include "stc15f2k60s2.h"
#include "LCD_Driver_SPLC780D.h"
#include "Receiver_Position_Data.h"
#include "math.h"
//#include "PCF85963BTL.h"
void Delay_ms(unsigned int ms);
int Day_Of_Year(unsigned char months,unsigned char days);
unsigned char BCDtoDec1(char bcd);
float degree;

unsigned char BCDtoDec1(unsigned char bcd)
{
	unsigned char hi,lo;
	hi=bcd>>4;
	lo=bcd&0x0F;
	return hi*10+lo;
}





void Step_move(unsigned int step, bit dir)
{
			unsigned int i=0;
			if(dir)
				P4 |=(1<<2);// set bit P4.2
			else
				P4 &=~(1<<2);// clear bit P4.2
			
			for( i=0;i<step;i++)
			{
					P4 |=1<<1;// P41=1 // moving distance (mm)=pi^2*step*4/675
					Wait_ms(2);
					P4 &= ~(1<<1);
					Wait_ms(2);
			}
}

void Move(float distance, bit direction)
{
		unsigned int step;
		step= distance*337.5/(3.14159);
		Step_move(step,direction);
}




void Update_position(unsigned char mnths,unsigned char dys,unsigned char hurs,unsigned char mns,unsigned char sconds,int *currnt_pos)
{
	int date,i;
	int desired_distance,distance;
	/*hurs=0x12;
	mns=0x30;*/
	//sconds=0x15;
	date=Day_Of_Year(mnths,dys);
	//date=80;
	for(i=0;i<47;i++)// time stamp from 12PM to 15PM, 47 diff values of time stamp
	{
		if (BCDtoDec1(hurs)==Time_stamp_PM[i][0] && BCDtoDec1(mns)== Time_stamp_PM[i][1] && BCDtoDec1(sconds&0x7f)==Time_stamp_PM[i][2])// check if current time match the time stamp in the table
		{			
			switch(date)
			{
				case 79:
					desired_distance=receiver_pos[i][0];
					break;
				case 80:
					desired_distance=receiver_pos[i][1];
					break;
				case 81:
					desired_distance=receiver_pos[i][2];
					break;
				case 82:
					desired_distance=receiver_pos[i][3];
					break;
				case 83:
					desired_distance=receiver_pos[i][4];
					break;
			}
			//desired_distance=receiver_pos[0][4];;
			//distance=11;
			distance=desired_distance-*currnt_pos;
			*currnt_pos=desired_distance;
			if(distance>0)
			{
				Move(abs(distance),1);// counter clock wise
			}
			else if(distance<0)
			{
				Move(abs(distance),0);// clock wise
			}
			
			break;
		}
	}
}

//int Day_Of_Year(unsigned char months,unsigned char days)*/