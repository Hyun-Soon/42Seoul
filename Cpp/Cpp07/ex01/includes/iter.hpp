#pragma once

#include <iostream>
#define unsigned long int size_t

template<typename T>
void printPlusOne(T& ref)
{
	std::cout << ++ref << std::endl;
}

template<typename T>
void printVal(const T& ref)
{
	std::cout << ref << std::endl;
}

template<typename T>
void printMinusOne(T& ref)
{
	std::cout << --ref << std::endl;
}

template<typename T>
void iter(T* addr, size_t len, void (*func)(T&))
{
	for (size_t i = 0; i < len; i++)
		func(addr[i]);
}

template<typename T>
void iter(T* addr, size_t len, void (*func)(const T&))
{
	for (size_t i = 0; i < len; i++)
		func(addr[i]);
}

template<typename T>
void iter(T* addr, size_t len, void (*func)(T*))
{
	for (size_t i = 0; i < len; i++)
		func(addr + i);
}

template<typename T>
void iter(T* addr, size_t len, void (*func)(const T*))
{
	for (size_t i = 0; i < len; i++)
		func(addr + i);
}

template<>
void printMinusOne(float& ref)
{
	std::cout << "function template<float> specialization" << std::endl;
	std::cout << --ref << std::endl;
}