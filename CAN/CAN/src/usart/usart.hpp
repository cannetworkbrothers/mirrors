/*
 * usart.h
 *
 * Created: 3/12/2016 5:38:57 PM
 *  Author: Igor
 */ 


#ifndef USART_H_
#define USART_H_

#ifndef MAIN_H_
	#include "../../main.hpp"
#endif

class USART  {
	
	public:
	USART(const long baud = USART_SPEED);
	~USART();
	
	unsigned char	ReceiveChar(void);
	void			SendFrame(unsigned int);
	void			Write(char *);
	void			WriteLine(char *);
	};

#endif /* USART_H_ */