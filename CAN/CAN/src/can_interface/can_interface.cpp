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

void CanInterface::init(){
	CREATE_LOGGER(logger)
	LOG(logger, (char*) "CanInterface.Init() started...")
	can_protocol_.Init(CAN_5kBPS);
	LOG(logger, (char*) "CanInterface.Init() ended.")
}

bool CanInterface::sendMessage(canmsg_t * p_canmsg){
	can_protocol_.sendMessage(p_canmsg);
	
	return 0;
}