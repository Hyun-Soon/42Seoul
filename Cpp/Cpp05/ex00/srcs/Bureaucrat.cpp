#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : _grade(150) {}

Bureaucrat::Bureaucrat(const int grade)
{
	if (grade < 1 || grade > 150)
		throw 
}

Bureaucrat::Bureaucrat(const Bureaucrat &other)
{
}

Bureaucrat::~Bureaucrat()
{
}
