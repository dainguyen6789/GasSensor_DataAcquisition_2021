#include "AT25SF041.h"
#include "stc15f2k60s2.h"
//unsigned char ucRead_Status_Register_Byte1(void);

void Wait_ms_SPINOR(int ms)
{
  unsigned int De_Cnt;
  while( (ms--) != 0)
  {
    for(De_Cnt = 0; De_Cnt < 4; De_Cnt++); 
  }  	
}
void AT25SF041_ChipErase(void)
{
	int i;
	unsigned char opcode;
	opcode=Chip_Erase;
	//P4M1|=0x10;
	//P4M0&=~(1<<4);
	P4M1&=~(1<<1 |1<<2|1<<3);
	P4M0|=0x07;
	AT25SF041_CS_Clr();
	Wait_ms_SPINOR(5);
	
	for( i=0;i<8;i++)
	{
				AT25SF041_SCK_Clr();
				Wait_ms_SPINOR(5);
				if( (opcode&0x80)==0x80 )	  	 //
				{
						AT25SF041_SDI_Set();
				}	
					else
				{
						AT25SF041_SDI_Clr();

				}
				Wait_ms_SPINOR(5); 		
				AT25SF041_SCK_Set();
				Wait_ms_SPINOR(5);
				opcode <<= 1;                   //


	}
	
	AT25SF041_CS_Set();
	Wait_ms_SPINOR(10);
	while(ucRead_Status_Register_Byte1()&0x01==0x01);
	
}
void AT25SF041_WriteEnable(void)
{
	int i;
	unsigned char write_en;
	write_en=Write_Enable;
	AT25SF041_CS_Clr();
//Wait_ms_SPINOR(5);
	
	for( i=0;i<8;i++)
	{
				AT25SF041_SCK_Clr();
				Wait_ms_SPINOR(5);
				if( (write_en&0x80)==0x80 )	  	 //
				{
						AT25SF041_SDI_Set();
				}	
					else
				{
						AT25SF041_SDI_Clr();

				}
				Wait_ms_SPINOR(5); 		
				AT25SF041_SCK_Set();
				Wait_ms_SPINOR(5);
				write_en <<= 1;                   //


	}
	AT25SF041_CS_Set();
	Wait_ms_SPINOR(5);
	while(ucRead_Status_Register_Byte1()&0x01==0x01);
}


void AT25SF041_Write(unsigned char opcode, unsigned long int addr,unsigned char dat)
{
	int i;
	AT25SF041_CS_Clr();
	Wait_ms_SPINOR(5);

	//////////////////////////////////////////
	for( i=0;i<8;i++)
		{
				AT25SF041_SCK_Clr();
				Wait_ms_SPINOR(5);
				if( (opcode&0x80)==0x80 )	  	 //
				{
						AT25SF041_SDI_Set();
				}	
					else
				{
						AT25SF041_SDI_Clr();

				}
				Wait_ms_SPINOR(5); 		
				AT25SF041_SCK_Set();
				Wait_ms_SPINOR(5);
				opcode <<= 1;                   //


		}
	// SEND THE ADDR (24-bit)
	for( i=0;i<24;i++)
	{
			AT25SF041_SCK_Clr();
			Wait_ms_SPINOR(5);
			if( (addr&0x00800000)==0x00800000 )	  	 //
			{
					AT25SF041_SDI_Set();
			}	
				else
			{
					AT25SF041_SDI_Clr();

			}
			Wait_ms_SPINOR(5); 		
			AT25SF041_SCK_Set();
			Wait_ms_SPINOR(5);
			addr <<= 1;

	}
	
		for( i=0;i<8;i++)
	{
			AT25SF041_SCK_Clr();
			Wait_ms_SPINOR(5);
			if( (dat&0x80)==0x80 )	  	 //
			{
					AT25SF041_SDI_Set();
			}	
				else
			{
					AT25SF041_SDI_Clr();

			}
			Wait_ms_SPINOR(5); 		
			AT25SF041_SCK_Set();
			Wait_ms_SPINOR(5);
			dat <<= 1;

	}
	///////////////////////////////////////
	AT25SF041_CS_Set();
	Wait_ms_SPINOR(5);
	while(ucRead_Status_Register_Byte1()&0x01==0x01);

}

unsigned char  AT25SF041_Read(unsigned char opcode,unsigned long int addr)
{
	unsigned char dat=0;
	int i;
	AT25SF041_CS_Clr();
	Wait_ms_SPINOR(5);

	//////////////////////////////////////////
	// Send the OPCODE
	for( i=0;i<8;i++)
	{
			AT25SF041_SCK_Clr();
			Wait_ms_SPINOR(5);
			if( (opcode&0x80)==0x80 )	  	 //
			{
					AT25SF041_SDI_Set();
			}	
				else
			{
					AT25SF041_SDI_Clr();

			}
			Wait_ms_SPINOR(5); 		
			AT25SF041_SCK_Set();
			Wait_ms_SPINOR(5);
			opcode <<= 1;                   //


	}
	// SEND THE ADDR (24-bit)
	for( i=0;i<24;i++)
	{
			AT25SF041_SCK_Clr();
			Wait_ms_SPINOR(5);
			if( (addr&0x00800000)==0x00800000 )	  	 //
			{
					AT25SF041_SDI_Set();
			}	
				else
			{
					AT25SF041_SDI_Clr();

			}
			Wait_ms_SPINOR(5); 		
			AT25SF041_SCK_Set();
			Wait_ms_SPINOR(5);
			addr <<= 1;

	}
	/////////////////////////////////////////
	// Store the output data from NOR FLash
	Wait_ms_SPINOR(10);

	AT25SF041_SDO_Set();
	Wait_ms_SPINOR(2);
	
	for( i=0;i<8;i++)
	{
			dat <<= 1;	              //
			AT25SF041_SCK_Set();
			Wait_ms_SPINOR(5);
			AT25SF041_SCK_Clr();
			Wait_ms_SPINOR(5);

			if(AT25SF041_SDO)
			{
				// INPUT BIT =1
				dat |= 0x01;            //
			}

			//Wait_ms_SPINOR(5); 
			//AT25SF041_SCK_Set();
			//Wait_ms_SPINOR(5);

	}	
	
	///////////////////////////////////////
	AT25SF041_CS_Set();	
	Wait_ms_SPINOR(5);
	while(ucRead_Status_Register_Byte1()&0x01==0x01);

	return dat;

}



