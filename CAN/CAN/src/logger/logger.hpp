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
	#define LOG_CHARS(logger_var, msg) logger_var.Write(msg);
#else
	#define CREATE_LOGGER(logger_var)
	#define LOG(logger_var, msg)
	#define LOG_CHARS(logger_var, msg)
#endif

void strmerge(char* start_str_ptr, char* end_str_ptr, char* target_str_ptr);

#endif /* LOGGER_H_ */