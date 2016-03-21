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

#define USART_SUPPORT ON
#define USB_SUPPORT OFF
#define ENABLE_LOG ON

#if USART_SUPPORT == ON
	#include "src/usart/usart.hpp"
#else
	#undef USART_SUPPORT
#endif

#include "src/logger/logger.hpp"

#endif /* MAIN_H_ */