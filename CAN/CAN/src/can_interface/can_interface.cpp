/*
 * can_interface.cpp
 *
 * Created: 11/29/2015 12:45:50 PM
 *  Author: Igor
 */ 

#include "can_interface.h"

void CAN_USB_INTERFACE::init(){
	
}
unsigned char CAN_USB_INTERFACE::sendMessage(canmsg_t * p_canmsg){
	can_protocol_.receiveMessage(p_canmsg);
	
	return 0;
}