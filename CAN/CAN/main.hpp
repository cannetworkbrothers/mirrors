/*
 * main.h
 *
 * Created: 3/12/2016 5:25:17 PM
 *  Author: Igor
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#ifndef F_CPU
	#define F_CPU 12000000UL
#endif

#include <avr/io.h>

#define	ON 1
#define	OFF 0

//USART configuration
#define USART_SUPPORT ON
//USART_SPEED is COM speed, possible values:
//100, 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 38400, 56000, 57600, 115200, 128000, 256000
#define USART_SPEED 9600
#define USB_SUPPORT OFF
#define ENABLE_LOG ON

#if USART_SUPPORT == ON
	#include "src/usart/usart.hpp"
#else
	#undef USART_SUPPORT
#endif

#if ENABLE_LOG == OFF
	#include "src/logger/logger.hpp"
#else
	#undef ENABLE_LOG
#endif

#endif /* MAIN_H_ */