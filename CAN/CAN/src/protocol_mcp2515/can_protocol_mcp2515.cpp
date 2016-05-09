/*
 * CAN_PROTOCOL_MCP2515.cpp
 *
 * Created: 18.11.2015 13:05:41
 *  Author: Brothers
 */ 


#include "can_protocol_mcp2515.h"
#include "math.h"
#ifndef MAIN_H_
	#include "../../main.hpp"
#endif
#ifndef CANCONFIG_H_
	#include "canconfig.h"
#endif
#include <util/delay.h>
#include <stdlib.h>

// macro for micro controller callback, will be used in appropriate MCP2515 functions
// when MCP2515 call controller_spi_transmit, will be invoked callback controller_p
// controller_p is actually function pointer, it is initialized
#define SPI_TRANSMIT(adr) ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, adr);

/* 
 * Implementation of MCP2515 private members
 */

void ProtocolHandlerMcp2515::BitModify(unsigned char address, unsigned char mask, unsigned char data) {
	
	CREATE_LOGGER(logger)
	// set CS pin to low level
	SELECT_CAN_CHIP(SPI_CS_PORT, SPI_CS_PIN)
	
	
	LOG(logger, (char*) "SPI: sending command bit_modify")
	SPI_TRANSMIT(MCP2515_CMD_BIT_MODIFY);
	LOG(logger, (char*) "SPI: command sent")
	LOG(logger, (char*) "SPI: sending address")
	SPI_TRANSMIT(address);
	LOG(logger, (char*) "SPI: address sent")
	LOG(logger, (char*) "SPI: sending mask")
	SPI_TRANSMIT(mask);
	LOG(logger, (char*) "SPI: mask sent")
	LOG(logger, (char*) "SPI: sending data")
	SPI_TRANSMIT(data);
	LOG(logger, (char*) "SPI: data sent")
	
	// release CS
	UNSELECT_CAN_CHIP(SPI_CS_PORT, SPI_CS_PIN)
	
}

void ProtocolHandlerMcp2515::InitCanBuffers(void)
{
	unsigned char i, address_1, address_2, address_3; 
	address_1 = TXB0CTRL;
	address_2 = TXB1CTRL;
	address_3 = TXB2CTRL;
	for (i = 0; i < 14; i++)
	{
		WriteRegister(address_1, 0);
		WriteRegister(address_2, 0);
		WriteRegister(address_3, 0);
		address_1++;
		address_2++;
		address_3++;
	}
	WriteRegister(RXB0CTRL, 0);
	WriteRegister(RXB1CTRL, 0);
}

unsigned char ProtocolHandlerMcp2515::Init(const unsigned char can_speed)
{
	CREATE_LOGGER(logger);
	unsigned char result = MCP_FAIL;
	char retries = 0;
	LOG(logger, (char*)"MCP2515.Init started...")
	Reset(); // after reset MCP2515 should be in CONFIGURATION MODE
	
	// any way check it, if fails perform 5 retries
	while (GET_MODE != MODE_CONFIG)
	{
		retries++;
		result = SetMode(MODE_CONFIG);
		if (retries == 5 && result != MCP_OK)
		{
			LOG(logger, (char*) "CONFIG_MODE initialization fails")
			return MCP_FAIL;
		}
	}
	LOG(logger, (char*) "CONFIG_MODE has initialized successfully")
	
	InitCanBuffers();
	WriteRegister(CANINTE, CAN_RX0IF_BIT | CAN_RX1IF_BIT);
	
	
	//enable both receive-buffers to receive any message
	BitModify(RXB0CTRL, MCP_RXB_RX_MASK | MCP_RXB_BUKT_MASK, MCP_RXB_RX_STDEXT | MCP_RXB_BUKT_MASK);
	BitModify(RXB1CTRL, MCP_RXB_RX_MASK, MCP_RXB_RX_STDEXT);
	
	result = MCP_FAIL;
	retries = 0;
	while (result != MCP_OK)
	{
		retries++;
		result = SetCanSpeed(can_speed);
		if (retries == 5 && result != MCP_OK)
		{
			LOG(logger, (char*) "Init - failed to set CAN speed")
			return result;
		}
	}
	LOG(logger, (char*) "Init - successfully set upped CAN speed")
	
	result = MCP_FAIL;
	retries = 0;
	while (result != MCP_OK)
	{
		retries++;
		result = SetMode(MODE_NORMAL);
		if (retries == 5 && result != MCP_OK)
		{
			LOG(logger, (char*) "Init - failed to get NORMAL_MODE")
			return result;
		}
	}
	LOG(logger, (char*) "Init - Initialization passed - NORMAL_MODE now")
	return result;
}

