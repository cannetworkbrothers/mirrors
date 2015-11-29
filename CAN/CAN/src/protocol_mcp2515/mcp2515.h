/*
 * mcp2515.h
 *
 * Created: 11/29/2015 11:28:21 AM
 *  Author: Igor
 */ 


#ifndef MCP2515_H_
#define MCP2515_H_


// pin mapping
#define MCP2515_CS PORTC0


// command definitions - TODO: move to separate header file
#define MCP2515_CMD_RESET 0xC0
#define MCP2515_CMD_READ 0x03
#define MCP2515_CMD_WRITE 0x02
#define MCP2515_CMD_BIT_MODIFY 0x05
#define MCP2515_CMD_READ_STATUS 0xA0
#define MCP2515_CMD_LOAD_TX 0x40
#define MCP2515_CMD_RTS 0x80
#define MCP2515_CMD_RX_STATUS 0xB0
#define MCP2515_CMD_READ_RX 0x90

// register definitions
#define MCP2515_REG_CNF1 0x2A
#define MCP2515_REG_CNF2 0x29
#define MCP2515_REG_CNF3 0x28
#define MCP2515_REG_CANCTRL 0x0F
#define MCP2515_REG_RXB0CTRL 0x60
#define MCP2515_REG_RXB1CTRL 0x70
#define MCP2515_REG_BFPCTRL 0x0C
#define MCP2515_REG_CANINTF 0x2C
#define MCP2515_REG_CANINTE 0x2B


#endif /* MCP2515_H_ */