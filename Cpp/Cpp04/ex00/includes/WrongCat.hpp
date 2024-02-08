#pragma once
#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal
{
	public:
		WrongCat();
		WrongCat(const WrongCat& other);
		const WrongCat& operator= (const WrongCat& other);
		~WrongCat();
		void	makeSound() const;
};

