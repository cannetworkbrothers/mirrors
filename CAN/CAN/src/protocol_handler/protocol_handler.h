/*
 * Can_controller.h
 *
 * Created: 18.11.2015 23:44:52
 *  Author: Armin
 */ 

typedef unsigned char PIN;

//Function pointer calls controller_spi_transmit that takes a char and returns a char
typedef unsigned char (*callback_spi_transmit_ptr)(void*, char);

typedef struct
{
	unsigned long id;				// identifier (11 or 29 bit)
	struct {
		unsigned char rtr : 1;		// remote transmit request
		unsigned char extended : 1;	// extended identifier
	} flags;

	unsigned char dlc;				// data length code
	unsigned char data[8];			// payload data
	unsigned short timestamp;		// timestamp
} canmsg_t;

class ProtocolHandler
{
protected:
	callback_spi_transmit_ptr controller_spi_transmit_;
	void *controller_p;
		
public:
	ProtocolHandler() {};
	~ProtocolHandler() {};
    
	void ConnectSpiTransmitCallback(callback_spi_transmit_ptr cb, void *p)
	{
		controller_spi_transmit_ = cb;
		controller_p = p;
	};
	
	virtual unsigned char init(const unsigned char canSpeed) = 0;
	virtual bool getPin(PIN pin) = 0;
	virtual void setPin(PIN pin, bool level) = 0;
	virtual unsigned char readRegister(	unsigned char address) = 0;
	virtual void writeRegister(unsigned char address, unsigned char data) = 0;
	
	//returns true on success reception, false otherwise
	virtual bool receiveMessage(canmsg_t * p_canmsg) = 0;
	virtual unsigned char sendMessage(canmsg_t * p_canmsg) = 0;
	
	virtual bool writeMessage(canmsg_t * p_canmsg) =0;
	
	
	};