#include "iter.hpp"

int main()
{
	char arrChar[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
	int arrInt[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	float arrFloat[10] = {0.1f, 1.1f, 2.1f, 3.1f, 4.1f, 5.1f, 6.1f, 7.1f, 8.1f, 9.1f};


	iter(arrChar, 10, printPlusOne<char>);
	std::cout << std::endl;
	iter(arrChar, 10, printMinusOne<char>);
	std::cout << std::endl;
	iter(arrInt, 10, printPlusOne<int>);
	std::cout << std::endl;
	iter(arrInt, 10, printMinusOne<int>);
	std::cout << std::endl;
	iter(arrFloat, 10, printPlusOne<float>);
	std::cout << std::endl;
	iter(arrFloat, 10, printMinusOne<float>);
	std::cout << std::endl;

	return 0;
}
