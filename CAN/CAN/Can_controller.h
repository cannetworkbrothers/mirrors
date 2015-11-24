/*
 * Can_controller.h
 *
 * Created: 18.11.2015 23:44:52
 *  Author: Admin
 */ 


#ifndef CAN_CONTROLLER_H_
#define CAN_CONTROLLER_H_

#include "mcu.h"
#include "CAN_PROTOCOL_MCP2515.h"

class Can_controller
{
	
	private:
	mcu mcu1;
	MCP2515 can;
	public:
	Can_controller(mcu d_mcu, MCP2515 d_can) {mcu1 = d_mcu; can = d_can;};
    
	void init() {};
	void read()  {};
	
	};


#endif /* CAN_CONTROLLER_H_ */