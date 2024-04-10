#include "PmergeMeFinal.hpp"

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		std::cerr << "Error: Enter numbers." << std::endl;
		return 1;
	}

	PmergeMe test;

	//chain_t v;
	//v.push_back(2);
	//v.push_back(1);
	//chain_t f;
	//f.push_back(2);

	//if (v > f)
	//	std::cout << "1" << std::endl;
	//else
	//	std::cout << "2" << std::endl;


	if (test.sort(argv + 1, argc - 1) == 1)
	{
		std::cerr << "Error: Wrong input." << std::endl;
		return 1;
	}

	return 0;
}