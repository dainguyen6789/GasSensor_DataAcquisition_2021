#ifndef __A25LC040_H__
#define __A25LC040_H__

#include "stc15f2k60s2.h"

//A25LC040�ӿڶ���
 sbit 			A25LC040_CS		=	P2^0;	   //A25LC040Ƭѡ��
 sbit 			A25LC040_SCK	=	P2^1;	   //A25LC040ʱ�Ӷ�
 sbit 			A25LC040_SDI	=	P2^3;	   //A25LC040���������
 sbit 			A25LC040_SDO	=	P2^2;	   //A25LC040���������

//�˿ڲ���
 #define		A25LC040_CS_Clr()			{A25LC040_CS=0;} //�õ�
 #define		A25LC040_CS_Set()			{A25LC040_CS=1;} //�ø�

 #define		A25LC040_SCK_Clr()		{A25LC040_SCK=0;} 
 #define		A25LC040_SCK_Set()		{A25LC040_SCK=1;}

 #define		A25LC040_SDI_Clr()		{A25LC040_SDI=0;} 
 #define		A25LC040_SDI_Set()		{A25LC040_SDI=1;}

 #define		A25LC040_SDO_Clr()		{A25LC040_SDO=0;} 
 #define		A25LC040_SDO_Set()		{A25LC040_SDO=1;}
 
 //25LC040A�Ĵ�������
 #define		READH		0x0b		//��ȡ��256�ֽڵ�Ԫ
 #define		READL		0x03		//��ȡ��256�ֽڵ�Ԫ
 #define		WRITEH	0x0a		//д��256�ֽڵ�Ԫ
 #define		WRITEL	0x02		//д��256�ֽڵ�Ԫ
 #define		WREN		0x06		//дʹ��
 #define		WRDI		0x04		//д��ֹ
 #define		RDSR		0x05		//��״̬�Ĵ���
 #define		WRSR		0x01		//д״̬�Ĵ���

//�ⲿ��������
void A25LC040_Init(void);
unsigned char A25LC040_ReadByte(unsigned int addt);
void A25LC040_WriteByte(unsigned int add,unsigned char dat);

#endif