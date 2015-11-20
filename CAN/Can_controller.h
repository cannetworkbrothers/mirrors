/*
 * Can_controller.h
 *
 * Created: 18.11.2015 23:44:52
 *  Author: Admin
 */ 


#ifndef CAN_CONTROLLER_H_
#define CAN_CONTROLLER_H_


class Can_controller
{
	
	private:
	mcu mcu;
	can can;
	public:
	Can_controller(mcu d_mcu, can d_can) {mcu = d_mcu; c = d_can;};
	void init();
	void read();
	
	};


#endif /* CAN_CONTROLLER_H_ */