unsigned char ucRead_Status_Register_Byte1(void)
{
	unsigned char dat=0,opcode,count=0;
	int i=0;
	opcode=Read_Stat_Register_Byte1;
	AT25SF041_CS_Clr();
	Wait_ms_SPINOR(5);

	//////////////////////////////////////////
	// Send the OPCODE
	for( i=0;i<8;i++)
	{
			AT25SF041_SCK_Clr();
			Wait_ms_SPINOR(5);
			if( (opcode&0x80)==0x80 )	  	 //
			{
					AT25SF041_SDI_Set();
			}	
				else
			{
					AT25SF041_SDI_Clr();

			}
			Wait_ms_SPINOR(5); 		
			AT25SF041_SCK_Set();
			Wait_ms_SPINOR(5);
			opcode <<= 1;                   //


	}

	/////////////////////////////////////////
	// Store the output data from NOR FLash
	Wait_ms_SPINOR(10);

	AT25SF041_SDO_Set();
	Wait_ms_SPINOR(2);
	for( i=0;i<8;i++)
	{
			dat <<= 1;	              //
			AT25SF041_SCK_Set();
			Wait_ms_SPINOR(5);
			AT25SF041_SCK_Clr();
			Wait_ms_SPINOR(5);

			if(AT25SF041_SDO)
			{
				// INPUT BIT =1
				dat |= 0x01;            //
			}

	}	
	
	
	///////////////////////////////////////
	AT25SF041_CS_Set();	
	Wait_ms_SPINOR(5);
	return dat;
}

void SPI_NOR_Write_Data(struct data_to_store dat,unsigned long int *addr)
{
						
	AT25SF041_WriteEnable();
	//Wait_ms_SPINOR(50);	
	AT25SF041_Write(Byte_Page_Program, *addr,dat.month);
	++*addr;
	
	Wait_ms_SPINOR(50);	
	AT25SF041_WriteEnable();
	//Wait_ms_SPINOR(50);	
	AT25SF041_Write(Byte_Page_Program, *addr,dat.date);	
	Wait_ms_SPINOR(50);	
	++*addr;


	AT25SF041_WriteEnable();
	//Wait_ms_SPINOR(50);	
	AT25SF041_Write(Byte_Page_Program, *addr,dat.hour);	
	Wait_ms_SPINOR(50);	
	++*addr;

	AT25SF041_WriteEnable();
	//Wait_ms_SPINOR(50);	
	AT25SF041_Write(Byte_Page_Program, *addr,dat.min);
	Wait_ms_SPINOR(50);	
	++*addr;

	AT25SF041_WriteEnable();
	//Wait_ms_SPINOR(50);	
	AT25SF041_Write(Byte_Page_Program, *addr,dat.calib_max_voltage_ADC);		
	Wait_ms_SPINOR(50);	
	++*addr;
	
	AT25SF041_WriteEnable();
	//Wait_ms_SPINOR(50);	
	AT25SF041_Write(Byte_Page_Program, *addr,dat.calib_max_pos_floor);
	Wait_ms_SPINOR(50);	
	++*addr;
	
	AT25SF041_WriteEnable();
	//Wait_ms_SPINOR(50);	
	AT25SF041_Write(Byte_Page_Program, *addr,dat.calib_max_pos_float);
	Wait_ms_SPINOR(50);	
	++*addr;
	
	AT25SF041_WriteEnable();
	//Wait_ms_SPINOR(50);	
	AT25SF041_Write(Byte_Page_Program, *addr,dat.light_ADC);	
	Wait_ms_SPINOR(50);	
	++*addr;

	AT25SF041_WriteEnable();
	//Wait_ms_SPINOR(50);
	AT25SF041_Write(Byte_Page_Program, *addr,dat.Voltage_at_LUT_pos);	
	Wait_ms_SPINOR(50);	
	++*addr;
	
	AT25SF041_WriteEnable();
	//Wait_ms_SPINOR(50);	
	AT25SF041_Write(Byte_Page_Program, *addr,dat.LUT_max_pos_floor);	
	Wait_ms_SPINOR(50);	
	++*addr;
	
	AT25SF041_WriteEnable();
	//Wait_ms_SPINOR(50);	
	AT25SF041_Write(Byte_Page_Program, *addr,dat.LUT_max_pos_float);	
	Wait_ms_SPINOR(50);	
	++*addr;


}

