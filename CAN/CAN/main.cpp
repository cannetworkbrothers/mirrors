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
	
	LOG(logger, (char*) "END!!!")
	// create buffer for CAN message
	canmsg_t * buffer_message_1[10];
	// initiate filed "data" for control changes 
	for(int message_number =0; message_number<=10; message_number++){
		for(int bit_data = 0; bit_data<=7; bit_data++){
			buffer_message_1[message_number]->data[bit_data] = 2;
		}
	}
	// Write CAN message in input buffer MCU
	for(int message_number =0; message_number<=10; message_number++){
	bool receive_status = can_interface.receiveMessage( buffer_message_1[message_number]);
	if(receive_status == 1)	{
		LOG(logger, (char*) &buffer_message_1[message_number]->data);
	} else {
	 LOG(logger, (char*) "Not receive CAN massage");
	}
	}
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

