/*
 * CAN_PROTOCOL_MCP2515.cpp
 *
 * Created: 18.11.2015 13:05:41
 *  Author: Admin
 */ 


#include "CAN_PROTOCOL_MCP2515.h"


unsigned char MCP2515::mcp2515_read_register(unsigned char address)

 {

	unsigned char data;
	
	// pull SS to low level
	MCP2515_SS_0;
	
	mcu1.SPI_MasterTransmit(MCP2515_CMD_READ);
	mcu1.SPI_MasterTransmit(address);
	data = mcu1.SPI_MasterTransmit(0xff);
		
	// release SS
	MCP2515_SS_1;
	
	return data;
};

void MCP2515::mcp2515_write_register(unsigned char address, unsigned char data)
{
	// pull SS to low level
	MCP2515_SS_0;
	
	mcu1.SPI_MasterTransmit(MCP2515_CMD_WRITE);
	mcu1.SPI_MasterTransmit(address);
	mcu1.SPI_MasterTransmit(data);
	
	// release SS
	MCP2515_SS_1;
};