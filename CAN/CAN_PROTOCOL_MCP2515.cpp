/*
 * CAN_PROTOCOL_MCP2515.cpp
 *
 * Created: 18.11.2015 13:05:41
 *  Author: Admin
 */ 


#include "CAN_PROTOCOL_MCP2515.h"


unsigned char mcp2515_read_register(unsigned char address)

 {

	unsigned char data;
	
	// pull SS to low level
	MCP2515_SS_0;
	
	mcu.SPI_Master_Transmit(MCP2515_CMD_READ);
	mcu.SPI_Master_Transmit(address);
	data = mcu.SPI_Mastre_Transmit(0xff);
	
	
	
	
	
	
	// release SS
	MCP2515_SS_1;
	
	return data;
}
