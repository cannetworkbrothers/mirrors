/*
 * CAN_PROTOCOL_MCP2515.h
 *
 * Created: 18.11.2015 12:53:23
 *  Author: Admin
 */ 


#ifndef CAN_PROTOCOL_MCP2515_H_
#define CAN_PROTOCOL_MCP2515_H_

// macros

// 0xe0 this mask 1110 0000 for compare read data with CANSTAT, register 10-2, page 61
#define GET_MODE (ReadRegister(CANSTAT) & 0xE0)

#define SET_MODE(mode) WriteRegister(CANSTAT, (ReadRegister(CANSTAT)& (mode+0x0F)))  //  mode - have hight rate byte
																					// 0x0f -this mask low 4-bit/
																					// op. & not change low bin when recordig

#include <avr/io.h>
#include "../protocol_handler/protocol_handler.h"
#include "mcp2515.h"

// pin mapping - TODO: move to separate header file

#define MCP2515_SS_0 PORTB &= ~(1 << PINB2 )
#define MCP2515_SS_1 PORTB |= (1 << PINB2)

class ProtocolHandlerMcp2515: public ProtocolHandler
{
private:
	void			BitModify(unsigned char address, unsigned char mask, unsigned char data);
	unsigned char	ReadRegister(const unsigned char address);
	void			Reset(void);
	void			SetBitRateRegisters(unsigned char cnf1, unsigned char cnf2, unsigned char cnf3);
	unsigned char	SetCanSpeed(unsigned char can_speed);
	unsigned char	SetMode(const unsigned char desired_mode);
	void			WriteRegister(unsigned char address, unsigned char data);
		
public:
	
	ProtocolHandlerMcp2515(){};
	~ProtocolHandlerMcp2515() {};
	
	unsigned char	Init(const unsigned char can_speed);
	bool getPin(PIN pin);
	void setPin(PIN pin, bool level);
	unsigned char mcp2515_read_status();
	bool receiveMessage(canmsg_t * p_canmsg);
	unsigned char sendMessage(canmsg_t * p_canmsg);
	bool writeMessage(canmsg_t * p_canmsg);
	unsigned char mcp2515_rx_status();
	
	
	};



#endif /* CAN_PROTOCOL_MCP2515_H_ */