#pragma once
#include "Animal.hpp"

class Cat : public Animal
{
	public:
		Cat();
		Cat(const Cat& other);
		const Cat& operator= (const Cat& other);
		~Cat();
		virtual void	makeSound() const;
};

