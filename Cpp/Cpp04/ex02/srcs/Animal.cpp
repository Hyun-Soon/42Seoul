#include "Animal.hpp"

Animal::~Animal()
{
	std::cout << "Animal destructor called." << std::endl;
}

const std::string& Animal::getType() const
{
	return (_type);
}