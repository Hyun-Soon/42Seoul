#pragma once
#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
	private:
		Brain* _brain;
	public:
		Cat();
		Cat(const Cat& other);
		const Cat& operator= (const Cat& other);
		~Cat();
		virtual void	makeSound() const;
		Brain*	getBrain() const;
		void		setBrain(const std::string idea);
		void	printFirstIdea() const;
};

