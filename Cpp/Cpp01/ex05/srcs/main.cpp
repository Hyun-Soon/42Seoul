#include "Harl.hpp"

int main()
{
	std::string	inp;
	Harl		harl;

	while (getline(std::cin, inp))
	{
		harl.complain(inp);
	}
	return (0);
}