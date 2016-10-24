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
	// canmsg_t * p_can_message_1 = (canmsg_t*) malloc(sizeof(canmsg_t));
	// canmsg_t * p_can_message_2 = (canmsg_t*) malloc(sizeof(canmsg_t));
		
	// rx_buffers_status receive_status = {};
	LOG(logger, (char*) "Waiting for message...")
	canmsg_t my_id = {};
	while (true) {
		LOG(logger, (char*) "enter...")
		srand(15);
		my_id.id = rand() % 0x1fffffff;
		my_id.flags.rtr = 0;
		if (my_id.id > 0x7ff)
		{
			my_id.flags.extended = 1;
		}
		else{
			my_id.flags.extended = 0;
		}
		my_id.dlc = 8;
		for (int i = 0; i < 8; ++i)
		{
			my_id.data[i]  = rand() % 255;
		}
		my_id.timestamp = 12212;
		
		char* free_memory_string = (char*) malloc(10);
		LOG(logger, (char*) itoa(freeRam(), free_memory_string, 10));
		can_interface.SendMessageToPC(&my_id);
		LOG(logger, (char*) itoa(freeRam(), free_memory_string, 10));
		free(free_memory_string);
		_delay_ms(20);
	}
	//while (true)
	//{
		//receive_status = can_interface.ReceiveMessage(p_can_message_1, p_can_message_2);
		//if(receive_status.rx0_status == true){
			//LOG(logger, (char*) "Message in Rx0")
			//char* data_str = (char*) malloc(3);
				//
			//itoa(p_can_message_1->flags.extended, data_str, 10);
			//LOG(logger, (char*) data_str)
				//
			//itoa(p_can_message_1->id, data_str, 16);
			//LOG(logger, (char*) data_str)
	//
			//for (int i = 0; i < 8; ++i)
			//{
				///* code */
				//itoa(p_can_message_1->data[i], data_str, 16);
				//LOG(logger, (char*) data_str)
			//}
			//free(data_str);
		//}
		//if (receive_status.rx1_status == true){
			//LOG(logger, (char*) "Message in Rx1")
			//char* data_str = (char*) malloc(3);
				//
			//itoa(p_can_message_2->flags.extended, data_str, 10);
			//LOG(logger, (char*) data_str)
				//
			//itoa(p_can_message_2->id, data_str, 16);
			//LOG(logger, (char*) data_str)
				//
			//for (int i = 0; i < 8; ++i)
			//{
				///* code */
				//itoa(p_can_message_2->data[i], data_str, 16);
				//LOG(logger, (char*) data_str)
			//}
			//free(data_str);
		//}
	//} 
}

