#pragma once

#include "AForm.hpp"
#include <iostream>
#include <exception>

class Bureaucrat
{
	private:
		const std::string	_name;
		int					_grade;
	public:
		Bureaucrat();
		Bureaucrat(const int grade);
		Bureaucrat(const std::string name, const int grade);
		Bureaucrat(const Bureaucrat& other);
		const Bureaucrat& operator=(const Bureaucrat& other);
		~Bureaucrat();
		const std::string&	getName() const;
		const int&			getGrade() const;
		void				promote();
		void				demote();
		void 				signForm(AForm& form);

		class GradeTooHighException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class GradeTooLowException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

std::ostream& operator<< (std::ostream& out, const Bureaucrat& br);