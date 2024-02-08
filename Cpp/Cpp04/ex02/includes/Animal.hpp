#pragma once

#include "Brain.hpp"
#include <iostream>

class Animal
{
	protected:
		std::string	_type;
	public:
		virtual ~Animal();
		virtual void	makeSound() const = 0;
		const std::string& getType() const;
};
