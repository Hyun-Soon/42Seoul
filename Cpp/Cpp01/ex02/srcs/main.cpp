#include <string>
#include <iostream>

int main()
{
	std::string	brain("HI THIS IS BRAIN");
	std::string	*stringPTR = &brain;
	std::string	&stringREF = brain;

	std::cout << "memory addr of string var : " << &brain << std::endl;
	std::cout << "memory addr held by stringPTR : " << stringPTR << std::endl;
	std::cout << "memory addr held by stringREF : " << &stringREF  << "\n" << std::endl;

	std::cout << "value of string var : " << brain << std::endl;
	std::cout << "value pointed to by stringPTR : " << *stringPTR << std::endl;
	std::cout << "value pointed to by stringREF : " << stringREF << std::endl;
	
	return 0;
}