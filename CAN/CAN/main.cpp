/*
 * CAN.cpp
 *
 * Created: 11/29/2015 11:06:35 PM
 * Author : Igor
 */ 

#include "main.hpp"
#include <avr/io.h>
#include "src/can_interface/can_interface.h"


int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
		canmsg_t can_message_buffer;
		CAN_USB_INTERFACE can_interface;
		
		can_interface.init();
		can_interface.receiveMessage(&can_message_buffer);
		
		

    }
}

