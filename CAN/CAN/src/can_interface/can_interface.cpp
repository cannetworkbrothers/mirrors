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

bool CanInterface::SendMessage(canmsg_t * p_canmsg){
	bool status_message = can_protocol_.SendMessage(p_canmsg);
	
	return status_message;
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
