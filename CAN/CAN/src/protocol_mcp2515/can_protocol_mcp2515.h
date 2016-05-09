/*
 * CAN_PROTOCOL_MCP2515.h
 *
 * Created: 18.11.2015 12:53:23
 *  Author: Admin
 */ 


#ifndef CAN_PROTOCOL_MCP2515_H_
#define CAN_PROTOCOL_MCP2515_H_

#ifndef MAIN_H_
#include "../../main.hpp"
#endif

// 0xe0 this mask 1110 0000 for compare read data with CANSTAT, register 10-2, page 61
#define GET_MODE (ReadRegister(CANSTAT) & 0xE0)
#define SELECT_CAN_CHIP(port_name, pin_name)	port_name &= ~(1<<pin_name);
#define UNSELECT_CAN_CHIP(port_name, pin_name)	port_name |= (1<<pin_name);

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
	void			InitCanBuffers(void);
	unsigned char	ReadRegister(const unsigned char address);
	void			ReadRxBuffer(unsigned char buffer_address, unsigned char status_rx, canmsg_t * p_canmsg);
	void			Reset(void);
	void			SetBitRateRegisters(unsigned char cnf1, unsigned char cnf2, unsigned char cnf3);
	unsigned char	SetCanSpeed(unsigned char can_speed);
	unsigned char	SetMode(const unsigned char desired_mode);
	void			WriteRegister(unsigned char address, unsigned char data);
		
public:
	
	ProtocolHandlerMcp2515() {};
	~ProtocolHandlerMcp2515() {};
	
	unsigned char	Init(const unsigned char can_speed);
	unsigned char mcp2515_read_status();
	bool ReceiveMessage(canmsg_t * p_canmsg_1);
	
	bool ReceiveMessage(canmsg_t * p_canmsg_1, canmsg_t * p_canmsg_2);
	
	bool ReceiveMessage(canmsg_t * p_canmsg_1, canmsg_t * p_canmsg_2,
						canmsg_t * p_canmsg_3, canmsg_t * p_canmsg_4);
						
	unsigned char sendMessage(canmsg_t * p_canmsg);
	bool writeMessage(canmsg_t * p_canmsg);
	unsigned char mcp2515_rx_status();
	
	
	};



#endif /* CAN_PROTOCOL_MCP2515_H_ */