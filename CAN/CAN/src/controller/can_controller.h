/*
 * mcu.h
 *
 * Created: 18.11.2015 23:18:46
 *  Author: Ad min
 */ 


class CanController
{
public:
	
	CanController() {};
	~CanController() {};
	
	static unsigned char static_SPI_Master_Transmit(void *p, unsigned char cData)
	{
		// Get back into the class by treating p as the "this" pointer.
		((CanController *)p)->SPI_MasterTransmit(cData);
		return 0;
	};		
	
	virtual unsigned char SPI_MasterTransmit(char cData) = 0;
	
};