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

	std::vector<int> temp = _v;
	std::sort(temp.begin(), temp.end());
	int minRet = temp.back() - temp.front();
	for (size_t i = 0; i < temp.size() - 2; i++)
		if (temp[i + 1] - temp[i] < minRet)
			minRet = temp[i + 1] - temp[i];
	
	return minRet;
}

unsigned int Span::longestSpan()
{
	if (_v.size() < 2)
		throw std::exception();

	std::vector<int> temp = _v;
	std::sort(temp.begin(), temp.end());
	return temp.back() - temp.front();
}
