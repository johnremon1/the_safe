/*
 * functions.c
 *
 * Created: 8/31/2023 5:24:22 PM
 *  Author: johnr
 */ 

#include "functions.h"



void creat_new_password()
{
	LCD_Send_Cmd(DISPLAY_OFF_CURSOR_OFF);
	LCD_Clear_Screen();
	LCD_String("create password: "); //we need to read from the lcd in this stage so we will what to learn it
	LCD_Move_cursor(2,1);
	LCD_Send_Char('<');
	LCD_Move_cursor(2,15);
	LCD_Send_Char('>');
	LCD_Move_cursor(2,5);
	
	for (int i=0;i<6;i++)
	{
		LCD_Send_Char('_');
	}
	LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);
	LCD_Move_cursor(2,5);
	
	LCD_Send_Cmd(DISPLAY_ON_CURSOR_BLINKING);
	unsigned char position=0;//this varibale is for the programmer as an indication of the cursor location and it can vary from 0 to 5 as we have 6 digit password
unsigned char password[6]={0,0,0,0,0,0};//the most important variable in the function as it holds each digit of the passward in each varible of the array so we can store it in the futur in the eeprom
unsigned char keypad=0;//this variable holds the keypad return value
while(1)
{
	keypad=Keypad_u8check_press();
	if (keypad!=0xFF)
	{
		LCD_Send_Char(keypad);
		password[position]=keypad;
		position++;

		
		if (position>=6)
		{
			position=5;
			LCD_Send_Cmd(SHIFT_CURSOR_LEFT);
		}
		_delay_ms(250);
		
	}
	else if (Button_u8read(OUTPUTS_PORT,RIGHT_BUTTON)==1)//this means that the user wants to move the cursor right as the user could write any number wrong and want to edit it
	{
		if (position<5)//this because we only have 6 digits so if the user in the digit number 6 the cursor cant move to the right more
		{
			LCD_Send_Cmd(SHIFT_CURSOR_RIGHT);
			position++;
		}
		while(Button_u8read(OUTPUTS_PORT,RIGHT_BUTTON)==1); //waiting the user to let the button free
	}
	
	
	else if (Button_u8read(OUTPUTS_PORT,LEFT_BUTTON)==1)//the same of the right button but to the left
	{
		if(position>0)
		{
			LCD_Send_Cmd(SHIFT_CURSOR_LEFT);
			position--;
		}
		while(Button_u8read(OUTPUTS_PORT,LEFT_BUTTON)==1);
	}
	else if (Button_u8read(OUTPUTS_PORT,OK_BUTTON)==1)//this button means that the user enter all the password and want the program to save it
	{
		for (unsigned char i=0;i<6;i++)
		{
			EEPROM_Write(PASSWORD_LOCATION1+i,password[i]);
		}
		while(Button_u8read(OUTPUTS_PORT,OK_BUTTON)==1);
		
		Confirm_password();	//this is the confirmation password
		break;
	}
	
}
}


