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

int main(void)
{
	DDRB = 0b00000010; // PB1 as output
	PORTB = 0b00000010; // light the LED for fun :)
	
	//wait 10 seconds for start logging
	_delay_ms(10*1000);
	CREATE_LOGGER(logger);
	LOG(logger, (char*) "Start!!!")

 	//canmsg_t can_message_buffer;
 	CanInterface can_interface;
	LOG(logger, (char*) "Initialized can_interface!!!")
 	can_interface.init();
	LOG(logger, (char*) "END!!!")
	
	//char msg[] = "HelloIgor. ";
	//char portb_value[9];
// 	char* out_message = (char*) malloc(30);
	//CREATE_LOGGER(logger)
    
	//Main loop
    //while (1) 
    //{
		//itoa(PORTB, portb_value, 2);
		//char* out_message = (char*) malloc(30);
		//strmerge(msg, portb_value, out_message);
		////can_interface.receiveMessage(&can_message_buffer);
		//LOG(logger, out_message)
		///*logger_var.WriteLine(msg);*/
		//_delay_ms(1000);
		////invert PB1
		//PORTB ^= 0b00000010;
		//free(out_message);
    //}
}

