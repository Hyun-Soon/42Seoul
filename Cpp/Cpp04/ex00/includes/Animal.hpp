#pragma once
#include <iostream>

class Animal
{
protected:
	std::string	_type;
public:
	Animal();
	Animal(const Animal& other);
	const Animal& operator= (const Animal& other);
	virtual ~Animal();
	virtual void		makeSound() const;
	const std::string&	getType() const;
};
