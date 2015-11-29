/*
 * CAN_PROTOCOL_MCP2515.cpp
 *
 * Created: 18.11.2015 13:05:41
 *  Author: Brothers
 */ 


#include "can_protocol_mcp2515.h"

void Protocol_MCP2515::setPin(PIN pin, bool level){
	if (level == true)
	{
		pin = 0;
	}
	else
	{
		pin = 1;
	}
	
}

unsigned char Protocol_MCP2515::readRegister(unsigned char address, controller_spi_transmit spi_transmit){
	unsigned char data;
	
	//Set CS pin to low level
	setPin(MCP2515_CS, false);
	
	spi_transmit(MCP2515_CMD_READ);
	spi_transmit(address);
	
	data = spi_transmit(0xFF);
	
	setPin(MCP2515_CS, true);
	
	return data;
}

bool Protocol_MCP2515::receiveMessage(canmsg_t * p_canmsg, controller_spi_transmit spi_transmit){
	unsigned char address = 0x40; // for example
	
	setPin(MCP2515_CS, false);
	spi_transmit(MCP2515_CMD_READ | address);
	p_canmsg->data = spi_transmit(0xff);
	setPin(MCP2515_CS, true);
}