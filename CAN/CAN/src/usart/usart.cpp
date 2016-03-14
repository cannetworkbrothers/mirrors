/*
 * usart.cpp
 *
 * Created: 3/12/2016 5:38:32 PM
 *  Author: Igor
 */ 
#include "usart.hpp"

USART::USART(const long baud /* = 9600 */) {
	/* Set baud rate */
	#define BAUD_PRESCALLER (((F_CPU / (baud * 16UL))) - 1)
	UBRRH = (unsigned char)(BAUD_PRESCALLER>>8);
	UBRRL = (unsigned char)BAUD_PRESCALLER;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}

unsigned char USART::ReceiveChar(void) {
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) );
	/* Get and return received data from buffer */
	return UDR;
}

void USART::SendFrame(unsigned int data) {
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Copy ninth bit to TXB8 */
	UCSRB &= ~(1<<TXB8);
	if ( data & 0x0100 )
		UCSRB |= (1<<TXB8);
	/* Put data into buffer, sends the data */
	UDR = data;
}

void USART::Write(char * ptr_line) {
	while (*ptr_line != 0x00){
		SendFrame(*ptr_line);
		ptr_line++;
	}
}

void USART::WriteLine(char * ptr_string) {
	Write(ptr_string);
	//SendFrame((unsigned int) '\n'); // send "goto new line"
	SendFrame((unsigned int) '\r'); // send "carriage return"
}