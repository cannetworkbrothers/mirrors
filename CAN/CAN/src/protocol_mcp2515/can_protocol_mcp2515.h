/*
 * CAN_PROTOCOL_MCP2515.h
 *
 * Created: 18.11.2015 12:53:23
 *  Author: Admin
 */ 


#ifndef CAN_PROTOCOL_MCP2515_H_
#define CAN_PROTOCOL_MCP2515_H_

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
	unsigned char readRegister(unsigned char address);
	void writeRegister(unsigned char address);
	bool receiveMessage(canmsg_t * p_canmsg);
	bool writeMessage(canmsg_t * p_canmsg);
	
	};



#endif /* CAN_PROTOCOL_MCP2515_H_ */