void Confirm_password()
{
		LCD_Send_Cmd(DISPLAY_OFF_CURSOR_OFF);
		LCD_Clear_Screen();
		LCD_String("confirm password: "); //we need to read from the lcd in this stage so we will what to learn it
		LCD_Move_cursor(2,1);
		LCD_Send_Char('<');
		LCD_Move_cursor(2,15);
		LCD_Send_Char('>');
		LCD_Move_cursor(2,5);
		for (int i=0;i<6;i++)
		{
			LCD_Send_Char('_');
		}
		LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);
		LCD_Move_cursor(2,5);
		
		LCD_Send_Cmd(DISPLAY_ON_CURSOR_BLINKING);//every varible is doing the function from the creat password function
	unsigned char position=0;
	unsigned char password[6]={0,0,0,0,0,0};
	unsigned char keypad=0;
	while(1)
	{
		keypad=Keypad_u8check_press();
		if (keypad!=0xFF)
		{   
			 LCD_Send_Char(keypad);
			 password[position]=keypad;
			 position++;

			 
			 if (position>=6)
			 {
				 position=5;
				 LCD_Send_Cmd(SHIFT_CURSOR_LEFT);
			 }
			 _delay_ms(250);
			 
		 }
		 else if (Button_u8read(OUTPUTS_PORT,RIGHT_BUTTON)==1)
		 {
			 if (position<5)
			 {
				 LCD_Send_Cmd(SHIFT_CURSOR_RIGHT);
				 position++;
			 }
			 while (Button_u8read(OUTPUTS_PORT,RIGHT_BUTTON)==1);
		 }
		 
		 
		 else if (Button_u8read(OUTPUTS_PORT,LEFT_BUTTON)==1)
		 {
			 if(position>0)
			 {
				 LCD_Send_Cmd(SHIFT_CURSOR_LEFT);
				 position--;
			 }
			 while (Button_u8read(OUTPUTS_PORT,LEFT_BUTTON)==1);
		 }
		 
		 
		else if (Button_u8read(OUTPUTS_PORT,OK_BUTTON)==1)//if the password is right then go out of the function but if it wrong go to create password function again
		{
			if ((password[0]==EEPROM_u8Read(PASSWORD_LOCATION1))&&(password[1]==EEPROM_u8Read(PASSWORD_LOCATION2))&&(password[2]==EEPROM_u8Read(PASSWORD_LOCATION3))&&(password[3]==EEPROM_u8Read(PASSWORD_LOCATION4))&&(password[4]==EEPROM_u8Read(PASSWORD_LOCATION5))&&(password[5]==EEPROM_u8Read(PASSWORD_LOCATION6)))
			{	
				GREEN_MOOD;
				open_the_safe();
				break;
			}

			else
			{
				LCD_Clear_Screen();
				LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);
				LCD_String("you entered a");
				LCD_Move_cursor(2,1);
				LCD_String("wrong password");
				_delay_ms(2000);
				LCD_Clear_Screen();
				LCD_String("create the");
				LCD_Move_cursor(2,1);
				LCD_String("password again");
				_delay_ms(2000);
				creat_new_password();//we are going back to creat the password again	
				break;			
			}
			while (Button_u8read(OUTPUTS_PORT,OK_BUTTON)==1);
		}
		
	}
	
}


void open_the_safe()
{
	LCD_Clear_Screen();
	EEPROM_Write(TRIES_LOCATION,NUMBER_OF_TRIES);
	LCD_String("the safe is opened");
	_delay_ms(3000);
	RED_MOOD;
	
	
		
}


