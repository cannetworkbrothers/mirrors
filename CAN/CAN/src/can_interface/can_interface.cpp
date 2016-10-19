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
#include "../usart/usart.hpp"
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
	
// 	MaskFilterProperties masks[] = {{0, false, 0x07ff}, {1, false, 0x07ff}};
// 	MaskFilterProperties filters[] = {	{0, false, 0x1e6},
// 	{1, false, 0x1e6},
//  	{2, false, 0x1e6},
//  	{3, false, 0x1e6},
//  	{4, false, 0x1e6},
//  	{5, false, 0x1e6}
// 		};
// 	can_protocol_.InitFiltering(masks, filters);
	LOG(logger, (char*) "Can::init_fltrng end")
}

bool CanInterface::SendMessageToBus(canmsg_t * p_canmsg){
	bool status_message = can_protocol_.SendMessage(p_canmsg);
	
	return status_message;
}

bool CanInterface::SendMessageToPC(canmsg_t * p_canmsg)
{
	
	USART transmiter;
	
	//calculate number of chars in result string
	uint8_t string_to_send_length = GetNumberOfDigits(p_canmsg->id, 16);
	
	char *id_prefix = (char*) malloc(2);
	if (p_canmsg->flags.extended == 1)
	{
		id_prefix = (char*) "W";
	}
	else
	{
		id_prefix = (char*) "S";
	}
	char *id_itself = (char*) malloc(string_to_send_length+1);
	itoa(p_canmsg->id, id_itself, 16);
	
	char *id = (char *) malloc(strlen(id_prefix)+strlen(id_itself)+1);
	strcpy(id, id_prefix);
	strcat(id, id_itself);
	free(id_prefix);
	free(id_itself);
	
	for(uint8_t i = 0; i < p_canmsg->dlc; i++){
		string_to_send_length += GetNumberOfDigits(p_canmsg->data[i], 16);
	}
	
	//plus W/S, plus zero end
	string_to_send_length += 2;
	
	//plus number of "D"
	string_to_send_length += p_canmsg->dlc;
	
	char *can_msg_str = (char*) malloc(string_to_send_length);
	strcpy(can_msg_str, id);
	free(id);
	
	for (uint8_t i = 0; i < p_canmsg->dlc; i++)
	{
		char * data = (char *) malloc((GetNumberOfDigits(p_canmsg->data[i], 16) + 1));
		itoa(p_canmsg->data[i], data, 16);
		strcat(can_msg_str, "D");
		strcat(can_msg_str, data);
		free(data);
	}
	transmiter.Write(can_msg_str);
	free(can_msg_str);
	return true;
}

uint8_t CanInterface::GetNumberOfDigits(uint8_t number, uint8_t radix)
{
	uint8_t count = 0;
	while(number > 0){
		number /= radix;
		count++;
	}
	
	return count;
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
