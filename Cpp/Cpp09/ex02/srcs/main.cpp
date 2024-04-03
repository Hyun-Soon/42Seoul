#include "PmergeMe2.hpp"

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		std::cerr << "Error: Enter numbers." << std::endl;
		return 1;
	}

	PmergeMe test;

	if (test.sort(argv + 1, argc - 1) == 1)
	{
		std::cerr << "Error: Wrong input." << std::endl;
		return 1;
	}

	return 0;
}