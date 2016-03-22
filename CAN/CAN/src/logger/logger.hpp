/*
 * logger.h
 *
 * Created: 3/20/2016 3:46:33 PM
 *  Author: Igor
 */ 


#ifndef LOGGER_H_
#define LOGGER_H_

#if ENABLE_LOG == ON
	#include "../usart/usart.hpp"
	#define CREATE_LOGGER(logger_var) USART logger_var;
	#define LOG(logger_var, msg) logger_var.WriteLine(msg);
#else
	#define CREATE_LOGGER(logger_var)
	#define LOG(logger_var, msg)
#endif


#endif /* LOGGER_H_ */