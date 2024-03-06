#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : _name("default"), _sign(false), _gradeForSign(150), _gradeForExec(150) {}

AForm::AForm(int gradeForSign, int gradeForExec) : _name("default"), _gradeForSign(gradeForSign), _gradeForExec(gradeForExec)
{
	if (gradeForSign < 1 || gradeForExec < 1)
		throw GradeTooHighException();
	else if (gradeForSign > 150 || gradeForExec > 150)
		throw GradeTooLowException();
}

AForm::AForm(std::string name, int gradeForSign, int gradeForExec) : _name(name), _gradeForSign(gradeForSign), _gradeForExec(gradeForExec)
{
	if (gradeForSign < 1 || gradeForExec < 1)
		throw GradeTooHighException();
	else if (gradeForSign > 150 || gradeForExec > 150)
		throw GradeTooLowException();
}

AForm::AForm(const AForm &other) : _name(other._name), _sign(other._sign), _gradeForSign(other._gradeForSign), _gradeForExec(other._gradeForExec) {}

AForm &AForm::operator= (const AForm &other)
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

AForm::~AForm() {}

void AForm::setName(const std::string &name)
{
	const_cast<std::string&>(_name) = name;
}

void AForm::setSign(const bool &sign)
{
	_sign = sign;
}

void AForm::setGradeForSign(const int &grade)
{
	if (grade < 1)
		throw AForm::GradeTooHighException();
	else if (grade > 150)
		throw AForm::GradeTooLowException();
	const_cast<int&>(_gradeForSign) = grade;
}

void AForm::setGradeForExec(const int &grade)
{
	if (grade < 1)
		throw AForm::GradeTooHighException();
	else if (grade > 150)
		throw AForm::GradeTooLowException();
	const_cast<int&>(_gradeForExec) = grade;
}

const std::string& AForm::getName() const
{
	return _name;
}

const bool& AForm::getSign() const
{
	return _sign;
}

const int& AForm::getGradeForSign() const
{
	return _gradeForSign;
}

const int& AForm::getGradeForExec() const
{
	return _gradeForExec;
}

void	AForm::beSigned(const Bureaucrat& br)
{
	checkGrade(br, SIGN);
	_sign = true;
}

void	AForm::checkSign() const
{
	if (_sign == false)
		throw AForm::NotSigned();
}

void	AForm::checkGrade(Bureaucrat const &br, int flag) const
{
	if (flag == SIGN && br.getGrade() > this->getGradeForSign())
		throw AForm::GradeTooLowException();
	if (flag == EXEC && br.getGrade() > this->getGradeForExec())
		throw AForm::GradeTooLowException();
}

void AForm::performIfConditionMet(Bureaucrat const &executor) const
{
	checkSign();
	checkGrade(executor, EXEC);
	execute(executor);
}

const char *AForm::NotSigned::what() const throw()
{
	return "Error:NotSigned";
}

const char* AForm::GradeTooHighException::what() const throw()
{
	return "Error:GradeTooHigh";
}

const char* AForm::GradeTooLowException::what() const throw()
{
	return "Error:GradeTooLow";
}

std::ostream& operator<< (std::ostream &out, const AForm &form)
{
	out << "AForm name : " << form.getName() << " | sign : " << (form.getSign() ? "signed" : "unsigned") << " | grade for sign : " << form.getGradeForSign() << " | grade for exec : " << form.getGradeForExec();
	return out;
}
