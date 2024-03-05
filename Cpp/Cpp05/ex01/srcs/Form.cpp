#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : _name("default"), _sign(false), _gradeForSign(150), _gradeForExec(150) {}

Form::Form(int gradeForSign, int gradeForExec) : _name("default"), _gradeForSign(gradeForSign), _gradeForExec(gradeForExec)
{
	if (gradeForSign < 1 || gradeForExec < 1)
		throw GradeTooHighException();
	else if (gradeForSign > 150 || gradeForExec > 150)
		throw GradeTooLowException();
}

Form::Form(std::string name, int gradeForSign, int gradeForExec) : _name(name), _gradeForSign(gradeForSign), _gradeForExec(gradeForExec)
{
	if (gradeForSign < 1 || gradeForExec < 1)
		throw GradeTooHighException();
	else if (gradeForSign > 150 || gradeForExec > 150)
		throw GradeTooLowException();
}

Form::Form(const Form &other) : _name(other._name), _sign(other._sign), _gradeForSign(other._gradeForSign), _gradeForExec(other._gradeForExec) {}

Form &Form::operator= (const Form &other)
{
	if (this != &other)
	{
		const_cast<std::string&>(_name) = other._name;
		_sign = other._sign;
		const_cast<int&>(_gradeForSign) = other._gradeForSign;
		const_cast<int&>(_gradeForExec) = other._gradeForExec;
	}
	return *this;
}

Form::~Form() {}

const std::string& Form::getName() const
{
	return _name;
}

const bool& Form::getSign() const
{
	return _sign;
}

const int& Form::getGradeForSign() const
{
	return _gradeForSign;
}

const int& Form::getGradeForExec() const
{
	return _gradeForExec;
}

void	Form::beSigned(const Bureaucrat& br)
{
	if (br.getGrade() > _gradeForSign)
		throw GradeTooLowException();
	_sign = true;
}

const char* Form::GradeTooHighException::what() const throw()
{
	return "Error:GradeTooHigh";
}

const char* Form::GradeTooLowException::what() const throw()
{
	return "Error:GradeTooLow";
}

std::ostream& operator<< (std::ostream &out, const Form &form)
{
	out << "Form name : " << form.getName() << " | sign : " << (form.getSign() ? "signed" : "unsigned") << " | grade for sign : " << form.getGradeForSign() << " | grade for exec : " << form.getGradeForExec();
	return out;
}
