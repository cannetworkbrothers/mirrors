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
#define SPI_TRANSMIT(adr) ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, adr);

/* 
 * Implementation of MCP2515 private members
 */

void ProtocolHandlerMcp2515::BitModify(unsigned char address, unsigned char mask, unsigned char data) {
	
	CREATE_LOGGER(logger)
	// set CS pin to low level
	setPin(SPI_CS_PORT, SPI_CS_PIN, false);
	
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
	setPin(SPI_CS_PORT, SPI_CS_PIN, true);
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
	unsigned char result = 0;
	LOG(logger, (char*)"MCP2515.Init started...")
	Reset();
	
	// initialization only configure mode
	if (GET_MODE != MODE_CONFIG) 
		result = SetMode(MODE_CONFIG);
	
	//check if MODE_CONFIG was successfully set upped
	if (result > 0)
	{
		LOG(logger, (char*) "Failed to setup CONFIG_MODE")
		return result;
	}
	LOG(logger, (char*) "CONFIG_MODE has initialized successfully")
	
	//// set all interrupt Flags
	//WriteRegister(CANINTE, 0xFF);
	//
	//// configure filter
	//WriteRegister(RXB0CTRL, 0x00); // use filter for standard and extended frames
	//WriteRegister(RXB1CTRL, 0x00); // use filter for standard and extended frames
//
	//// initialize filter mask
	//WriteRegister(RXM0SIDH, 0x00);
	//WriteRegister(RXM0SIDL, 0x00);
	//WriteRegister(RXM0EID8, 0x00);
	//WriteRegister(RXM0EID0, 0x00);
	//WriteRegister(RXM1SIDH, 0x00);
	//WriteRegister(RXM1SIDL, 0x00);
	//WriteRegister(RXM1EID8, 0x00);
	//WriteRegister(RXM1EID0, 0x00);
	//
	//// set pin assigment RX0BF and RX1BF
	//
	//// RXnBF pin contrjl and status reg all 1 pins setting interrupt 
	//// Теперь на них будет 0, когда данные будут в соответствующем буфере.
	//WriteRegister(BFPCTRL, 0x0F);
	
	InitCanBuffers();
	WriteRegister(CANINTE, CAN_RX0IF_BIT | CAN_RX1IF_BIT);
	
	//enable both receive-buffers to receive any message
	BitModify(RXB0CTRL, MCP_RXB_RX_MASK | MCP_RXB_BUKT_MASK, MCP_RXB_RX_STDEXT | MCP_RXB_BUKT_MASK);
	BitModify(RXB1CTRL, MCP_RXB_RX_MASK, MCP_RXB_RX_STDEXT);
	
	SetCanSpeed(can_speed);
	
	result = SetMode(MODE_NORMAL);
	if (result > 0)
	{
		LOG(logger, (char*)"Init of NORMAL_MODE fails.")
		return result;
	}
	LOG(logger, (char*)"Init of Normal_MODE success");
	
	/* Let's check some register value*/
	char register_value[9];
	char msg[] = "RXB1SIDH ";
	char* out_message = (char*) malloc(30);
	itoa(ReadRegister(RXB1SIDH), register_value, 2);
	strmerge(msg, register_value, out_message);
	LOG(logger, (char*)register_value)
	free(out_message);
	return result;
}

unsigned char ProtocolHandlerMcp2515::ReadRegister(unsigned char address)
{
	unsigned char data;
	
	//Set CS pin to low level
	setPin(SPI_CS_PORT, SPI_CS_PIN, false);
	
	SPI_TRANSMIT(READ);
	SPI_TRANSMIT(address);
	
	data = SPI_TRANSMIT(0xFF);
	
	setPin(SPI_CS_PORT, SPI_CS_PIN, true);
	return data;
}

void ProtocolHandlerMcp2515::Reset(void)
{
	CREATE_LOGGER(logger)
	LOG(logger, (char*)"MCP2515.Reset started ...")
	//to start SPI transfer need to push CS low level (chip select or slave select)
	setPin(SPI_CS_PORT, SPI_CS_PIN, false);
	LOG(logger, (char*)"SPI is ready")
	//send 8bit via SPI
	SPI_TRANSMIT(RESET);
	LOG(logger, (char*)"SPI transmit ended")
	//to end SPI transfer need to push CS to high level (chip select or slave select)
	setPin(SPI_CS_PORT, SPI_CS_PIN, true);
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
	CREATE_LOGGER(logger)
	switch (can_speed)
	{
	case (0): // enum 0 - MCP_5kBPS in CanController
		SetBitRateRegisters(MCP_8MHz_5kBPS);
		LOG(logger, (char*)"Setup CAN speed pass.")
		return MCP_OK;
		break;
	default:
		LOG(logger, (char*)"Setup CAN speed fails.")
		return MCP_FAIL;
	}
}

