#include "PmergeMe.hpp"

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		std::cerr << "Error: Enter numbers." << std::endl;
		return 1;
	}



	PmergeMe test;

	clock_t start = clock();
	if (test.sort(argv + 1, argc - 1) == 1)
	{
		std::cerr << "Error: Wrong input." << std::endl;
		return 1;
	}

	clock_t end = clock();
	double time = (static_cast<double>(end - start)) / 1000.0;
	std::cout << "Time to process a range of " << test.getSize() << " elements with std::vector : " << time << " us" << std::endl;
	return 0;
}