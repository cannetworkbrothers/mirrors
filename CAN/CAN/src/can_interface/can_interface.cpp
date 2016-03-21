/*
 * can_interface.cpp
 *
 * Created: 11/29/2015 12:45:50 PM
 *  Author: Igor
 */ 

#include "can_interface.h"

void CAN_USB_INTERFACE::init(){
	
}
bool CAN_USB_INTERFACE::sendMessage(canmsg_t * p_canmsg){
	can_protocol_.sendMessage(p_canmsg);
	
	return 0;
}