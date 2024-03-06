#pragma once

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
	private:
		std::string _target;

		PresidentialPardonForm();
	public:
		PresidentialPardonForm(std::string target);
		PresidentialPardonForm(const PresidentialPardonForm& other);
		PresidentialPardonForm& operator= (const PresidentialPardonForm& other);
		virtual ~PresidentialPardonForm();
		virtual void	execute(Bureaucrat const& executor) const;
};