#include "Animal.hpp"

Animal::Animal() : _type("Animal")
{
	std::cout << "Animal default constructor called." << std::endl;
}

Animal::Animal(const Animal& other) : _type(other._type)
{
	std::cout << "Animal destructor called." << std::endl;
}

const Animal& Animal::operator= (const Animal& other)
{
	if (this != &other)
		_type = other._type;

	return (*this);
}

Animal::~Animal()
{
	std::cout << "Animal destructor called." << std::endl;
}

void	Animal::makeSound() const
{
	std::cout << "Animal sound" << std::endl;
}

const std::string& Animal::getType() const
{
	return (_type);
}