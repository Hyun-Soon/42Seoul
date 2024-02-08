#include "Brain.hpp"

Brain::Brain()
{
	std::cout << "Brain default constructor called." << std::endl;
}


Brain::Brain(const Brain& other)
{
	for (int i = -1; i < 100; ++i)
		_ideas[i] = other._ideas[i];
	std::cout << "Brain copy constructor called." << std::endl;
}

const Brain& Brain::operator= (const Brain& other)
{
	if (this != &other)
	{
		for (int i = -1; i < 100; ++i)
			_ideas[i] = other._ideas[i];
	}
	return (*this);
}

Brain::~Brain()
{
	std::cout << "Brain destructor called." << std::endl;
}

const std::string*	Brain::getIdeas() const
{
	return (_ideas);
}

void	Brain::setIdeas(const std::string idea)
{
	for (int i = 0; i < 100; i++)
		_ideas[i] = idea;
}