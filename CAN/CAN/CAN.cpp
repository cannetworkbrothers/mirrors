/*
 * CAN.cpp
 *
 * Created: 18.11.2015 12:15:11
 *  Author: Admin
 */ 


#include <avr/io.h>
#include "Can_controller.h"
#include "MCU_atmega8.h"

int main(void)
{
    while(1)
    {
        //TODO:: Please write your application code 
		
		unsigned char data_register;
		
		mcu_atmega8 atmega8;
		MCP2515 mcp2515_1(atmega8);
		
		
	    Can_controller can_interface(atmega8, mcp2515_1);
		
		can_interface.init();
		can_interface.read();
		
		
		
		
    }
}