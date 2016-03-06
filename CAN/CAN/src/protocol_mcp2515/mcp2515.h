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

// standard timing definitions
#define MCP2515_TIMINGS_10K  0xfb, 0xad, 0x06	// PropSeg=6Tq, PS1=6Tq, PS2=7Tq, SamplePoint=65%, SJW=4
#define MCP2515_TIMINGS_20K  0xdd, 0xad, 0x06   // PropSeg=6Tq, PS1=6Tq, PS2=7Tq, SamplePoint=65%, SJW=4
#define MCP2515_TIMINGS_50K  0xcb, 0xad, 0x06   // PropSeg=6Tq, PS1=6Tq, PS2=7Tq, SamplePoint=65%, SJW=4
#define MCP2515_TIMINGS_100K 0xc5, 0xad, 0x06   // PropSeg=6Tq, PS1=6Tq, PS2=7Tq, SamplePoint=65%, SJW=4
#define MCP2515_TIMINGS_125K 0xc5, 0xa4, 0x04   // PropSeg=5Tq, PS1=5Tq, PS2=5Tq, SamplePoint=68.75%, SJW=4
#define MCP2515_TIMINGS_250K 0xc2, 0xa4, 0x04	// PropSeg=5Tq, PS1=5Tq, PS2=5Tq, SamplePoint=68.75%, SJW=4
#define MCP2515_TIMINGS_500K 0xc1, 0x9a, 0x03   // PropSeg=3Tq, PS1=4Tq, PS2=4Tq, SamplePoint=66.67%, SJW=4
#define MCP2515_TIMINGS_800K 0xc0, 0xa3, 0x04   // PropSeg=4Tq, PS1=5Tq, PS2=5Tq, SamplePoint=66.67%, SJW=4
#define MCP2515_TIMINGS_1M   0xc0, 0x9a, 0x03   // PropSeg=4Tq, PS1=3Tq, PS2=4Tq, SamplePoint=66.67%, SJW=4


// command definitions - TODO: move to separate header file
#define RESET           0b11000000 // Сброс MCP2515
#define READ            0b00000011 // Читать регистр MCP2515
#define WRITE           0b00000010 // Записать в регистр MCP2515
#define WRITEBIT        0b00000101
#define MCP2515_CMD_LOAD_TX 0x40
#define READBUF0_RX_SH  0b10010000
#define READBUF0_RX_D0  0b10010010
#define READBUF1_RX_SH  0b10010100
#define READBUF1_RX_D0  0b10010110
#define LOADBUF0_TX_SH  0b01000000
#define LOADBUF0_TX_D0  0b01000001
#define LOADBUF1_TX_SH  0b01000010
#define LOADBUF1_TX_D0  0b01000011
#define LOADBUF2_TX_SH  0b01000100
#define LOADBUF2_TX_D0  0b01000101
#define RTS_TXB0        0b00000001 // Отправить сообщение из буфера 1
#define RTS_TXB1        0b00000010 // Отправить сообщение из буфера 2
#define RTS_TXB2        0b00000100 // Отправить сообщение из буфера 3
#define RTS_TXB_ALL     0b00000111 // Отправить сообщения из всех буферов
#define MCP2515_CMD_READ_STATUS 0xA0


// register definitions

#define     CANSTAT     0b00001110	  // CAN status register
#define     CANCTRL     0b00001111  // В PIC18 - CANCON
 
#define     RXF0SIDH    0b00000000
#define     RXF0SIDL    0b00000001
#define     RXF0EID8    0b00000010
#define     RXF0EID0    0b00000011
#define     RXF1SIDH    0b00000100
#define     RXF1SIDL    0b00000101
#define     RXF1EID8    0b00000110
#define     RXF1EID0    0b00000111
#define     RXF2SIDH    0b00001000
#define     RXF2SIDL    0b00001001
#define     RXF2EID8    0b00001010
#define     RXF2EID0    0b00001011
#define     BFPCTRL     0b00001100
#define     TXRTSCTRL   0b00001101
 
#define     RXF3SIDH    0b00010000
#define     RXF3SIDL    0b00010001
#define     RXF3EID8    0b00010010
#define     RXF3EID0    0b00010011
#define     RXF4SIDH    0b00010100
#define     RXF4SIDL    0b00010101
#define     RXF4EID8    0b00010110
#define     RXF4EID0    0b00010111
#define     RXF5SIDH    0b00011000
#define     RXF5SIDL    0b00011001
#define     RXF5EID8    0b00011010
#define     RXF5EID0    0b00011011
#define     TEC     0b00011100
#define     REC     0b00011101
 
