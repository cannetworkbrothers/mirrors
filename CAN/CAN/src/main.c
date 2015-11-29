/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "mcp2515.h"
#include "controller_atmega8/ControllerAtmega8.h"

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();

	/* Insert application code here, after the board has been initialized. */
	
	//TODO:: Please write your application code
	
	canmsg_t can_message_buffer;
		
	ControllerAtmega8 atmega8;
	Protocol_MCP2515 mcp2515;
	
	
	CAN_USB_INTERFACE can_interface(atmega8, mcp2515);
	
	can_interface.init()
	can_interface.receiveMessage(mcp2515, atmega8, &can_message_buffer);
}