unsigned char ProtocolHandlerMcp2515::ReadRegister(unsigned char address)
{
	unsigned char data;
	
	//Set CS pin to low level
	SELECT_CAN_CHIP(SPI_CS_PORT, SPI_CS_PIN)
	
	SPI_TRANSMIT(READ);
	SPI_TRANSMIT(address);
	
	data = SPI_TRANSMIT(0xFF);
	
	UNSELECT_CAN_CHIP(SPI_CS_PORT, SPI_CS_PIN)
	return data;
}

void ProtocolHandlerMcp2515::ReadRxBuffer(unsigned char buffer_address, unsigned char status_rx, canmsg_t * p_canmsg)
{
	// store flags
	p_canmsg->flags.rtr = (status_rx >> 3) & 0x01;
	p_canmsg->flags.extended = (status_rx >> 4) & 0x01;

	
	SELECT_CAN_CHIP(SPI_CS_PORT, SPI_CS_PIN)
	
	ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, MCP2515_CMD_READ_RX | buffer_address);
	
	if(p_canmsg->flags.extended){
		p_canmsg->id = (unsigned long) ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, 0xff) << 21;
		unsigned long temp = ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, 0xff);
		p_canmsg->id |= (temp & 0xe0) << 13;
		p_canmsg->id |= (temp & 0x03) << 16;
		p_canmsg->id |= (unsigned long) ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, 0xff) << 8;
		p_canmsg->id |= (unsigned long)  ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, 0xff);
		} else {
		p_canmsg->id =  (unsigned long)  ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, 0xff) << 3;
		p_canmsg->id |= (unsigned long)  ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, 0xff) >> 5;
		ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, 0xff);
		ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, 0xff);
	}
	
	// get length and data
	
	p_canmsg->dlc = ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, 0xff) & 0x0f;
	if (!p_canmsg->flags.rtr) {
		unsigned char i;
		unsigned char length = p_canmsg->dlc;
		if (length > 8) length = 8;
		for (i = 0; i < length; i++) {
			p_canmsg->data[i] = ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, 0xff);
		}
	}
	
	SELECT_CAN_CHIP(SPI_CS_PORT, SPI_CS_PIN)
}

void ProtocolHandlerMcp2515::Reset(void)
{
	CREATE_LOGGER(logger)
	LOG(logger, (char*)"MCP2515.Reset started ...")
	//to start SPI transfer need to push CS low level (chip select or slave select)
	SELECT_CAN_CHIP(SPI_CS_PORT, SPI_CS_PIN)
	LOG(logger, (char*)"SPI is ready")
	//send 8bit via SPI
	SPI_TRANSMIT(RESET);
	LOG(logger, (char*)"SPI transmit ended")
	//to end SPI transfer need to push CS to high level (chip select or slave select)
	UNSELECT_CAN_CHIP(SPI_CS_PORT, SPI_CS_PIN)
	_delay_ms(10);
	
}

unsigned char ProtocolHandlerMcp2515::SetMode(const unsigned char desired_mode)
{
	CREATE_LOGGER(logger)
	unsigned char result;
	LOG(logger, (char*) "CANCTRL before BitModify:")
	char* canctrl_string = (char*) malloc(10);
	result = ReadRegister(CANCTRL);
	LOG(logger,(char*) itoa(result, canctrl_string, 2)) 
	LOG(logger, (char*) itoa(desired_mode, canctrl_string,2 ))
	BitModify(CANCTRL, MODE_MASK, desired_mode);
	LOG(logger, (char*) "CANCTRL after BitModify:")
	result = ReadRegister(CANCTRL);
	LOG(logger, (char*) itoa(result, canctrl_string, 2))
	free(canctrl_string);
	// apply 1110 0000 mask to received content
	result &= MODE_MASK;
	if (result == desired_mode)
	{
		return MCP_OK;
	}
	else
	{
		return MCP_FAIL;
	}
}

/**
 * \brief Set bit timing registers
 *
 * \param cnf1 Configuration register 1
 * \param cnf2 Configuration register 2
 * \param cnf3 Configuration register 3
 *
 * This function has only affect if mcp2515 is in configuration mode
 */
void ProtocolHandlerMcp2515::SetBitRateRegisters(unsigned char cnf1, unsigned char cnf2, unsigned char cnf3) {
    WriteRegister(MCP_REG_CNF1, cnf1);
    WriteRegister(MCP_REG_CNF2, cnf2);
    WriteRegister(MCP_REG_CNF3, cnf3);
}

