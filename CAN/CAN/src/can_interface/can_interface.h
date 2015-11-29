/*
 * CAN_USB_INTERFACE.h
 *
 * Created: 18.11.2015 12:50:37
 *  Author: Admin
 */ 


#include "../protocol_handler/protocol_handler.h"
#include "../controller/can_controller.h"


class CAN_USB_INTERFACE

	{
		
		private:
		CanController mcu_;
		ProtocolHandler can_protocol_;
				
		public:
		virtual void init() = 0;
		virtual unsigned char receiveMessage(ProtocolHandler cp, CanController mcu, canmsg_t * p_canmsg) = 0;
		virtual unsigned char sendMessage(ProtocolHandler cp, CanController mcu, canmsg_t * p_canmsg) = 0;
		
		};


#endif /* CAN_USB_INTERFACE_H_ */