bool ProtocolHandlerMcp2515::getPin(unsigned char pin)
{
	return true;
}

void ProtocolHandlerMcp2515::setPin(unsigned char port, unsigned char pin, bool level)
{
	if (level == true)
	{
		//set port.pin to High level
		port |= (1<<pin);	
	} 
	else
	{
		//set port.pin to LOW level
		port &= ~(1<<pin);
	}
}

void ProtocolHandlerMcp2515::WriteRegister(unsigned char address, unsigned char data)
{
	  // set CS pin to low level
		setPin(SPI_CS_PORT, SPI_CS_PIN, false);
		
		SPI_TRANSMIT(WRITE);
		SPI_TRANSMIT(address);
		SPI_TRANSMIT(data);
		
		// release SS
		setPin(SPI_CS_PORT, SPI_CS_PIN, true);
}

unsigned char ProtocolHandlerMcp2515::mcp2515_read_status() {

	// set CS pin to low level
	setPin(SPI_CS_PORT, SPI_CS_PIN, false);
	
	ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, MCP2515_CMD_READ_STATUS );
	unsigned char status = ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, 0xff);
	
	// release SS
	setPin(SPI_CS_PORT, SPI_CS_PIN, true);

	return status;
}

unsigned char ProtocolHandlerMcp2515::mcp2515_rx_status(){
	
	// function implementation command rx status in SPI interface. This command return whether message any buffers and wich format can message
	
	// set CS pin to low lewel
	setPin(SPI_CS_PORT, SPI_CS_PIN, false);
	
	
	ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, MCP2515_CMD_RX_STATUS);
	unsigned char status = ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, 0xff);
	
	// release SS
	setPin(SPI_CS_PORT, SPI_CS_PIN, true);
	
	return status;
	
	
}

bool ProtocolHandlerMcp2515::receiveMessage(canmsg_t * p_canmsg){
		
	unsigned char status = mcp2515_rx_status();
	unsigned char Mask_address_rx_buffer;
	
	if(status == Message_in_RX0) Mask_address_rx_buffer = Buffer_RX0;
	else if(status == Message_in_RX1) Mask_address_rx_buffer = Buffer_RX1;
	else return 0;
	
	// store flags
	p_canmsg->flags.rtr = (status >> 3) & 0x01;
	p_canmsg->flags.extended = (status >> 4) & 0x01;

	
	setPin(SPI_CS_PORT, SPI_CS_PIN, false);
	
	ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, MCP2515_CMD_READ_RX | Mask_address_rx_buffer);
	
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
     // reset flag rx buffers register when empty
	 
	 if (Mask_address_rx_buffer == 0) Mask_address_rx_buffer = 1;
	 else Mask_address_rx_buffer = 2;
	 BitModify(MCP2515_REG_CANINTF, Mask_address_rx_buffer, 0);
	 
	 
	// release SS
	// set CS pin to low lewel
	setPin(SPI_CS_PORT, SPI_CS_PIN, false);
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
   setPin(SPI_CS_PORT, SPI_CS_PIN, false);
  
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
   setPin(SPI_CS_PORT, SPI_CS_PIN, true);
   
   //_delay(1); ????????????????????????????????????????????????
   
   
    // Send massage in CAN in select RTS bit Request to Send
	
	// When Send via SPI the flags
	//     ABTF -Message Aborted Flag bit       1- Massage was aborted
	//    MLOA -Message Lost Arbitration        1-Message lost arbitration while being sent
	//     TXERR -Transmission Error Detected   1 = A bus error occurred while the message was being transmitted
	//    will be cleared automatically
	
   // set CS pin to low lewel..
   setPin(SPI_CS_PORT, SPI_CS_PIN, false);
   
   if (address_load_buffer == LOADBUF0_TX_SH) address_load_buffer = RTS_TXB0;
   ProtocolHandler::controller_spi_transmit_(ProtocolHandler::controller_p, address_load_buffer);
   
   // release SS
   setPin(SPI_CS_PORT, SPI_CS_PIN, true);
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