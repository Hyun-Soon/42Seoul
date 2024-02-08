#include "Cat.hpp"

Cat::Cat()
{
	_type = "Cat";
	std::cout << "Cat default constructor called." << std::endl;
}

Cat::Cat(const Cat& other)
{
	_type = other._type;
	std::cout << "Cat copy constructor called." << std::endl;
}

const Cat& Cat::operator= (const Cat& other)
{
	if (this != &other)
		_type = other._type;
	
	return (*this);
}

Cat::~Cat()
{
	std::cout << "Cat destructor called." << std::endl;
}

void	Cat::makeSound() const
{
	std::cout << "Meow~" << std::endl;
}
