/*
 * CAN.cpp
 *
 * Created: 11/29/2015 11:06:35 PM
 * Author : Igor
 */ 

#ifndef MAIN_H_
	#include "main.hpp"
#endif
#include "src/can_interface/can_interface.h"
#include <util/delay.h>
#include <stdlib.h>

int freeRam () {
	extern int __heap_start, *__brkval;
	int v;
	return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

int main(void)
{
	DDRB = 0b00000010; // PB1 as output  and PB2 output
	PORTB |= (1<<PB1); // light the LED for fun :);
	
	//wait 10 seconds for start logging
	_delay_ms(10*1000);
	CREATE_LOGGER(logger);
	LOG(logger, (char*) "Start!!!")

 	//canmsg_t can_message_buffer;
 	CanInterface can_interface;
	LOG(logger, (char*) "Initialized can_interface!!!")
 	can_interface.init();
	can_interface.init_filtering();
	
	// create buffer for CAN message
	 canmsg_t * p_can_message_1 = (canmsg_t*) malloc(sizeof(canmsg_t));
	 canmsg_t * p_can_message_2 = (canmsg_t*) malloc(sizeof(canmsg_t));
	 
	 rx_buffers_status receive_status = {};
	LOG(logger, (char*) "Waiting for message...")
	while (true)
	{
		receive_status = can_interface.ReceiveMessage(p_can_message_1, p_can_message_2);
		if(receive_status.rx0_status == true){
			can_interface.SendMessageToPC(p_can_message_1);
		}
		if (receive_status.rx1_status == true){
			can_interface.SendMessageToPC(p_can_message_2);
		}
	} 
}

