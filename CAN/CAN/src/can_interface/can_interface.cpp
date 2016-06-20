/*
 * can_interface.cpp
 *
 * Created: 11/29/2015 12:45:50 PM
 *  Author: Igor
 */ 


#include "can_interface.h"
#ifndef MAIN_H_
#include "../../main.hpp"
#endif
#include <util/delay.h>
#include "../usart/usart.hpp"

void CanInterface::init(){
	CREATE_LOGGER(logger)
	LOG(logger, (char*) "Can.Init start")
	can_protocol_.Init(CAN_5kBPS);
	LOG(logger, (char*) "Can.Init end")
}

void CanInterface::init_filtering()
{
	CREATE_LOGGER(logger)
	_delay_ms(100);
	LOG(logger, (char*) "Can::init_fltrng start")
	
	MaskFilterProperties masks[] = {{0, false, 0x07ff}, {1, false, 0x07ff}};
	MaskFilterProperties filters[] = {	{0, false, 0x1e6},
	{1, false, 0x1e6},
 	{2, false, 0x1e6},
 	{3, false, 0x1e6},
 	{4, false, 0x1e6},
 	{5, false, 0x1e6}
		};
	can_protocol_.InitFiltering(masks, filters);
	LOG(logger, (char*) "Can::init_fltrng end")
}

bool CanInterface::SendMessageToBus(canmsg_t * p_canmsg){
	bool status_message = can_protocol_.SendMessage(p_canmsg);
	
	return status_message;
}

bool CanInterface::SendMessageToPC(canmsg_t * p_canmsg)
{
	// 0 0 0 1 1 1 1 1
	// x x x | | | | |
	//       | | | | |
	//       | | | | --- DLC.0 
	//       | | | ----- DLC.1
	//       | | ------- DLC.2
	//       | --------- DLC.3
	//       ----------- Identifier 0 - standard, 1 - extended
	
	// start frame repeats twice, 2nd is inverse of 1st
	#define START_FRAME 2
	#define ID_FRAME	2
	#define IS_EXTENDED	4
	
	USART transmiter;
	uint8_t frame = 0x00;
	
	if (p_canmsg->flags.extended == 1)
	{
		frame |= (1<<IS_EXTENDED);
	}
	
	if (p_canmsg->dlc > 8)
	{
		return false;
	}
	else
	{
		frame |= p_canmsg->dlc;
	}
	
	transmiter.SendFrame(frame);
	transmiter.SendFrame(~frame);
	transmiter.SendFrame((uint8_t) p_canmsg->id); // send id frame 0
	transmiter.SendFrame((uint8_t) (p_canmsg->id >> 8) ); // send id frame 1
	
	if (p_canmsg->flags.extended == 1)
	{
		transmiter.SendFrame((uint8_t) (p_canmsg->id >> 16) ); // send id frame 2
		transmiter.SendFrame((uint8_t) (p_canmsg->id >> 24) ); // send id frame 3
	}
	
	for (uint8_t i = 0; i < p_canmsg->dlc; i++)
	{
		transmiter.SendFrame(p_canmsg->data[i]);
	}
	return true;
}

bool CanInterface::ReceiveMessage(canmsg_t * p_canmsg) {
	bool status_message = can_protocol_.ReceiveMessage(p_canmsg);
	return status_message;
}

bool CanInterface::ReceiveMessage(canmsg_t * p_canmsg_1, canmsg_t * p_canmsg_2)
{
	bool status_message = can_protocol_.ReceiveMessage(p_canmsg_1, p_canmsg_2);
	return status_message;
}

bool CanInterface::ReceiveMessage(canmsg_t * p_canmsg_1, canmsg_t * p_canmsg_2, canmsg_t * p_canmsg_3, canmsg_t * p_canmsg_4)
{
	bool status_message = can_protocol_.ReceiveMessage(p_canmsg_1, p_canmsg_2, p_canmsg_3, p_canmsg_4);
	return status_message;
}
