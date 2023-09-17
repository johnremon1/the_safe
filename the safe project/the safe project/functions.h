/*
 * functions.h
 *
 * Created: 8/31/2023 5:25:14 PM
 *  Author: johnr
 */ 


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "LCD_CONFIG.h"
#include "LCD_DRIVER.h"
#include "PUSH_BUTTON.h"
#include "LED_DRIVER.h"
#include "EEPROM_DRIVER.h"
#include "KEY_PAD_DRIVER.h"
#define F_CPU 8000000ul
#include <util/delay.h>


#define GREEN_LED 3
#define RED_LED 4
#define RIGHT_BUTTON 0 //pull down
#define OK_BUTTON 1//pull down
#define LEFT_BUTTON 2//pull down
#define BUZZER_PIN 5
#define RESET_PIN 6
//these buttons are for the control on the lcd


#define PASSWORD_LOCATION1 0X20//the passwords location
#define PASSWORD_LOCATION2 0X21//very important note that is the location must be after each other like that with only 1 difference between every two adresess
#define PASSWORD_LOCATION3 0X22
#define PASSWORD_LOCATION4 0X23
#define PASSWORD_LOCATION5 0X24
#define PASSWORD_LOCATION6 0X25
#define TRIES_LOCATION 0X30//the eeprom addressee that holds the number of tries
#define WE_ARE_IN_EMERGNCY_LOCATION 0X40//this variable only for if the user unplug the safe while the emergency mood is on so the emergency can finish less that its original time
#define FIRST_TIME_LOCATION 0X28// this location only knows that this the first time the user enter the safe or not so the user can create a password
#define OTP_LOCATION1 0X50
#define OTP_LOCATION2 0X51
#define OTP_LOCATION3 0X52
#define OTP_LOCATION4 0X53
#define OTP_TRIES_LOCATION 0X55
#define OTP_NUMBER_OF_TRIES 3

#define NUMBER_OF_TRIES 3
#define WAITING_TIME_FOR_RENTER_THE_PASSWORD 15 //the time in seconds the safe is closed and the alarm is activated and no more actions on the safe
#define OUTPUTS_PORT 'D' //this port is for small external prephirals like leds and buttons
#define LCD_CHOICES_CONTROLE LCD_Send_Cmd(DISPLAY_ON_CURSOR_OFF);LCD_Move_cursor(2,1);LCD_Send_Char('<');LCD_Move_cursor(2,7);LCD_Send_Char('O');LCD_Send_Char('K');LCD_Move_cursor(2,15);LCD_Send_Char('>')
#define GREEN_MOOD Led_voff(OUTPUTS_PORT,RED_LED);Led_von(OUTPUTS_PORT,GREEN_LED)
#define RED_MOOD Led_voff(OUTPUTS_PORT,GREEN_LED);Led_von(OUTPUTS_PORT,RED_LED)


//functions area
void creat_new_password();
void Confirm_password();
void open_the_safe();
unsigned char write_password();
unsigned char write_otp();
void create_otp();
void change_password();
void reset();
void emergency_mood();


#endif /* FUNCTIONS_H_ */