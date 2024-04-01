#include <vector>
#include <iostream>
#include "easyfind.hpp"

int main()
{
	std::vector<int> v;
	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	std::vector<int>::iterator it1 = easyfind(v, 0);
	if (it1 != v.end())
		std::cout << *it1 << std::endl;
	else
		std::cout << "Not found." << std::endl;

	std::vector<int>::iterator it2 = easyfind(v, 5);
	if (it2 != v.end())
		std::cout << *it2 << std::endl;
	else
		std::cout << "Not found." << std::endl;

	return 0;
}