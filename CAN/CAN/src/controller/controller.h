/*
 * mcu.h
 *
 * Created: 18.11.2015 23:18:46
 *  Author: Ad min
 */ 


class Controller
{
public:
	
	Controller() {};
	~Controller() {};
	
	//this function will be used by ProtocolHandler to connect SpiMasterTransmit callback function
	static unsigned char StaticSpiMasterTransmit(void *p, char cData)
	{
		// Get back into the class by treating p as the "this" pointer.
		return ((Controller *)p)->SpiMasterTransmit(cData);
		
	};		
	
	virtual char SpiMasterTransmit(char cData) = 0;
	
};