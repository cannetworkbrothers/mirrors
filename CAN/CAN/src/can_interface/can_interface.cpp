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
#include <math.h>

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

int freeRamMemory () {
	extern int __heap_start, *__brkval;
	int v;
	return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

bool CanInterface::SendMessageToPC(canmsg_t * p_canmsg)
{
	
	USART transmiter;
	CREATE_LOGGER(logger)
	LOG(logger, (char*) "SendToPC-enter");
	
	char buffer[16];
	char can_msg_str[35]; // MAX 35 = 1 (W,S) + 8 (1fffffff) + 8 (D) + 8*2 (ff) + 1(N) + 1 ('0') 
	if (p_canmsg->flags.extended == 1)
	{
		strcpy(can_msg_str, (char*) "W");
	}
	else
	{
		strcpy(can_msg_str, (char*) "S");
	}
	
	strcat(can_msg_str, itoa(p_canmsg->id, buffer, 16));
	
	for (uint8_t i = 0; i < p_canmsg->dlc; i++)
	{
		strcat(can_msg_str, "D");
		strcat(can_msg_str, itoa(p_canmsg->data[i], buffer, 16));
	}
	strcat(can_msg_str, "N");
	transmiter.Write(can_msg_str);
	//free(can_msg_str);
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

rx_buffers_status CanInterface::ReceiveMessage(canmsg_t * p_canmsg_1, canmsg_t * p_canmsg_2)
{
	rx_buffers_status status_message = can_protocol_.ReceiveMessage(p_canmsg_1, p_canmsg_2);
	return status_message;
}

bool CanInterface::ReceiveMessage(canmsg_t * p_canmsg_1, canmsg_t * p_canmsg_2, canmsg_t * p_canmsg_3, canmsg_t * p_canmsg_4)
{
	bool status_message = can_protocol_.ReceiveMessage(p_canmsg_1, p_canmsg_2, p_canmsg_3, p_canmsg_4);
	return status_message;
}
