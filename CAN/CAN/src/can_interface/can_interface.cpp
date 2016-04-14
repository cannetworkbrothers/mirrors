/*
 * can_interface.cpp
 *
 * Created: 11/29/2015 12:45:50 PM
 *  Author: Igor
 */ 

#include "can_interface.h"

void CanInterface::init(){
	can_protocol_.Init(CAN_5kBPS);
}

bool CanInterface::sendMessage(canmsg_t * p_canmsg){
	can_protocol_.sendMessage(p_canmsg);
	
	return 0;
}