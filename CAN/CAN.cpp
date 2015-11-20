/*
 * CAN.cpp
 *
 * Created: 18.11.2015 12:15:11
 *  Author: Admin
 */ 


#include <avr/io.h>

int main(void)
{
    while(1)
    {
        //TODO:: Please write your application code 
		
		unsigned char data_register;
		
		mcu_atmega8 mcu_atmega8;
		MCP2515 mcp2515(mcu_atmega8);
		
		
		Can_interface Can_controller(mcu_atmega8, mcp2515);
		
		Can_controller.init();
		Can_controller.read();
		
		
		
		data_register = Can_controller.mcp2515_read_register(0x34);
    }
}