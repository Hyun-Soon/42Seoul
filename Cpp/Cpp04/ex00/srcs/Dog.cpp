#include "Dog.hpp"

Dog::Dog()
{
	_type = "Dog";
	std::cout << "Dog default constructor called." << std::endl;
}

Dog::Dog(const Dog& other)
{
	_type = other._type;
	std::cout << "Dog copy constructor called." << std::endl;
}

const Dog& Dog::operator= (const Dog& other)
{
	if (this != &other)
		_type = other._type;
	
	return (*this);
}

Dog::~Dog()
{
	std::cout << "Dog destructor called." << std::endl;
}

void	Dog::makeSound() const
{
	std::cout << "Woof Woof!" << std::endl;
}