unsigned char write_password()
{
 
   if (EEPROM_u8Read(TRIES_LOCATION)==0)
	{
		LCD_Clear_Screen();
		LCD_String("no more tries");
		LCD_Move_cursor(2,1);
		LCD_String("try again later");
		_delay_ms(3000);
		emergency_mood();
		return 0 ;
	}
	LCD_Send_Cmd(DISPLAY_OFF_CURSOR_OFF);
	LCD_Clear_Screen();
	LCD_String("the password: "); //we need to read from the lcd in this stage so we will what to learn it
	LCD_Move_cursor(2,1);
	LCD_Send_Char('<');
	LCD_Move_cursor(2,15);
	LCD_Send_Char('>');
	LCD_Move_cursor(2,5);
	for (int i=0;i<6;i++)
	{
		LCD_Send_Char('_');
	}
	LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);
	LCD_Move_cursor(2,5);
	
	LCD_Send_Cmd(DISPLAY_ON_CURSOR_BLINKING);//every variable is doing the function from the create password function
	unsigned char position=0;
    unsigned char password[6]={0,0,0,0,0,0};
     unsigned char keypad=0;
    while(1)
  {
	keypad=Keypad_u8check_press();
	if (keypad!=0xFF)
	{
		LCD_Send_Char(keypad);
		password[position]=keypad;
		position++;

		
		if (position>=6)
		{
			position=5;
			LCD_Send_Cmd(SHIFT_CURSOR_LEFT);
		}
		_delay_ms(250);
		
	}
	else if (Button_u8read(OUTPUTS_PORT,RIGHT_BUTTON)==1)
	{
		if (position<5)
		{
			LCD_Send_Cmd(SHIFT_CURSOR_RIGHT);
			position++;
		}
		while (Button_u8read(OUTPUTS_PORT,RIGHT_BUTTON)==1);
	}
	else if (Button_u8read(OUTPUTS_PORT,LEFT_BUTTON)==1)
	{
		if(position>0)
		{
			LCD_Send_Cmd(SHIFT_CURSOR_LEFT);
			position--;
		}
		while (Button_u8read(OUTPUTS_PORT,LEFT_BUTTON)==1);
	}
	
	
	else if (Button_u8read(OUTPUTS_PORT,OK_BUTTON)==1)//if the password is right then go out of the function but if it wrong go to create password function again
	{
		if ((password[0]==EEPROM_u8Read(PASSWORD_LOCATION1))&&(password[1]==EEPROM_u8Read(PASSWORD_LOCATION2))&&(password[2]==EEPROM_u8Read(PASSWORD_LOCATION3))&&(password[3]==EEPROM_u8Read(PASSWORD_LOCATION4))&&(password[4]==EEPROM_u8Read(PASSWORD_LOCATION5))&&(password[5]==EEPROM_u8Read(PASSWORD_LOCATION6)))
		{
			GREEN_MOOD;
			LCD_Clear_Screen();
			LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);
			LCD_String("right password");
			_delay_ms(3000);
		//	open_the_safe();//we removed it as we want this function to return 1 and use it any many other functions
			return 1;
		}

		else
		{
			EEPROM_Write(TRIES_LOCATION,EEPROM_u8Read(TRIES_LOCATION)-1);
			
			if (EEPROM_u8Read(TRIES_LOCATION)==0)
			{
				LCD_Clear_Screen();
				LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);
				LCD_String("no more tries");
			    LCD_Move_cursor(2,1);
				LCD_String("try again later");
				_delay_ms(3000);
				emergency_mood();
				return 0;	
			}
			else 
			{	
			LCD_Clear_Screen();
			LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);
			LCD_String("you entered a");
			LCD_Move_cursor(2,1);
			LCD_String("wrong password");
			_delay_ms(2000);
			LCD_Clear_Screen();
			LCD_String("number of tries");
			LCD_Move_cursor(2,1);
			LCD_String("left is ");
			LCD_Send_Char(EEPROM_u8Read(TRIES_LOCATION)+48);
			_delay_ms(2000);
			   return 0;//we we return zero this means that the user wrote a wrong password
			}			
		}
		while (Button_u8read(OUTPUTS_PORT,OK_BUTTON)==1);
	}
	
  }


  
}