unsigned char ProtocolHandlerMcp2515::SetCanSpeed(unsigned char can_speed)
{
	switch (can_speed)
	{
	case (0): // enum 0 - MCP_5kBPS in CanController
		SetBitRateRegisters(MCP2515_TIMINGS_500K);
		return MCP_OK;
		break;
	default:
		return MCP_FAIL;
	}
}

void ProtocolHandlerMcp2515::WriteRegister(unsigned char address, unsigned char data)
{
	  // set CS pin to low level
		SELECT_CAN_CHIP(SPI_CS_PORT, SPI_CS_PIN)
		
		SPI_TRANSMIT(WRITE);
		SPI_TRANSMIT(address);
		SPI_TRANSMIT(data);
		
		// release SS
		UNSELECT_CAN_CHIP(SPI_CS_PORT, SPI_CS_PIN)
}

unsigned char ProtocolHandlerMcp2515::mcp2515_read_status() {

	// set CS pin to low level
	SELECT_CAN_CHIP(SPI_CS_PORT, SPI_CS_PIN)
	
	ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, MCP2515_CMD_READ_STATUS );
	unsigned char status = ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, 0xff);
	
	// release SS
	UNSELECT_CAN_CHIP(SPI_CS_PORT, SPI_CS_PIN)

	return status;
}

unsigned char ProtocolHandlerMcp2515::mcp2515_rx_status(){
	
	// function implementation command Rx status in SPI interface. This command return whether message any buffers and which format can message
	
	// set CS pin to low level
	SELECT_CAN_CHIP(SPI_CS_PORT, SPI_CS_PIN)
	
	
	ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, MCP2515_CMD_RX_STATUS);
	unsigned char status = ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, 0xff);
	
	// release SS
	UNSELECT_CAN_CHIP(SPI_CS_PORT, SPI_CS_PIN)
	
	return status;
	
	
}
// 
bool ProtocolHandlerMcp2515::ReceiveMessage(canmsg_t * p_canmsg_1)
{
	// just a stub, could be deleted after with appropriate virtual functions
	// to do - should be added configuration of buffers to remove unnecessary functions
	// conditional compilation
	return 1;
}

	
	

bool ProtocolHandlerMcp2515::ReceiveMessage(canmsg_t * p_canmsg_1, canmsg_t * p_canmsg_2)
{
	CREATE_LOGGER(logger)
	
	unsigned char status =  0; //temporary for debug, combine with mcp2515_rx_status
	bool return_status = false;
	
	#if ENABLE_LOG == ON
	char* status_rx_value = (char*) malloc(10);
	LOG(logger, (char*) itoa(status, status_rx_value, 2))
	#endif
	
	status = mcp2515_rx_status();
	
	#if ENABLE_LOG == ON
	LOG(logger, (char*) "Status RX got:")
	LOG(logger, (char*) itoa(status, status_rx_value, 2))
	free(status_rx_value);
	#endif
	
	if( (status & MESSAGE_IN_RX0) == MESSAGE_IN_RX0) {
		ReadRxBuffer(BUFFER_RX0, status, p_canmsg_1);
		p_canmsg_1->timestamp = 0; //for debug purpose, this indicates that timestamp was changed
		return_status = true;
	}
	if( (status & MESSAGE_IN_RX1) == MESSAGE_IN_RX1) {
		ReadRxBuffer(BUFFER_RX1, status, p_canmsg_2);
		p_canmsg_2->timestamp = 0;
		return_status = true;
	}
	else {
		LOG(logger, (char*) "No message received")
		return return_status;
	}
	
	return return_status;
}

bool ProtocolHandlerMcp2515::ReceiveMessage(canmsg_t * p_canmsg_1, canmsg_t * p_canmsg_2, canmsg_t * p_canmsg_3, canmsg_t * p_canmsg_4)
{
	// just a stub, could be deleted after with appropriate virtual functions
	// to do - should be added configuration of buffers to remove unnecessary functions
	// conditional compilation
	return 1;
}

