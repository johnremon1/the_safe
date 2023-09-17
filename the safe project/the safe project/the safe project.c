/*
 * the_safe_project.c
 *
 * Created: 8/19/2023 10:32:43 PM
 *  Author: johnr
 */ 



#include "functions.h"


int main(void)
{
	//EEPROM_Write(FIRST_TIME_LOCATION,0);//temporary command
	//EEPROM_Write(TRIES_LOCATION,NUMBER_OF_TRIES);//temporary command
	LCD_init();
	Keypad_init();
	Button_vinit(OUTPUTS_PORT,RIGHT_BUTTON);	
	Button_vinit(OUTPUTS_PORT,OK_BUTTON);
	Button_vinit(OUTPUTS_PORT,LEFT_BUTTON);
	Led_vinit(OUTPUTS_PORT,GREEN_LED);
	Led_vinit(OUTPUTS_PORT,GREEN_LED);
	Led_vinit(OUTPUTS_PORT,RED_LED);
	Led_vinit(OUTPUTS_PORT,BUZZER_PIN);
	Led_von(OUTPUTS_PORT,RESET_PIN);
	Led_vinit(OUTPUTS_PORT,RESET_PIN);
	LCD_Send_Cmd(DISPLAY_OFF_CURSOR_OFF);
	if (EEPROM_u8Read(WE_ARE_IN_EMERGNCY_LOCATION)==1)
	{
		emergency_mood();
	}
	LCD_Move_cursor(1,4);
	LCD_String("WELCOME TO ");
	LCD_Move_cursor(2,5);
	LCD_String("THE SAFE");
	LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);
	_delay_ms(2000);
	Led_von(OUTPUTS_PORT,RED_LED);
	Led_voff(OUTPUTS_PORT,GREEN_LED);
	RED_MOOD;//this means to turn the red led on and turn the green led off
	
	if (EEPROM_u8Read(FIRST_TIME_LOCATION)==0)//this protocol is for first time log in 
	{
	  creat_new_password();
	  EEPROM_Write(FIRST_TIME_LOCATION,5);
	}
	unsigned char position=0;//this variable is for controlling the choice you want in the following choices 
	unsigned char enable =1;//this function is for taking action every time this variable is one and after taking the action it returns zero again and another action is needed
    while(1)
    {
	   if (enable==1)
	   {
		   LCD_Send_Cmd(DISPLAY_OFF_CURSOR_OFF);
		 switch ( position )
		 {
			case 0:
			        LCD_Clear_Screen();
					LCD_Send_Cmd(RETURN_HOME);
					LCD_String("write password");
					LCD_CHOICES_CONTROLE;
			break;
			
			case 1:
			        LCD_Clear_Screen();
			        LCD_Send_Cmd(RETURN_HOME);
			        LCD_String("write OTP");
			        LCD_CHOICES_CONTROLE;
			break;
			
			case 2:
			        LCD_Clear_Screen();
			        LCD_Send_Cmd(RETURN_HOME);
			        LCD_String("create OTP");
			        LCD_CHOICES_CONTROLE;
			break;
			 
			case 3:
			        LCD_Clear_Screen();
			        LCD_Send_Cmd(RETURN_HOME);
			        LCD_String("change password");
			        LCD_CHOICES_CONTROLE;
			break;
			
			case 4:
			        LCD_Clear_Screen();
			        LCD_Send_Cmd(RETURN_HOME);
			        LCD_String("factory reset");
			        LCD_CHOICES_CONTROLE;
			break; 
		 }	
		 LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);		 			    
		enable=0;   
	   }
      if (Button_u8read(OUTPUTS_PORT,RIGHT_BUTTON)==1)
	   {
		   if (position==4)
		   {
			   position=0;
		   }
		   else
		   {
			   position++;
		   }
		  while (Button_u8read(OUTPUTS_PORT,RIGHT_BUTTON)==1); 
		 enable=1; //this means that in the other loop you need to take action  
	   }	
	   else if (Button_u8read(OUTPUTS_PORT,LEFT_BUTTON)==1)
	   {
		  if (position==0)
		  {
			  position=5;
		  }			   
		  else
		  {
			  position--;
		  }			  
		  while (Button_u8read(OUTPUTS_PORT,LEFT_BUTTON)==1);
		   enable=1 ;//this means that in the other loop you need to take action   
	   }		   	   		   	
	  else if (Button_u8read(OUTPUTS_PORT,OK_BUTTON)==1)
	  {
		  while(Button_u8read(OUTPUTS_PORT,OK_BUTTON)==1);
		  
		  switch (position)
		  {
			 case 0:
			      if (write_password()==1)
				  {
					  open_the_safe();
				  }					  
				  enable=1; 
			 break;
			 
			 case 1:
			      if (write_otp()==1)
				  {
					open_the_safe();  
				  }					  
                  enable=1;
			 break;
			 
			 case 2:
			       create_otp();
				   enable=1;
			 break;
			 
			 case 3:
			      change_password();
				  enable=1;
			 break;
			 
			 case 4:
			       reset();
				  enable=1;
			 break;
			   
		  }

	  }
	  		  
		

    }
}