unsigned char write_otp()
{
	 if (EEPROM_u8Read(OTP_TRIES_LOCATION)==0)
	 {
		 LCD_Clear_Screen();
		 LCD_String("no more tries");
		 LCD_Move_cursor(2,1);
		 LCD_String("try again later");
		 _delay_ms(3000);
		 emergency_mood();
		 return 0 ;
	 }
	if ((EEPROM_u8Read(OTP_LOCATION1)==0)&&(EEPROM_u8Read(OTP_LOCATION2)==0)&&(EEPROM_u8Read(OTP_LOCATION3)==0)&&(EEPROM_u8Read(OTP_LOCATION4)==0))
	{
		LCD_Clear_Screen();
		LCD_String("no OTP found");
		_delay_ms(2000);
		return 0;
	}
	 LCD_Send_Cmd(DISPLAY_OFF_CURSOR_OFF);
	 LCD_Clear_Screen();
	 LCD_String("the OTP is: "); //we need to read from the lcd in this stage so we will what to learn it
	 LCD_Move_cursor(2,1);
	 LCD_Send_Char('<');
	 LCD_Move_cursor(2,15);
	 LCD_Send_Char('>');
	 LCD_Move_cursor(2,5);
	 for (int i=0;i<4;i++)
	 {
		 LCD_Send_Char('_');
	 }
	 LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);
	 LCD_Move_cursor(2,5);
	 
	 LCD_Send_Cmd(DISPLAY_ON_CURSOR_BLINKING);//every variable is doing the function from the create password function
	 unsigned char position=0;
 unsigned char password[4]={0,0,0,0};
 unsigned char keypad=0;
 while(1)
 {
	 keypad=Keypad_u8check_press();
	 if (keypad!=0xFF)
	 {
		 LCD_Send_Char(keypad);
		 password[position]=keypad;
		 position++;

		 
		 if (position>=4)
		 {
			 position=3;
			 LCD_Send_Cmd(SHIFT_CURSOR_LEFT);
		 }
		 _delay_ms(250);
		 
	 }
	 else if (Button_u8read(OUTPUTS_PORT,RIGHT_BUTTON)==1)
	 {
		 if (position<3)
		 {
			 LCD_Send_Cmd(SHIFT_CURSOR_RIGHT);
			 position++;
		 }
		 while (Button_u8read(OUTPUTS_PORT,RIGHT_BUTTON)==1);
	 }
	 else if (Button_u8read(OUTPUTS_PORT,LEFT_BUTTON)==1)
	 {
		 if(position>0)
		 {
			 LCD_Send_Cmd(SHIFT_CURSOR_LEFT);
			 position--;
		 }
		 while (Button_u8read(OUTPUTS_PORT,LEFT_BUTTON)==1);
	 }
	 
	 
	 else if (Button_u8read(OUTPUTS_PORT,OK_BUTTON)==1)//if the password is right then go out of the function but if it wrong go to create password function again
	 {
		 
		 if ((password[0]==EEPROM_u8Read(OTP_LOCATION1))&&(password[1]==EEPROM_u8Read(OTP_LOCATION2))&&(password[2]==EEPROM_u8Read(OTP_LOCATION3))&&(password[3]==EEPROM_u8Read(OTP_LOCATION4)))
		 {
			 GREEN_MOOD;
			 LCD_Clear_Screen();
			 LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);
			 LCD_String("right password");
			 _delay_ms(3000);
			 //	open_the_safe();//we removed it as we want this function to return 1 and use it any many other functions
			 for (int i=0;i<4;i++)
			 {
				 EEPROM_Write(OTP_LOCATION1+i,0);
			 }
			 return 1;
		 }

		 else
		 {
			 EEPROM_Write(OTP_TRIES_LOCATION,EEPROM_u8Read(OTP_TRIES_LOCATION)-1);
			 
			 if (EEPROM_u8Read(TRIES_LOCATION)==0)
			 {
				 LCD_Clear_Screen();
				 LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);
				 LCD_String("no more tries");
				 LCD_Move_cursor(2,1);
				 LCD_String("try again later");
				 _delay_ms(3000);
				 emergency_mood();
				 return 0;
			 }
			 else
			 {
				 LCD_Clear_Screen();
				 LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);
				 LCD_String("you entered a");
				 LCD_Move_cursor(2,1);
				 LCD_String("wrong password");
				 _delay_ms(2000);
				 LCD_Clear_Screen();
				 LCD_String("number of tries");
				 LCD_Move_cursor(2,1);
				 LCD_String("left is ");
				 LCD_Send_Char(EEPROM_u8Read(OTP_TRIES_LOCATION)+48);
				 _delay_ms(2000);
				 return 0;//we we return zero this means that the user wrote a wrong password
			 }
		 }
		 while (Button_u8read(OUTPUTS_PORT,OK_BUTTON)==1);
	 }
 }   


	
}


