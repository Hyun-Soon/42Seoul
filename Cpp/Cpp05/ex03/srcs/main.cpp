#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main()
{
	try
	{
		Intern phan;
		AForm* shrub = phan.makeForm("shrubbery creation", "hyuim");
		AForm* robot = phan.makeForm("robotomy request", "hyuim");
		AForm* pres = phan.makeForm("presidential pardon", "hyuim");
		//AForm* wrongTest = phan.makeForm("wrong", "hyuim");
		//(void)wrongTest;

		std::cout << "\n------------------------\n" << std::endl;

		Bureaucrat br("br", 150);
		Bureaucrat br1("br1", 140);
		Bureaucrat br2("br2", 1);
		std::cout << br << std::endl;
		std::cout << br1 << std::endl;
		std::cout << br2 << std::endl;
		
		std::cout << "\n------------------------\n" << std::endl;

		br.signForm(*shrub);
		br.signForm(*robot);
		br.signForm(*pres);
		br.executeForm(*shrub);

		std::cout << "\n------------------------\n" << std::endl;

		br1.signForm(*shrub);
		br1.signForm(*robot);
		br1.signForm(*pres);
		br1.executeForm(*shrub);

		std::cout << "\n------------------------\n" << std::endl;

		br2.signForm(*shrub);
		br2.signForm(*robot);
		br2.signForm(*pres);
		br2.executeForm(*shrub);
		br2.executeForm(*robot);
		br2.executeForm(*pres);

		delete shrub;
		delete robot;
		delete pres;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}