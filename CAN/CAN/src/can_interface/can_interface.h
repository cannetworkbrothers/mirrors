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

#define CAN_5kBPS		(1)
#define CAN_10KBPS		(2)
#define CAN_20KBPS		(3)
#define CAN_25KBPS		(4)
#define CAN_31K25BPS	(5)
#define CAN_33KBPS		(6)
#define CAN_40KBPS		(7)
#define CAN_50KBPS		(8)
#define CAN_80KBPS		(9)
#define CAN_83K3BPS		(10)
#define CAN_95KBPS		(11)
#define CAN_100KBPS		(12)
#define CAN_125KBPS		(13)
#define CAN_200KBPS		(14)
#define CAN_250KBPS		(15)
#define CAN_500KBPS		(16)
#define CAN_666KBPS		(17)
#define CAN_1000KBPS	(18)

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
		
	void init(uint8_t can_bus_nominal_speed);
	void init_filtering();
	
	// function for CAN controller with only 1 buffer
	bool ReceiveMessage(canmsg_t * p_canmsg);
	
	// function for CAN controller with 2 buffers
	rx_buffers_status ReceiveMessage(canmsg_t * p_canmsg_1, canmsg_t * p_canmsg_2);
	
	// function for CAN controller with 4 buffers
	bool ReceiveMessage(canmsg_t * p_canmsg_1, canmsg_t * p_canmsg_2, 
						canmsg_t * p_canmsg_3, canmsg_t * p_canmsg_4);
	
	bool SendMessageToBus(canmsg_t * p_canmsg);
	
	bool SendMessageToPC(canmsg_t * p_canmsg);
	
	private:
	uint8_t GetNumberOfDigits(uint8_t number, uint8_t radix);
};


#endif /* CAN_INTERFACE_H_ */