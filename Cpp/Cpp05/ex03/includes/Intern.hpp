#pragma once

#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern
{
	private:
		AForm* createShrubberyCreationForm(std::string target);
		AForm* createRobotomyRequestForm(std::string target);
		AForm* createPresidentialPardonForm(std::string target);

	public:
		AForm* makeForm(std::string name, std::string target);

		class FormDoesNotExist : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};