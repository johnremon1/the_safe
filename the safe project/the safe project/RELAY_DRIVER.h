/*
 * RELAY_DRIVER.h
 *
 * Created: 8/5/2023 2:49:03 PM
 *  Author: johnr
 */ 


#ifndef RELAY_DRIVER_H_
#define RELAY_DRIVER_H_



/*
Function name   : Relay_init
Function return : void
Function Arguments :  port_name,pin
Function description :this function make the pin you choose an output pin
*/
void Relay_init(unsigned char port_name,unsigned char pin);

/*
Function name   : Relay_on
Function return : void
Function Arguments :  port_name,pin
Function description :this function write 1 or logic high on the pin you choose
*/
void Relay_on(unsigned char port_name,unsigned char pin);

/*
Function name   : Relay_off
Function return : void
Function Arguments :  port_name,pin
Function description :this function write 0 or logic low on the pin you choose
*/
void Relay_off(unsigned char port_name,unsigned char pin);




#endif /* RELAY_DRIVER_H_ */