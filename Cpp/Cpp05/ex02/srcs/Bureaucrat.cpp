#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : _name("default"), _grade(150) {}

Bureaucrat::Bureaucrat(const int grade) : _name("default")
{
	if (grade < 1)
		throw GradeTooHighException();
	else if (grade > 150)
		throw GradeTooLowException();
	_grade = grade;
}

Bureaucrat::Bureaucrat(const std::string name, const int grade) : _name(name)
{
	if (grade < 1)
		throw GradeTooHighException();
	else if (grade > 150)
		throw GradeTooLowException();
	_grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat &other) : _name(other._name), _grade(other._grade) {}

const Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other)
{
	if (this != &other)
	{
		const_cast<std::string&>(_name) = other._name;
		this->_grade = other._grade;
	}
	return (*this);
}

Bureaucrat::~Bureaucrat() {}

const std::string& Bureaucrat::getName() const
{
	return _name;
}

const int& Bureaucrat::getGrade() const
{
	return _grade;
}

void Bureaucrat::promote()
{
	if (_grade == 1)
		throw GradeTooHighException();
	--_grade;
	std::cout << _name << " promoted to " << _grade << "." << std::endl;
}

void Bureaucrat::demote()
{
	if (_grade == 150)
		throw GradeTooLowException();
	++_grade;
	std::cout << _name << " demoted to " << _grade << "." << std::endl;
}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Error:GradeTooHigh";
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Error:GradeTooLow";
}

void Bureaucrat::signForm(AForm& form)
{
	try
	{
		form.beSigned(*this);
		std::cout << _name << " signed " << form.getName() << "." << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << _name << " couldn't sign " << form.getName() << " because " << e.what() << " occured." << std::endl;
	}
}

std::ostream& operator<< (std::ostream& out, const Bureaucrat& br)
{
	out << br.getName() << ", bureaucrat grade " << br.getGrade() << "." << std::endl;
	return out;
}

