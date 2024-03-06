#pragma once

#include <iostream>

class Bureaucrat;

class AForm
{
	private:
		const std::string	_name;
		bool				_sign;
		const int			_gradeForSign;
		const int			_gradeForExec;

	protected:
		enum grade{
			SIGN, EXEC,
		};

	public:
		AForm();
		AForm(int gradeForSign, int gradeForExec);
		AForm(std::string name, int gradeForSign, int gradeForExec);
		AForm(const AForm& other);
		AForm& operator= (const AForm& other);
		virtual ~AForm();
		void				setName(const std::string& name);
		void				setSign(const bool& sign);
		void				setGradeForSign(const int& grade);
		void				setGradeForExec(const int& grade);
		const std::string&	getName() const;
		const bool&			getSign() const;
		const int&			getGradeForSign() const;
		const int&			getGradeForExec() const;
		void				beSigned(const Bureaucrat& br);
		void				checkSign() const;
		void				checkGrade(Bureaucrat const &br, int flag) const;
		void				performIfConditionMet(Bureaucrat const &executor) const;
		virtual void		execute(Bureaucrat const & executor) const = 0;

		class NotSigned : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

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

std::ostream& operator<< (std::ostream& out, const AForm& form);