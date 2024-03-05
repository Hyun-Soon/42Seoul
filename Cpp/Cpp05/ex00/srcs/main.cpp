#include "Bureaucrat.hpp"

int main()
{
	try
	{	
		Bureaucrat br1;
		Bureaucrat br2("br2", 3);
		Bureaucrat br3(br1);

		std::cout << br1 << std::endl;
		std::cout << br2 << std::endl;
		std::cout << br3 << std::endl;

		//br1.demote();
		br2.promote();
		br2.promote();
		br2.promote();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;;
	}
	

	return 0;
}