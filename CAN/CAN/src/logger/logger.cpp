/*
 * logger.cpp
 *
 * Created: 3/23/2016 8:51:20 AM
 *  Author: Igor
 */ 
#include "logger.hpp"

void strmerge(char* start_str_ptr, char* end_str_ptr, char* target_str_ptr){
	//get length of entire string
	int length = 0;
	int start_length;
	while (start_str_ptr[length] != '\0')
	{
		length++;
	}
	start_length = length;

	int index = -1;
	do
	{
		length++;
		index++;
	} while (end_str_ptr[index] != '\0');
	//char* target_str_ptr = (char*) malloc(length);

	//concatenate
	int j = 0;
	for (int i = 0; i < length; i++)
	{
		if (i < start_length)
		{
			target_str_ptr[i] = start_str_ptr[i];
		}
		else
		{
			target_str_ptr[i] = end_str_ptr[j];
			j++;
		}
	}
}