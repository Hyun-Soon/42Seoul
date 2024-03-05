#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm", 145, 137) {}

ShrubberyCreationForm::ShrubberyCreationForm(int gradeForSign, int gradeForExec) : AForm("ShrubberyCreationForm", gradeForSign, gradeForExec) {}

ShrubberyCreationForm::ShrubberyCreationForm(std::string name, int gradeForSign, int gradeForExec) : AForm(name, gradeForSign, gradeForExec) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other) : AForm(other.getName(), other.getGradeForSign(), other.getGradeForExec()) {}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{
	if (this != &other)
	{
		
	}
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	return ;
}