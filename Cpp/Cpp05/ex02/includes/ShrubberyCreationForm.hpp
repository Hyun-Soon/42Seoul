#pragma once

#include "AForm.hpp"

class ShrubberyCreationForm : public AForm
{
	public:
		ShrubberyCreationForm();
		ShrubberyCreationForm(int gradeForSign, int gradeForExec);
		ShrubberyCreationForm(std::string name, int gradeForSign, int gradeForExec);
		ShrubberyCreationForm(const ShrubberyCreationForm& other);
		ShrubberyCreationForm& operator= (const ShrubberyCreationForm& other);
		virtual ~ShrubberyCreationForm();
		virtual void	execute(Bureaucrat const& executor) const;
};