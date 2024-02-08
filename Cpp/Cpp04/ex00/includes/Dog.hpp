#pragma once
#include "Animal.hpp"

class Dog : public Animal
{
	public:
		Dog();
		Dog(const Dog& other);
		const Dog& operator= (const Dog& other);
		~Dog();
		virtual void	makeSound() const;
};
