/*
 * KEY_PAD_DRIVER.h
 *
 * Created: 8/16/2023 7:51:06 PM
 *  Author: johnr
 */ 


#ifndef KEY_PAD_DRIVER_H_
#define KEY_PAD_DRIVER_H_
#include "DIO_DRIVER.h"

#define PORT_NAME 'B'

void Keypad_init();

char Keypad_u8check_press();



#endif /* KEY_PAD_DRIVER_H_ */