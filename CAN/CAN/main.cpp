/*
 * CAN.cpp
 *
 * Created: 11/29/2015 11:06:35 PM
 * Author : Igor
 */ 

#include "main.hpp"
#include "src/can_interface/can_interface.h"
#include <avr/delay.h>

int main(void)
{
	DDRB = 0b00000010; // PB1 as output
	PORTB = 0b00000010; // light the LED for fun :)

// 	canmsg_t can_message_buffer;
// 	CAN_USB_INTERFACE can_interface;
// 	can_interface.init();
	
/*	char msg[] = "HelloIgor. ";*/
	CREATE_LOGGER(logger)
    
	//Main loop
    while (1) 
    {
		//can_interface.receiveMessage(&can_message_buffer);
		LOG(logger, msg)
		/*logger_var.WriteLine(msg);*/
		_delay_ms(1000);
		//invert PB1
		PORTB = PORTB^0b00000010;
    }
}

