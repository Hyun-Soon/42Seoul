#include "PmergeMe.hpp"

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		std::cerr << "Error: Enter numbers." << std::endl;
		return 1;
	}

	PmergeMe test;

	test.mergeInsertion(argv + 1, argc - 1);
	return 0;
}