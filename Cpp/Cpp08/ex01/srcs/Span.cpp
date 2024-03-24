#include "Span.hpp"
#include <iostream>



Span::Span(unsigned int N) : _maxSize(N)
{
	_v.reserve(N);
}

Span::Span(const Span& other) : _maxSize(other._maxSize), _v(other._v) {}

Span& Span::operator=(const Span& other)
{
	if (this != &other)
	{
		_v = other._v; 
		const_cast<unsigned int&>(_maxSize) = other._maxSize;
	}
	return *this;
}

Span::~Span() {}

void Span::addNumber(unsigned int n)
{
	if (_v.size() >= _maxSize)
		throw std::exception();
	
	_v.push_back(n);
}

unsigned int Span::shortestSpan()
{
	if (_v.size() < 2)
		throw std::exception();

	std::sort(_v.begin(), _v.end());
	int minRet = _v.back() - _v.front();
	for (size_t i = 0; i < _v.size() - 2; i++)
		if (_v[i + 1] - _v[i] < minRet)
			minRet = _v[i + 1] - _v[i];
	
	return minRet;
}

unsigned int Span::longestSpan()
{
	if (_v.size() < 2)
		throw std::exception();

	std::sort(_v.begin(), _v.end());
	return _v.back() - _v.front();
}
