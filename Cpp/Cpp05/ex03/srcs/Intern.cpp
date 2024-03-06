#include "Intern.hpp"

AForm *Intern::createShrubberyCreationForm(std::string target)
{
	return new ShrubberyCreationForm(target);
}

AForm *Intern::createRobotomyRequestForm(std::string target)
{
	return new RobotomyRequestForm(target);
}

AForm *Intern::createPresidentialPardonForm(std::string target)
{
	return new PresidentialPardonForm(target);
}

AForm *Intern::makeForm(std::string name, std::string target)
{
	std::string formNames[3] = {"shrubbery creation", "robotomy request", "presidential pardon"};
	AForm* (Intern::*farray[3])(std::string target) = {&Intern::createShrubberyCreationForm, &Intern::createRobotomyRequestForm, &Intern::createPresidentialPardonForm};
	
	for (int i = 0; i < 3; i++)
	{
		if (formNames[i] == name)
		{
			std::cout << "Intern creates " << name << std::endl;
			return (this->*farray[i])(target);
		}
	}
	throw Intern::FormDoesNotExist();
}

const char *Intern::FormDoesNotExist::what() const throw()
{
	return "Error:FormDoesNotExist";
}
