#include "Data.hpp"

Data::Data() : _data(1014) {}

Data::Data(int data) : _data(data) {}

Data::Data(const Data &other) : _data(other._data) {}

const Data &Data::operator=(const Data &other)
{
	if (this != &other)
		_data = other._data;
	return *this;
}

Data::~Data() {}

const int &Data::getData() const
{
	return _data;
}