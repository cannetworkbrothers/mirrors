/*
 * CAN_USB_INTERFACE.h
 *
 * Created: 18.11.2015 12:50:37
 *  Author: Admin
 */ 

#ifndef CAN_INTERFACE_H_
#define CAN_INTERFACE_H_

#include "../protocol_mcp2515/can_protocol_mcp2515.h"
#include "../controller_atmega8/controller_atmega8.h"

#define CAN_5kBPS (0)

class CanInterface

{
	private:
	ControllerAtmega8 mcu_;
	ProtocolHandlerMcp2515 can_protocol_;
	
	public:
	CanInterface() 
	{
		can_protocol_.ConnectSpiTransmitCallback(ControllerAtmega8::StaticSpiMasterTransmit, &mcu_);
		
	};
	~CanInterface() {};
		
	void init();
	
	// function for CAN controller with only 1 buffer
	bool ReceiveMessage(canmsg_t * p_canmsg);
	
	// function for CAN controller with 2 buffers
	bool ReceiveMessage(canmsg_t * p_canmsg_1, canmsg_t * p_canmsg_2);
	
	// function for CAN controller with 4 buffers
	bool ReceiveMessage(canmsg_t * p_canmsg_1, canmsg_t * p_canmsg_2, 
						canmsg_t * p_canmsg_3, canmsg_t * p_canmsg_4);
	
	bool sendMessage(canmsg_t * p_canmsg);
		
};


#endif /* CAN_INTERFACE_H_ */