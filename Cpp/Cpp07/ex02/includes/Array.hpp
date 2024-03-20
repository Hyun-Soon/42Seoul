#pragma once

#include <unistd.h>
#include <exception>

template<typename T>
class Array
{
private:
	T* _arr;
	size_t _size;
public:
	Array();
	Array(unsigned int n);
	Array(const Array& other);
	const Array& operator=(const Array& other);
	T& operator[] (int idx);
	size_t size() const;
	~Array();
};

#include "Array.tpp"