void create_otp()
{
	LCD_Clear_Screen();
	LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);
	LCD_String("write original");
	LCD_Move_cursor(2,1);
	LCD_String("password first");
	_delay_ms(2000);
  if (write_password()==1)
 {
	LCD_Clear_Screen();
	LCD_Send_Cmd(DISPLAY_OFF_CURSOR_OFF);
	LCD_String("NEW OTP:");
	LCD_Move_cursor(2,1);
	LCD_Send_Char('<');
	LCD_Move_cursor(2,15);
	LCD_Send_Char('>');
	LCD_Move_cursor(2,5);

	for (int i=0;i<4;i++)
	{
		LCD_Send_Char('_');
	}
	LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);
	LCD_Move_cursor(2,5);

	LCD_Send_Cmd(DISPLAY_ON_CURSOR_BLINKING);

        unsigned char position=0;//this varibale is for the programmer as an indication of the cursor location and it can vary from 0 to 3 as we have 4 digit password
        unsigned char password[4]={0,0,0,0};//the most important variable in the function as it holds each digit of the passward in each varible of the array so we can store it in the future in the eeprom
        unsigned char keypad=0;//this variable holds the keypad return value
  while(1)
 {
	keypad=Keypad_u8check_press();
	if (keypad!=0xFF)
	{
		LCD_Send_Char(keypad);
		password[position]=keypad;
		position++;

		
		if (position>=4)
		{
			position=3;
			LCD_Send_Cmd(SHIFT_CURSOR_LEFT);
		}
		_delay_ms(250);
		
	}
	else if (Button_u8read(OUTPUTS_PORT,RIGHT_BUTTON)==1)//this means that the user wants to move the cursor right as the user could write any number wrong and want to edit it
	{
		if (position<3)//this because we only have 6 digits so if the user in the digit number 6 the cursor cant move to the right more
		{
			LCD_Send_Cmd(SHIFT_CURSOR_RIGHT);
			position++;
		}
		while(Button_u8read(OUTPUTS_PORT,RIGHT_BUTTON)==1); //waiting the user to let the button free
	}
	
	
	else if (Button_u8read(OUTPUTS_PORT,LEFT_BUTTON)==1)//the same of the right button but to the left
	{
		if(position>0)
		{
			LCD_Send_Cmd(SHIFT_CURSOR_LEFT);
			position--;
		}
		while(Button_u8read(OUTPUTS_PORT,LEFT_BUTTON)==1);
	}
	else if (Button_u8read(OUTPUTS_PORT,OK_BUTTON)==1)//this button means that the user enter all the password and want the program to save it
	{
		if ((password[0]==0)&&(password[1]==0)&&(password[2]==0)&&(password[3]==0))
		{
			LCD_Clear_Screen();
			LCD_String("WRONG FORMAT");
			_delay_ms(2000);
			LCD_Clear_Screen();
			LCD_String("YOU CA NOT");
			LCD_Move_cursor(2,1);
			LCD_String("ENTER ALL 0");
		}
		else
		{
		for (unsigned char i=0;i<4;i++)
		{
			EEPROM_Write(OTP_LOCATION1+i,password[i]);
		}
		EEPROM_Write(OTP_TRIES_LOCATION,OTP_NUMBER_OF_TRIES);
		LCD_Clear_Screen();
		LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);
		LCD_String("OTP created");
		LCD_Move_cursor(2,1);
		LCD_String("successfully");
		_delay_ms(3000);
		while(Button_u8read(OUTPUTS_PORT,OK_BUTTON)==1);
		}		

		break;
	}
	
  }
	
}
else
{
	LCD_Clear_Screen();
	LCD_String("no OTP");
	LCD_Move_cursor(2,1);
	LCD_String("created");		
}	
	
}


