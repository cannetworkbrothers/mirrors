/*
 * CAN_PROTOCOL_MCP2515.cpp
 *
 * Created: 18.11.2015 13:05:41
 *  Author: Brothers
 */ 


#include "can_protocol_mcp2515.h"

void Protocol_MCP2515::init()
{
	
}

bool Protocol_MCP2515::getPin(PIN pin)
{
	return true;
}

void Protocol_MCP2515::setPin(PIN pin, bool level)
{
	if (level == true)
	{
		pin = 0;
	}
	else
	{
		pin = 1;
	}
	
}

unsigned char Protocol_MCP2515::readRegister(unsigned char address){
	unsigned char data;
	
	//Set CS pin to low level
	setPin(MCP2515_CS, false);
	
	ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, MCP2515_CMD_READ);
	ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, address);
	
	data = ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, 0xFF);
	
	setPin(MCP2515_CS, true);
	
	return data;
}

void Protocol_MCP2515::writeRegister(unsigned char address)
{
	//just a stub
}

bool Protocol_MCP2515::receiveMessage(canmsg_t * p_canmsg){
	unsigned char address = 0x40; // for example
	
	setPin(MCP2515_CS, false);
	ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, MCP2515_CMD_READ | address);
	p_canmsg->dlc = ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, 0xff);
	setPin(MCP2515_CS, true);
	return true;
}

bool Protocol_MCP2515::writeMessage(canmsg_t * p_canmsg)
{
	//just a stub
	return true;
}