unsigned char ProtocolHandlerMcp2515::sendMessage(canmsg_t * p_canmsg) {

 unsigned char status = mcp2515_read_status();
 unsigned char address_load_buffer;
 unsigned char length;

 
 // check length
 length = p_canmsg->dlc;
 if (length > 8) length = 8;
 


 
 
  // get offest address of next free tx buffer  TXREQ - Message Transmit Request bit 
	//Buffer is currently pending transmission or Buffer is not currently pending transmission
		
  if ((status & TXB0CTRL_TXREQ) == 0) {                  ;
	  address_load_buffer = LOADBUF0_TX_SH;
	  } else if ((status & TXB1CTRL_TXREQ) == 0) {
	  address_load_buffer =LOADBUF1_TX_SH;
	  } else if ((status & TXB2CTRL_TXREQ) == 0) {
	  address_load_buffer = LOADBUF2_TX_SH;
	  } else {
	  // no free transmit buffer
	  return 0;
  }
  
   
  
  // set CS pin to low level..
   SELECT_CAN_CHIP(SPI_CS_PORT, SPI_CS_PIN)
  
  ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, address_load_buffer);

   if (p_canmsg->flags.extended) {
	   // All id divided into  
	   //               hight standard id    low standard id(ext id)   hight ext id    low ext id
	   //                  76543210         43210                     76543210        76543210  
	   //                     >> 21         calculation 432xxx10         >>8             direct transive
	   // transmit low standard id
	   ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, p_canmsg->id >> 21);     // load standard id hight 29-21 =8 hight bit
	   // transmit hight standard id which the must include bit4=0, bit2=0, bit3=1(massage id extended)
	   
	   ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, ((p_canmsg->id >> 13) & 0xe0) | ((p_canmsg->id >> 16) & 0x03) | 0x08);
	   // transmit hight extended id
	   ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, p_canmsg->id >> 8);
	   // transmit low extended id
	   ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, p_canmsg->id);
	   } else {
	    ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, p_canmsg->id >> 3);   // load standard id hight  11-3=8 bit
	    ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, p_canmsg->id << 5);   // load standard id low  3=8-5 bit
	    ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, 0);                   // load extended id hight
	    ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, 0);                   // load extended id low
   }
   
   // length and data
   if (p_canmsg->flags.rtr) {				// RTR Remote Transmission Request (Frame request - recessive  Frame data -dominate)
	    ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, p_canmsg->dlc | CAN_TXBxDLC_RTR);  // RTR fisical locate in TXBnDLC register in 6 bit. (this is a 0x40)
											// if 0 - data if  1- remoute  transmit request/ if true then setiings 1 in 6 bit 
	   } else {
	   ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, p_canmsg->dlc);
	   unsigned char i;
	   for (i = 0; i < length; i++) {
		   ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, p_canmsg->data[i]);
	   }
   }
   
   
   // release SS
   UNSELECT_CAN_CHIP(SPI_CS_PORT, SPI_CS_PIN)
   
   //_delay(1); ????????????????????????????????????????????????
   
   
    // Send massage in CAN in select RTS bit Request to Send
	
	// When Send via SPI the flags
	//     ABTF -Message Aborted Flag bit       1- Massage was aborted
	//    MLOA -Message Lost Arbitration        1-Message lost arbitration while being sent
	//     TXERR -Transmission Error Detected   1 = A bus error occurred while the message was being transmitted
	//    will be cleared automatically
	
   // set CS pin to low lewel..
   SELECT_CAN_CHIP(SPI_CS_PORT, SPI_CS_PIN)
   
   if (address_load_buffer == LOADBUF0_TX_SH) address_load_buffer = RTS_TXB0;
   ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, address_load_buffer);
   
   // release SS
   UNSELECT_CAN_CHIP(SPI_CS_PORT, SPI_CS_PIN)
   // check if interrupt
   unsigned char INTERRUPT_FLAGS = ReadRegister(CANINTF);
   
   // check empty tx buffers
   
   while((INTERRUPT_FLAGS && CAN_TX0IF_BIT == 0) | (INTERRUPT_FLAGS && CAN_TX1IF_BIT == 0 )| (INTERRUPT_FLAGS && CAN_TX2IF_BIT == 0)) {
	   
	  //  check error massage tx
	  INTERRUPT_FLAGS = ReadRegister(CANINTF);
	   if(INTERRUPT_FLAGS && CAN_MERRF_BIT ==1)  {
		   BitModify(CANINTF,CAN_MERRF_BIT,0 );
		   return 0;
		   
	   }
	   
	  }
	  // again check error massage
	   if(INTERRUPT_FLAGS && CAN_MERRF_BIT ==1)  {
		   BitModify(CANINTF,CAN_MERRF_BIT,0 );
		   return 0;
	   }
	  // set flag interrupt when buffer is empty
	  INTERRUPT_FLAGS = ReadRegister(CANINTF);
	  if(INTERRUPT_FLAGS && CAN_TX0IF_BIT == 1) BitModify(CANINTF, CAN_TX0IF_BIT, 0);
	  if(INTERRUPT_FLAGS && CAN_TX1IF_BIT == 1) BitModify(CANINTF, CAN_TX1IF_BIT, 0);
	  if(INTERRUPT_FLAGS && CAN_TX2IF_BIT == 1) BitModify(CANINTF, CAN_TX2IF_BIT, 0);
   
   return 1;
   
   
   
}

bool ProtocolHandlerMcp2515::writeMessage(canmsg_t * p_canmsg)
{
	//just a stub
	return true;
}