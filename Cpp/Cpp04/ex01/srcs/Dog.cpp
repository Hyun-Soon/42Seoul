#include "Dog.hpp"

Dog::Dog()
{
	_type = "Dog";
	_brain = new Brain();
	std::cout << "Dog default constructor called." << std::endl;
}

Dog::Dog(const Dog& other)
{
	_type = other._type;
	_brain = new Brain();
	_brain->setIdeas(other.getBrain()->getIdeas()[0]);
	std::cout << "Dog copy constructor called." << std::endl;
}

const Dog& Dog::operator= (const Dog& other)
{
	if (this != &other)
		_type = other._type;

	return (*this);
}

Dog::~Dog()
{
	delete _brain;
	std::cout << "Dog destructor called." << std::endl;
}

void	Dog::makeSound() const
{
	std::cout << "Woof Woof!" << std::endl;
}

Brain* Dog::getBrain() const
{
	return (_brain);
}

void	Dog::setBrain(const std::string idea)
{
	_brain->setIdeas(idea);
}

void	Dog::printFirstIdea() const
{
	std::cout << _brain->getIdeas()[0] << std::endl;;
}