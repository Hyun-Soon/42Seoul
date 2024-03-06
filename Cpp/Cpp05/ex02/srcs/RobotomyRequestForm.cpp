#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() : AForm("RobotomyRequestForm", 72, 45) {}

RobotomyRequestForm::RobotomyRequestForm(std::string target) : AForm("RobotomyRequestForm", 72, 45), _target(target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other) : AForm(other.getName(), other.getGradeForSign(), other.getGradeForExec()) {}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other)
{
	if (this != &other)
	{
		this->setName(other.getName());
		this->setSign(other.getSign());
		this->setGradeForSign(other.getGradeForSign());
		this->setGradeForExec(other.getGradeForExec());
	}
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
	(void)executor;
	srand(uint32_t(time(NULL)));
	if (rand() % 2 == 0)
		std::cout << _target << " has been robotomized." << std::endl;
	else
		std::cout << "Robotomy failed." << std::endl;
}