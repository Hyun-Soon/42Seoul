#pragma once
#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
	private:
		Brain* _brain;
	public:
		Dog();
		Dog(const Dog& other);
		const Dog& operator= (const Dog& other);
		~Dog();
		virtual void	makeSound() const;
		Brain*			getBrain() const;
		void			setBrain(const std::string idea);
		void			printFirstIdea() const;
};
