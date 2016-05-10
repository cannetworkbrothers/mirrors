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
	can_interface.init_filtering();
	
	LOG(logger, (char*) "END!!!")
	// create buffer for CAN message
	canmsg_t * p_can_message_1 = (canmsg_t*) malloc(sizeof(canmsg_t));
	canmsg_t * p_can_message_2 = (canmsg_t*) malloc(sizeof(canmsg_t));
		
	bool receive_status = false;
	LOG(logger, (char*) "Waiting for message...")
	while (true)
	{
		p_can_message_1->timestamp = 255;
		p_can_message_2->timestamp = 255;
		receive_status = can_interface.ReceiveMessage(p_can_message_1, p_can_message_2);
		if(receive_status == 1)	
		{
			if (p_can_message_1->timestamp == 0)
			{
				LOG(logger, (char*) "Message in Rx0")
				char* data_str = (char*) malloc(3);
				
				itoa(p_can_message_1->flags.extended, data_str, 10);
				LOG(logger, (char*) data_str)
				
				itoa(p_can_message_1->id, data_str, 16);
				LOG(logger, (char*) data_str)
	
				for (int i = 0; i < 8; ++i)
				{
					/* code */
					itoa(p_can_message_1->data[i], data_str, 16);
					LOG(logger, (char*) data_str)
				}
				free(data_str);
			}
			if (p_can_message_2->timestamp == 0)
			{
				LOG(logger, (char*) "Message in Rx1")
				char* data_str = (char*) malloc(3);
				
				itoa(p_can_message_2->flags.extended, data_str, 10);
				LOG(logger, (char*) data_str)
				
				itoa(p_can_message_2->id, data_str, 16);
				LOG(logger, (char*) data_str)
				
				for (int i = 0; i < 8; ++i)
				{
					/* code */
					itoa(p_can_message_2->data[i], data_str, 16);
					LOG(logger, (char*) data_str)
				}
				free(data_str);
			}
		} 
		else {
			continue;
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

