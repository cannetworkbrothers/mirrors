/*
 * CAN_USB_INTERFACE.h
 *
 * Created: 18.11.2015 12:50:37
 *  Author: Admin
 */ 

#ifndef CAN_USB_INTERFACE_H_
#define CAN_USB_INTERFACE_H_

#include "../protocol_mcp2515/can_protocol_mcp2515.h"
#include "../controller_atmega8/controller_atmega8.h"


class CAN_USB_INTERFACE

{
	private:
	ControllerAtmega8 mcu_;
	Protocol_MCP2515 can_protocol_;
	
	public:
	CAN_USB_INTERFACE() 
	{
		can_protocol_.connectSpiTransmitCallback(ControllerAtmega8::static_SPI_Master_Transmit, &mcu_);
		
	};
	~CAN_USB_INTERFACE() {};
		
	void init();
	bool receiveMessage(canmsg_t * p_canmsg);
	bool sendMessage(canmsg_t * p_canmsg);
		
};


#endif /* CAN_USB_INTERFACE_H_ */