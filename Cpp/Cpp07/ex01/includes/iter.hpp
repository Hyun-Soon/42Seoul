#pragma once

#include <iostream>
#define unsigned long int size_t

template<typename T>
void printPlusOne(T* addr)
{
	std::cout << ++(*addr) << std::endl;
}

template<typename T>
void printVal(T* addr)
{
	std::cout << *addr << std::endl;
}

template<typename T>
void printMinusOne(T* addr)
{
	std::cout << --(*addr) << std::endl;
}

template<typename T>
void iter(T* addr, size_t len, void func(T*))
{
	for (size_t i = 0; i < len; i++)
		func(addr + i);
}

template<>
void printMinusOne(float* addr)
{
	std::cout << "function template<float> specialization" << std::endl;
	std::cout << --(*addr) << std::endl;
}