/*
 * CAN_PROTOCOL_MCP2515.h
 *
 * Created: 18.11.2015 12:53:23
 *  Author: Admin
 */ 


#ifndef CAN_PROTOCOL_MCP2515_H_
#define CAN_PROTOCOL_MCP2515_H_

// macros

#define getMode (readRegister(CANSTAT) & 0xE0)    // 0xe0 this mask 1110 0000 for compare read data with CAN_MODE_BIT
#define setMode(mode) writeRegister(CANSTAT, (readRegister(CANSTAT)& (mode+0x0F)))  //  mode - have hight rate byte
																					// 0x0f -this mask low 4-bit/
																					// op. & not change low bin when recordig

#include <avr/io.h>
#include "../protocol_handler/protocol_handler.h"
#include "mcp2515.h"

// pin mapping - TODO: move to separate header file

#define MCP2515_SS_0 PORTB &= ~(1 << PINB2 )
#define MCP2515_SS_1 PORTB |= (1 << PINB2)

class Protocol_MCP2515: public ProtocolHandler
{	
public:
	
	Protocol_MCP2515(){};
	~Protocol_MCP2515() {};
	
	void init();
	bool getPin(PIN pin);
	void setPin(PIN pin, bool level);
	unsigned char mcp2515_read_status();
	void mcp2515_set_bittiming(unsigned char cnf1, unsigned char cnf2, unsigned char cnf3);
	unsigned char readRegister(unsigned char address);
	void writeRegister(unsigned char address, unsigned char data);
	bool receiveMessage(canmsg_t * p_canmsg);
	unsigned char sendMessage(canmsg_t * p_canmsg);
	bool writeMessage(canmsg_t * p_canmsg);
	
	
	};



#endif /* CAN_PROTOCOL_MCP2515_H_ */