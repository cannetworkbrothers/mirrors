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

#include <inttypes.h>
#include <avr/io.h>
#include "../protocol_handler/protocol_handler.h"
#include "mcp2515.h"

// pin mapping - TODO: move to separate header file

#define MCP2515_SS_0 PORTB &= ~(1 << PINB2 )
#define MCP2515_SS_1 PORTB |= (1 << PINB2)

struct MaskFilterProperties{
	// 0 or 1 are possible values for MCP2515
	uint8_t		id;
	bool		is_extened_id;
	// 32 bits mask/filter value for extended id
	// for extended id range is 00 00 00 00 - 1F FF FF FF
	// 16 bits mask/filter value for standard id
	// for standard id range is 00 00 - 7 FF
	uint32_t	data; 
};


class ProtocolHandlerMcp2515: public ProtocolHandler
{
private:
	void			BitModify(unsigned char address, unsigned char mask, unsigned char data);
	void			InitCanBuffers(void);
	unsigned char	IsMessageInRxBuffers();
	unsigned char	ReadRegister(const unsigned char address);
	void			ReadRxBuffer(unsigned char buffer_address, unsigned char status_rx, canmsg_t * p_canmsg);
	unsigned char	ReadStatus();
	void			Reset(void);
	void			SetBitRateRegisters(unsigned char cnf1, unsigned char cnf2, unsigned char cnf3);
	unsigned char	SetCanSpeed(unsigned char can_speed);
	unsigned char	SetMode(const unsigned char desired_mode);
	void			WriteMaskFilterId(const uint8_t address, const bool is_extended_id, const uint32_t id);
	void			WriteRegister(unsigned char address, unsigned char data);
	void			WriteSequenceOfRegisters(const uint8_t address, const uint8_t data[], const uint8_t n);
		
public:
	
	ProtocolHandlerMcp2515() {};
	~ProtocolHandlerMcp2515() {};
	
	unsigned char	Init(const unsigned char can_speed);
	uint8_t			InitFiltering(MaskFilterProperties masks[], MaskFilterProperties filters[]);
	bool			ReceiveMessage(canmsg_t * p_canmsg);
	bool			ReceiveMessage(canmsg_t * p_canmsg_1, canmsg_t * p_canmsg_2);
	bool			ReceiveMessage(canmsg_t * p_canmsg_1, canmsg_t * p_canmsg_2,
						canmsg_t * p_canmsg_3, canmsg_t * p_canmsg_4);				
	unsigned char	SendMessage(canmsg_t * p_canmsg);
};

#endif /* CAN_PROTOCOL_MCP2515_H_ */