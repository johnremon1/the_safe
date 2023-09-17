/*
 * RELAY_DRIVER.c
 *
 * Created: 8/5/2023 2:44:15 PM
 *  Author: john
 */ 
#include "DIO_DRIVER.h"

void Relay_init(unsigned char port_name,unsigned char pin)
{
	DIO_SetPinDir(port_name,pin,1);
}

void Relay_on(unsigned char port_name,unsigned char pin)
{
	DIO_Write(port_name,pin,1);
}

void Relay_off(unsigned char port_name,unsigned char pin)
{
	DIO_Write(port_name,pin,0);
}
