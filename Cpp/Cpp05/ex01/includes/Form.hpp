#pragma once

#include <iostream>

class Bureaucrat;

class Form
{
	private:
		const std::string	_name;
		bool				_sign;
		const int			_gradeForSign;
		const int			_gradeForExec;
	public:
		Form();
		Form(int gradeForSign, int gradeForExec);
		Form(std::string name, int gradeForSign, int gradeForExec);
		Form(const Form& other);
		Form& operator= (const Form& other);
		~Form();
		const std::string&	getName() const;
		const bool&			getSign() const;
		const int&			getGradeForSign() const;
		const int&			getGradeForExec() const;
		void				beSigned(const Bureaucrat& br);

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

std::ostream& operator<< (std::ostream& out, const Form& form);