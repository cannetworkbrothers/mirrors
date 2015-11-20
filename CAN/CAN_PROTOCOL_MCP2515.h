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

// command definitions
#define MCP2515_CMD_RESET 0xC0
#define MCP2515_CMD_READ 0x03
#define MCP2515_CMD_WRITE 0x02
#define MCP2515_CMD_BIT_MODIFY 0x05
#define MCP2515_CMD_READ_STATUS 0xA0
#define MCP2515_CMD_LOAD_TX 0x40
#define MCP2515_CMD_RTS 0x80
#define MCP2515_CMD_RX_STATUS 0xB0
#define MCP2515_CMD_READ_RX 0x90



class MCP2515
{
	private:
	
	mcu mcu;
	
	public:
	
	MCP2515( mcu type_mcu ) const { mcu = type_mcu};
	
	unsigned char mcp2515_read_register(unsigned char address);
	
	
	};



#endif /* CAN_PROTOCOL_MCP2515_H_ */