/*
 * LCD_DRIVER.c
 *
 * Created: 8/13/2023 8:33:31 PM
 *  Author: johnr
 */ 

#include "LCD_DRIVER.h"

#define F_CPU 8000000UL
#include <util/delay.h>


void LCD_init(void)
{
	#if defined EIGHT_BITS_MODE
	_delay_ms(200);
	DIO_Set_Port_Direction(DATA_PORT,0XFF);
	DIO_SetPinDir(CONTROL_PORT,EN,1);
	DIO_SetPinDir(CONTROL_PORT,RS,1);
	
	LCD_Send_Cmd(EIGHT_BITS); //8 bit mode
	_delay_ms(1);
	LCD_Send_Cmd(CURSOR_ON_DISPLAY_ON);//display on cursor on
	_delay_ms(1);
	LCD_Send_Cmd(CLEAR_SCREEN);//clear the screen
	_delay_ms(10);
	LCD_Send_Cmd(ENTRY_MODE); //entry mode
	_delay_ms(1);	
	
	#elif defined FOUR_BITS_MODE_HIGH_NIBBLE
    _delay_ms(200);	
	DIO_Set_Port_Direction(DATA_PORT,0XF0);
	DIO_SetPinDir(CONTROL_PORT,EN,1);
    DIO_SetPinDir(CONTROL_PORT,RS,1);
	
	LCD_Send_Cmd(RETURN_HOME);
	_delay_ms(5);
	LCD_Send_Cmd(FOUR_BITS);
	_delay_ms(1);
	LCD_Send_Cmd(CURSOR_ON_DISPLAY_ON);
	_delay_ms(1);
	LCD_Send_Cmd(CLEAR_SCREEN);
	_delay_ms(5);
	LCD_Send_Cmd(ENTRY_MODE);
	_delay_ms(1);
	
	#elif defined FOUR_BITS_MODE_LOW_NIBBLE
	_delay_ms(200);
	 DIO_Set_Port_Direction(DATA_PORT,0X0F);
	 DIO_SetPinDir(CONTROL_PORT,EN,1);
	 DIO_SetPinDir(CONTROL_PORT,RS,1);
	 
	 LCD_Send_Cmd(RETURN_HOME);
	 _delay_ms(5);
	 LCD_Send_Cmd(FOUR_BITS);
	 _delay_ms(1);
	 LCD_Send_Cmd(DISPLAY_ON_CURSOR_ON);
	 _delay_ms(1);
	 LCD_Send_Cmd(CLEAR_SCREEN);
	 _delay_ms(5);
	 LCD_Send_Cmd(ENTRY_MODE);
	 _delay_ms(1);
	 
	#endif
		
	
}





void LCD_Send_Cmd(unsigned char cmd)
{
	#if defined EIGHT_BITS_MODE
	
		  DIO_Write(CONTROL_PORT,RS,0);
	      DIO_Write_Port(DATA_PORT,cmd);
	      enable();
	     _delay_ms(1);
		 
    #elif defined FOUR_BITS_MODE_HIGH_NIBBLE

		  DIO_Write_high_nibble(DATA_PORT,cmd>>4);
		  DIO_Write(CONTROL_PORT,RS,0);
		  enable();
		  _delay_ms(1);
		  DIO_Write_high_nibble(DATA_PORT,cmd);
		  enable();
		  _delay_ms(1);
		  
	#elif  defined FOUR_BITS_MODE_LOW_NIBBLE
	
		  DIO_Write_low_nibble(DATA_PORT,cmd>>4);
		  DIO_Write(CONTROL_PORT,RS,0);
		  enable();
		  _delay_ms(1);
		  DIO_Write_low_nibble(DATA_PORT,cmd);
		  enable();
		  _delay_ms(1);
		  
	#endif
	   
}



 void enable()
{
	DIO_Write(CONTROL_PORT,EN,1);
	_delay_ms(3);
	DIO_Write(CONTROL_PORT,EN,0);
}



void LCD_Send_Char(unsigned char data)
{
	#if defined EIGHT_BITS_MODE
	    DIO_Write(CONTROL_PORT,RS,1);
	    DIO_Write_Port(DATA_PORT,data);
	    enable();
	    _delay_ms(1);
	#elif defined FOUR_BITS_MODE_HIGH_NIBBLE
	     DIO_Write(CONTROL_PORT,RS,1);
		 DIO_Write_high_nibble(DATA_PORT,data>>4);
		 enable();
		 DIO_Write_high_nibble(DATA_PORT,data);
		 enable();
		 _delay_ms(1);
	#elif defined FOUR_BITS_MODE_LOW_NIBBLE
	     DIO_Write(CONTROL_PORT,RS,1);
		 DIO_Write_low_nibble(DATA_PORT,data>>4);
		 enable();
		 DIO_Write_low_nibble(DATA_PORT,data);
		 enable();
		 _delay_ms(1);
	#endif
	   
}



void LCD_String(char *ptr)
{
	while((*ptr)!='\0')
	{
		LCD_Send_Char(*ptr);
		ptr++;
	
	}
}



void LCD_Clear_Screen()
{
	LCD_Send_Cmd(CLEAR_SCREEN);
	_delay_ms(10);
}



void LCD_Move_cursor(unsigned char row,unsigned char column)
{
	char data=0; 
	if ((row<1)||(row>2)||(column<1)||(column>16))
	{
		data=0x08;
	}
	if (row==1)
	{
		data=0X80+column-1;
	}
	if(row==2)
	{
		data=0XC0+column-1;
	}
	LCD_Send_Cmd(data);
}


void LCD_Return_Home()
{
	LCD_Send_Cmd(RETURN_HOME);
}