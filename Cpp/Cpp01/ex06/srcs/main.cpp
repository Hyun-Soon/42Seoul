#include "Harl.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Wrong input." << std::endl;
		return (1);
	}

	Harl	harl;
	std::string	level(argv[1]);

	harl.filter(level);

	return (0);
}