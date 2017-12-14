#pragma once
#include <new>
#ifndef ERRORS_H
#define ERRORS_H
class NoMem {
public:
	NoMem() {}
};

class OutOfBounds
{
public:
	OutOfBounds(){}
};

void my_new_handler()
{
	throw NoMem();
}

std::new_handler Old_Handler = std::set_new_handler(my_new_handler);   //set an new exception for new function
#endif // !ERRORS_H

