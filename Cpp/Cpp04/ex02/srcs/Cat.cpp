#include "Cat.hpp"

Cat::Cat()
{
	_type = "Cat";
	_brain = new Brain();
	std::cout << "Cat default constructor called." << std::endl;
}

Cat::Cat(const Cat& other)
{
	_type = other._type;
	_brain = new Brain();
	_brain->setIdeas(other.getBrain()->getIdeas()[0]);
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
	delete _brain;
	std::cout << "Cat destructor called." << std::endl;
}

void	Cat::makeSound() const
{
	std::cout << "Meow~" << std::endl;
}

Brain* Cat::getBrain() const
{
	return (_brain);
}

void	Cat::setBrain(const std::string idea)
{
	_brain->setIdeas(idea);
}

void	Cat::printFirstIdea() const
{
	std::cout << _brain->getIdeas()[0] << std::endl;;
}