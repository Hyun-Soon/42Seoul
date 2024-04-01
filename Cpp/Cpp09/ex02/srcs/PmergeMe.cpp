#include "PmergeMe.hpp"

//debug
void printVector(std::string msg, std::vector<unsigned int>& v)
{
	std::cout << msg << " : ";
	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << ' ';
	std::cout << std::endl;	
}

PmergeMe::PmergeMe() {}

//TODO :: implement here
//PmergeMe::PmergeMe(const PmergeMe &other)
//{}

//PmergeMe PmergeMe::operator=(const PmergeMe &other)
//{}

PmergeMe::~PmergeMe() {}

int PmergeMe::parseElements(char** elements, size_t elemSize)
{
	double temp;

	for (size_t i = 0; i < elemSize; i++)
	{
		temp = strtod(elements[i], NULL);
		if (temp <= 0.0 || temp != temp || temp > INT_MAX)
			return 1;
		_elements.push_back(temp);
	}
	return 0;
}

void PmergeMe::makeChains(size_t elemSize)
{
	for (size_t i = 0; i < elemSize / 2; i++)
	{
		_mainChain.push_back(_elements[i]);
		_pendingChain.push_back(_elements[i + elemSize / 2]);
	}
	if (elemSize % 2 == 1)
		_pendingChain.push_back(_elements.back());
}

void PmergeMe::mergeInsertion(char** elements, size_t elemSize)
{
	if (parseElements(elements, elemSize) == 1)
	{
		std::cerr << "Error: Wrong input." << std::endl;
		return ;
	}

	makeChains(elemSize);

	//debug
	//printVector("mainChain", _mainChain);
	//printVector("pendingChain", _pendingChain);

}

