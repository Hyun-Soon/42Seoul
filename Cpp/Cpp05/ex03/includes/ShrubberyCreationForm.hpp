#pragma once

#include "AForm.hpp"
#include <fstream>

class ShrubberyCreationForm : public AForm
{
	private:
		std::string _target;

		ShrubberyCreationForm();
	public:
		ShrubberyCreationForm(std::string target);
		ShrubberyCreationForm(const ShrubberyCreationForm& other);
		ShrubberyCreationForm& operator= (const ShrubberyCreationForm& other);
		virtual ~ShrubberyCreationForm();
		virtual void	execute(Bureaucrat const& executor) const;
};