#define     RXM0SIDH    0b00100000
#define     RXM0SIDL    0b00100001
#define     RXM0EID8    0b00100010
#define     RXM0EID0    0b00100011
#define     RXM1SIDH    0b00100100
#define     RXM1SIDL    0b00100101
#define     RXM1EID8    0b00100110
#define     RXM1EID0    0b00100111
#define		MCP2515_REG_CNF1 0x2A
#define		MCP2515_REG_CNF2 0x29
#define		MCP2515_REG_CNF3 0x28
#define     CANINTE     0b00101011 // PIE3, Устанавливаем желаемые флаги прерываний
#define     CANINTF     0b00101100 // INTERRUPT FLAG
#define     EFLG        0b00101101
 

 
#define     RXB0CTRL    0b01100000 // см. RXBnCON

#define     RXB0SIDH    0b01100001 // Идентификатор стандартного сообщения приемного буфера 0, СТАРШИЙ байт
#define     RXB0SIDL    0b01100010 // Идентификатор стандартного сообщения приемного буфера 0, МЛАДШИЙ байт
#define     RXB0EID8    0b01100011 // Идентификатор расширенного сообщения приемного буфера 0, СТАРШИЙ байт
#define     RXB0EID0    0b01100100 // Идентификатор расширенного сообщения приемного буфера 0, МЛАДШИЙ байт

#define     RXB0DLC     0b01100101
#define     RXB0D0      0b01100110
#define     RXB0D1      0b01100111
#define     RXB0D2      0b01101000
#define     RXB0D3      0b01101001
#define     RXB0D4      0b01101010
#define     RXB0D5      0b01101011
#define     RXB0D6      0b01101100
#define     RXB0D7      0b01101101
 
#define     RXB1CTRL    0b01110000
#define     RXB1SIDH    0b01110001
#define     RXB1SIDL    0b01110010
#define     RXB1EID8    0b01110011
#define     RXB1EID0    0b01110100
#define     RXB1DLC     0b01110101
#define     RXB1D0      0b01110110
#define     RXB1D1      0b01110111
#define     RXB1D2      0b01111000
#define     RXB1D3      0b01111001
#define     RXB1D4      0b01111010
#define     RXB1D5      0b01111011
#define     RXB1D6      0b01111100
#define     RXB1D7      0b01111101


// CAN Rx Buffer Control bit definitions
#define CAN_RXRTR_BIT         0x08  // Request remote transmit
#define CAN_ACCFLT0_BITS      0x00  // Use Acceptance filter 0
#define CAN_ACCFLT1_BITS      0x01  // Use Acceptance filter 1
#define CAN_ACCFLT2_BITS      0x02  // Use Acceptance filter 2
#define CAN_ACCFLT3_BITS      0x03  // Use Acceptance filter 3
#define CAN_ACCFLT4_BITS      0x04  // Use Acceptance filter 4
#define CAN_ACCFLT5_BITS      0x05  // Use Acceptance filter 5
#define CAN_FLTR_OFF_BITS     0x60  // Receive all messages
#define CAN_FLTR_EXT_BITS     0x40  // Receive only extented ID packets
#define CAN_FLTR_STD_BITS     0x20  // Receive only standard ID packets
#define CAN_FLTR__BITS        0x00  // Receive standard or extended ID packets

// CAN_TXBxCTRL_REG bit definitions
#define CAN_TXP0_BITS         0x00  // Transmit priority zero (lowest)
#define CAN_TXP1_BITS         0x01  // Transmit priority one
#define CAN_TXP2_BITS         0x02  // Transmit priority two
#define CAN_TXP3_BITS         0x03  // Transmit priority three (highest)
#define CAN_TXREQ_BIT         0x08  // Request message transmit
#define CAN_TXERR_BIT         0x10  // Transmit error
#define CAN_MLOA_BIT          0x20  // Message lost arbitration
#define CAN_ABORT_BIT         0x40  // Message aborted

// CAN_TXBxDLC_REG bit definitions

#define CAN_TXBxDLC_RTR 0x40       // Remote transmit request bit



// CAN_INTE_REG bit definitions - clear interrupt flags using bit modify instruction
#define CAN_RX0IE_BIT         0x01  // Rx Buffer 0 interrupt enable
#define CAN_RX1IE_BIT         0x02  // Rx Buffer 0 interrupt enable
#define CAN_TX0IE_BIT         0x04  // Tx 0 buffer empty flag
#define CAN_TX1IE_BIT         0x08  // Tx 1 buffer empty flag
#define CAN_TX2IE_BIT         0x10  // Tx 2 buffer empty flag

// CAN_INTF_REG bit definitions - clear interrupt flags using bit modify instruction
#define CAN_RX0IF_BIT         0x01  // Tx 0 buffer empty flag
#define CAN_RX1IF_BIT         0x02  // Tx 0 buffer empty flag
#define CAN_TX0IF_BIT         0x04  // Tx 0 buffer empty flag
#define CAN_TX1IF_BIT         0x08  // Tx 1 buffer empty flag
#define CAN_TX2IF_BIT         0x10  // Tx 2 buffer empty flag
#define CAN_ERRIF_BIT         0x20  // Error interrupt flag
#define CAN_WAKIF_BIT         0x40  // Error interrupt flag
#define CAN_MERIF_BIT         0x80  // Error interrupt flag

