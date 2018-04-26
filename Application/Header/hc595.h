#ifndef __HC595_H__
#define __HC595_H__

#include "stc15f2k60s2.h"

//HC595�ӿڶ���
sbit 			HC595_DAT		=	P3^7;	   //HC595����������
sbit 			HC595_SCK		=	P4^2;	   //HC595��λʱ����
sbit 			HC595_RCK		=	P4^1;	   //HC595����ʱ����
sbit 			HC595_OE		=	P4^5;	   //HC595���������
																
//�����λ���壬������������Ϊ1~8λ
#define		DIG1				0		
#define		DIG2				1	
#define		DIG3				2		
#define		DIG4				3	
#define		DIG5				4	
#define		DIG6				5	
#define		DIG7				6			
#define		DIG8				7																	

//�˿ڲ�������
#define 	SET	   			1			   //�ߵ�ƽ
#define 	CLR	   			0			   //�͵�ƽ

//�˿ڲ���
#define		HC595_DAT_Clr()	{HC595_DAT=CLR;} 	//�˿��õ�
#define		HC595_DAT_Set()	{HC595_DAT=SET;}	//�˿��ø�

#define		HC595_SCK_Clr()	{HC595_SCK=CLR;} 
#define		HC595_SCK_Set()	{HC595_SCK=SET;}

#define		HC595_RCK_Clr()	{HC595_RCK=CLR;} 
#define		HC595_RCK_Set()	{HC595_RCK=SET;}

#define		HC595_OE_Clr()	{HC595_OE=CLR;} 
#define		HC595_OE_Set()	{HC595_OE=SET;}


 //�ⲿ����
 void HC595_Init(void);
 void LED_Display(void);
 void ToDisplayCorrect(void);
 void ToDisplayError(void);

#endif