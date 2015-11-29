/*
 * can_interface.cpp
 *
 * Created: 11/29/2015 12:45:50 PM
 *  Author: Igor
 */ 

#include "can_interface.h"

void CAN_USB_INTERFACE::init(){
	
}

unsigned char CAN_USB_INTERFACE::receiveMessage(ProtocolHandler cp, CanController mcu, canmsg_t * p_canmsg){
	cp.receiveMessage(p_canmsg, &mcu.SPI_MasterTransmit());
}