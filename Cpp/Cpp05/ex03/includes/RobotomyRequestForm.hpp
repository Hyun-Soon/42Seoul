#pragma once

#include "AForm.hpp"
#include <cstdlib>
#include <ctime>

class RobotomyRequestForm : public AForm
{
	private:
		std::string _target;

		RobotomyRequestForm();
	public:
		RobotomyRequestForm(std::string target);
		RobotomyRequestForm(const RobotomyRequestForm& other);
		RobotomyRequestForm& operator= (const RobotomyRequestForm& other);
		virtual ~RobotomyRequestForm();
		virtual void	execute(Bureaucrat const& executor) const;
};