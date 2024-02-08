#include "Phonebook.hpp"
#include <cstdio>

int	get_input(Phonebook	&pb)
{
	std::string	inp;

	std::cout << "Enter Command : ";
	if (getline(std::cin, inp).fail())
	{
		std::cin.clear();
		clearerr(stdin);
		std::cout << std::endl;
		std::cout << "\nWrong input.\n";
		return (1);
	}
	
	if (inp == "ADD")
		pb.add();
	else if (inp == "SEARCH")
		pb.search();
	else if (inp == "EXIT")
		return (0);
	else
		std::cout << "\nWrong Command.\n";
	return (1);
}

int main()
{
	Phonebook	pb;

	while (get_input(pb))
		;
	return (0);
}
