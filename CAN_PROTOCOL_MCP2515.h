/*
 * CAN_PROTOCOL_MCP2515.h
 *
 * Created: 18.11.2015 12:53:23
 *  Author: Admin
 */ 


#ifndef CAN_PROTOCOL_MCP2515_H_
#define CAN_PROTOCOL_MCP2515_H_

#include "mcu.h"

// pin mapping

#define MCP2515_SS_0 PORTB &= ~(1 << PINB2 )
#define MCP2515_SS_1 PORTB |= (1 << PINB2)



class MCP2515
{
	private:
	
	mcu mcu;
	
	public:
	
	MCP2515( mcu type_mcu ) const { mcu = type_mcu};
	
	unsigned char mcp2515_read_register(unsigned char address);
	
	
	};



#endif /* CAN_PROTOCOL_MCP2515_H_ */