void change_password()
{
	LCD_Clear_Screen();
	LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);
	LCD_String("write original");
	LCD_Move_cursor(2,1);
	LCD_String("password first");
	_delay_ms(2000);
	if (write_password()==1)
	{
		creat_new_password();
	}
	else
	{
		LCD_Clear_Screen();
		LCD_String("password not");
		LCD_Move_cursor(2,1);
		LCD_String("changed");
		_delay_ms(3000);
	}
	
}




void reset()
{
	LCD_Clear_Screen();
	LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);
	LCD_String("write original");
	LCD_Move_cursor(2,1);
	LCD_String("password first");
	_delay_ms(2000);
	if (write_password()==1)
	{
		LCD_Clear_Screen();
		LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);
		LCD_String("factory reset");
		_delay_ms(3000);
		for (unsigned char i=0;i<6;i++)
		{
			EEPROM_Write(PASSWORD_LOCATION1+i,0);
		}
		for (unsigned char i=0;i<4;i++)
		{
			EEPROM_Write(OTP_TRIES_LOCATION+i,0);
		}
		EEPROM_Write(TRIES_LOCATION,NUMBER_OF_TRIES);
		EEPROM_Write(FIRST_TIME_LOCATION,0);
		EEPROM_Write(OTP_TRIES_LOCATION,OTP_NUMBER_OF_TRIES);
		LCD_Clear_Screen();
		LCD_String("all data");
		LCD_Move_cursor(2,1);
		LCD_String("cleared ");
		Led_von(OUTPUTS_PORT,GREEN_LED);
		Led_von(OUTPUTS_PORT,RED_LED);
		Led_von(OUTPUTS_PORT,BUZZER_PIN);
		for (int i=0;i<7;i++)
		{
		Led_vtoggle(OUTPUTS_PORT,GREEN_LED);
		Led_vtoggle(OUTPUTS_PORT,RED_LED);
		Led_vtoggle(OUTPUTS_PORT,BUZZER_PIN);
		_delay_ms(500);
		}
		Led_voff(OUTPUTS_PORT,RESET_PIN);
				
	}
	else
	{
	  LCD_Clear_Screen();
	  LCD_String("no reset done");	
	  _delay_ms(3000);
	  
	}
	
	
}






void emergency_mood()
{
	EEPROM_Write(WE_ARE_IN_EMERGNCY_LOCATION,1);
	RED_MOOD;
	Led_von(OUTPUTS_PORT,BUZZER_PIN);
	LCD_Clear_Screen();
	LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);
	LCD_String("emergency mood");
    
	for (int i=0;i<WAITING_TIME_FOR_RENTER_THE_PASSWORD;i++)
	{
		if ((WAITING_TIME_FOR_RENTER_THE_PASSWORD-i)>9)
		{
		 LCD_Move_cursor(2,7);
		 LCD_Send_Char(((WAITING_TIME_FOR_RENTER_THE_PASSWORD-i)/10)+48);
		 LCD_Send_Char(((WAITING_TIME_FOR_RENTER_THE_PASSWORD-i)%10)+48);
		}
		else if ((WAITING_TIME_FOR_RENTER_THE_PASSWORD-i)<10)
		{
			LCD_Move_cursor(2,7);
			LCD_Send_Char((WAITING_TIME_FOR_RENTER_THE_PASSWORD-i)+48);
            LCD_Send_Char(' ');
		}					 
			 
		Led_vtoggle(OUTPUTS_PORT,RED_LED);
		Led_vtoggle(OUTPUTS_PORT,BUZZER_PIN);
		_delay_ms(1000);
	}
	LCD_Clear_Screen();
	LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);
	LCD_String("you have one");
	LCD_Move_cursor(2,1);
	LCD_String("more try");
	_delay_ms(3000);
	EEPROM_Write(TRIES_LOCATION,1);
    EEPROM_Write(WE_ARE_IN_EMERGNCY_LOCATION,0);	
}