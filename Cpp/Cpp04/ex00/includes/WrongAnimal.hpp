#pragma once
#include <iostream>

class WrongAnimal
{
protected:
	std::string	_type;
public:
	WrongAnimal();
	WrongAnimal(const WrongAnimal& other);
	const WrongAnimal& operator= (const WrongAnimal& other);
	virtual ~WrongAnimal();
	void		makeSound() const;
	const std::string&	getType() const;
};
