#include "PmergeMe.hpp"

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		std::cerr << "Error: Enter numbers." << std::endl;
		return 1;
	}

	PmergeMe test;

	if (test.parseElements(argv + 1, argc - 1) == 1)
	{
		std::cerr << "Error: Wrong input." << std::endl;
		return 1;
	}


	//std::vector
	clock_t start = clock();
	test.sort(VECTOR);
	clock_t end = clock();
	double time = (static_cast<double>(end - start)) / 1000.0;
	test.printUintVec_t();
	std::cout << "\033[1;31m" << "Time to process a range of " << test.getSize() << " elements with std::vector : " << time << " us" << "\033[0;0m" << std::endl;

	//std::deque
	start = clock();
	test.sort(DEQUE);
	end = clock();
	time = (static_cast<double>(end - start)) / 1000.0;
	std::cout << "\033[1;31m" << "Time to process a range of " << test.getSize() << " elements with std::deque : " << time << " us" << "\033[0;0m" << std::endl;
	return 0;
}