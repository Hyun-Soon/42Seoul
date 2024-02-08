#pragma once

#include <iostream>
#include <exception>

class Bureaucrat
{
	private:
		const std::string	_name;
		int					_grade;
	public:
		Bureaucrat();
		Bureaucrat(const Bureaucrat& other);
		const Bureaucrat& operator=(const Bureaucrat& other) const;
		~Bureaucrat();

		//TODO :: implement exception class
		class GradeTooHighException : public std::exception
		{
			GradeTooHighException();
			GradeTooHighException(const GradeTooHighException& other);
			const GradeTooHighException& operator= (const GradeTooHighException& other);
			~GradeTooHighException();
			virtual const char* what() const throw();
		};
};