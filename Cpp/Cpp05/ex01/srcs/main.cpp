#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	try
	{
		//Bureaucrat br0("br0", 160);
		Bureaucrat br1("br1", 150);
		Bureaucrat br2("br2", 3);

		Form a("a", 149, 149);
		Form b("b", 10, 10);

		std::cout << a << std::endl;
		br1.signForm(a);
		br1.promote();
		br1.signForm(a);
		std::cout << a << std::endl;

		std::cout << std::endl;
		
		std::cout << b << std::endl;
		br2.signForm(b);
		std::cout << b << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}