/*
 * CAN.cpp
 *
 * Created: 11/29/2015 11:06:35 PM
 * Author : Igor
 */ 

#include "main.hpp"
#include "src/can_interface/can_interface.h"

#if USART_SUPPORT == ON
	#include "src/usart/usart.hpp"
	#include <util/delay.h>
	#include <stdlib.h>
#endif

int main(void)
{
	DDRB = 0b00000010; // PB1 as output
	PORTB = 0b00000010; // light the LED for fun :)

	canmsg_t can_message_buffer;
	CAN_USB_INTERFACE can_interface;
	can_interface.init();
	
	#if USART_SUPPORT == ON
		USART Logger = USART();
		char msg[] = "HelloIgor. ";
		int i = 0;
		char * ptr_index = NULL;
	#endif
    
	//Main loop
    while (1) 
    {
		//can_interface.receiveMessage(&can_message_buffer);
		Logger.Write(msg);
		itoa(i, ptr_index,10);
		Logger.WriteLine(ptr_index);
		_delay_ms(100);
		i++;
    }
}