// CAN Load Tx Buffer bit definitions
#define TXB0SIDH					0x00
#define TXB0D0						0x01
#define TXB1SIDH					0x02
#define TXB1D0						0x03
#define TXB2SIDH					0x04
#define TXB2D0						0x05

// Request to send Packet command control bit definitions
#define TxREQ0 					0x01
#define TxREQ1			 			0x02
#define TxREQ2 					0x04

// CAN_CONFIG_REG bit definitions
#define CAN_NORMAL_BITS       0x00  // Set to this mode to send and receive packets
#define CAN_CONFIG_BITS       0x80  // Set to this mode to initialize MCP2515
#define CAN_LOOPBACK_BITS     0x40
#define CAN_SLEEP_BITS        0x20
#define CAN_LISTEN_BITS       0x60
#define CAN_1SHOT_BIT         0x08
#define CAN_ABORT_ALL_BIT     0x10
#define CAN_CLKEN_BIT         0x04  // Clock out enable - not used on ECE 341 board
#define CAN_CLKPRE1_BITS      0x00  // Clock out = Fosc/1 - not used on ECE 341 board
#define CAN_CLKPRE2_BITS      0x01  // Clock out = Fosc/2 - not used on ECE 341 board
#define CAN_CLKPRE4_BITS      0x02  // Clock out = Fosc/4 - not used on ECE 341 board
#define CAN_CLKPRE8_BITS      0x03  // Clock out = Fosc/8 - not used on ECE 341 board

// CAN Status READ results
#define CAN_RX0IF_STATUS_BIT  0x01  // Receiver buffer 0 full status bit
#define CAN_RX1IF_STATUS_BIT  0x02  // Receiver buffer 1 request to send
#define CAN_TX0REQ_STATUS_BIT 0x04  // Receiver buffer 0 request to send
#define CAN_TX0IF_STATUS_BIT  0x08  // Transmit buffer 0 empty status bit
#define CAN_TX1REQ_STATUS_BIT 0x10  // Receiver buffer 1 request to send
#define CAN_TX1IF_STATUS_BIT  0x20  // Transmit buffer 1 empty status bit
#define CAN_TX2REQ_STATUS_BIT 0x40  // Receiver buffer 2 request to send
#define CAN_TX2IF_STATUS_BIT  0x80  // Transmit buffer 2 empty status bit

// CAN Read status bit definitions
#define	CANINTF_RX0IF			0x01	// Rx buffer 0 full interrupt flag
#define	CANINTF_RX1IF			0x02  // Rx buffer 1 full interrupt flag
#define	TXB0CTRL_TXREQ			0x04	// Tx buffer 0 transmit request flag
#define	CANINTF_TX0IF			0x08	// Tx buffer 0 empty interrupt flag
#define	TXB1CTRL_TXREQ			0x10	// Tx buffer 1 transmit request flag
#define	CANINTF_TX1IF			0x20  // Tx buffer 1 empty interrupt flag
#define	TXB2CTRL_TXREQ			0x40	// Tx buffer 2 transmit request flag
#define	CANINTF_TX2IF			0x80	// Tx buffer 2 empty interrupt flag

#define MAX_CAN_PKT_LEN			8		// Maximum CAN message length
#define PACKET_SIZE           20    // CAN packet buffer size

// External Interrupt Expansion

#define IOX_PORT0          	0x76     // I2C Expansion IC 0
#define IOX_PORT1          	0x72     // I2C Expansion IC 1
#define EXT_INTR0          	0x8000   // Flag to signal external interrupt
#define EXT0_VECTOR        	0x00     // Vector address for external interrupt 0
#define EXT_INTR_CFG       	0x11     // External interrupt setup value
#define EXT_INTR_OFF       	0x00     // Disable external interrupts value
#define CAN_int            	0x04     // CAN interrupt channel on IOX_PORT0
#define Exp_intr5          	0x20     // Expansion IO interrupt for BUTT 3
#define Exp_intr6          	0x40     // Expansion IO interrupt for BUTT 2
#define Exp_intr3          	0x08     // Expansion IO interrupt for BUTT 4
#define Exp_intr4          	0x10     // Expansion IO interrupt for BUTT 5
#define Exp_intr2          	0x04     // Expansion IO interrupt for BUTT 5

#define PG0                	0x01     // Use Port G.0 bit for  "CAN Packet Received"
#define PG0bit             	0x00     // Port G.0 bit position
#define PG1                	0x02     // Use Port G.1 bit for  "CAN Packet Sent
#define PG1bit             	0x01     // Port G.1 bit position
#define SETBIT             	0x01     // Set bit control
#define CLEARBIT           	0x00     // Clear bit control






#endif /* MCP2515_H_ */