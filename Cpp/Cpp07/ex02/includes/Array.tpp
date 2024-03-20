#pragma once

#include "Array.hpp"

template<typename T>
Array<T>::Array() : _arr(NULL), _size(0) {}

template<typename T>
Array<T>::~Array()
{
	if (_arr)
		delete [] _arr;
}

template<typename T>
Array<T>::Array(const Array& other)
{
	_arr = new T[other._size];
	for (size_t i = 0; i < other._size; i++)
		_arr[i] = other._arr[i];
	_size = other._size;
}

template<typename T>
const Array<T>& Array<T>::operator=(const Array& other)
{
	if (this != &other)
	{
		if (_arr)
			delete [] _arr;
		_arr = new T[other._size];
		for (size_t i = 0; i < other._size; i++)
			_arr[i] = other._arr[i];
	}
	return *this;
}

template<typename T>
Array<T>::Array(unsigned int n)
{
	_arr = new T[n];
	_size = n;
}

template<typename T>
T& Array<T>::operator[] (int idx)
{
	if (idx < 0 || idx >= static_cast<int>(_size))
		throw std::exception();
	return _arr[idx];
}

template<typename T>
size_t Array<T>::size() const
{
	return _size;
}