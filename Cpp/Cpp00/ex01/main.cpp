#include <iomanip>
#include "contact.hpp"
#include "phonebook.hpp"


void	add()
{
	
}

int	get_input()
{
	std::string	inp;

	std::cin >> inp;
	if (inp == "ADD")
		add();
	else if (inp == "SEARCH")
		search();
	else if (inp == "EXIT")
		return (0);
	return (1);
}

int main()
{
	std::cout << std::setprecision(10);
	while (get_input())
		;

	return (0);
}