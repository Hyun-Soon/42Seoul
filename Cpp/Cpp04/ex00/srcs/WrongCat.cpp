#include "WrongCat.hpp"

WrongCat::WrongCat()
{
	_type = "WrongCat";
	std::cout << "WrongCat default constructor called." << std::endl;
}

WrongCat::WrongCat(const WrongCat& other)
{
	_type = other._type;
	std::cout << "WrongCat copy constructor called." << std::endl;
}

const WrongCat& WrongCat::operator= (const WrongCat& other)
{
	if (this != &other)
		_type = other._type;
	
	return (*this);
}

WrongCat::~WrongCat()
{
	std::cout << "WrongCat destructor called." << std::endl;
}

void	WrongCat::makeSound() const
{
	std::cout << "Meow~" << std::endl;
}
