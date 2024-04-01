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
		_unsorted.push_back(temp);
	}
	return 0;
}

void PmergeMe::makeChains(const chain_t& orgChain, chain_t& mainChain, chain_t& pendingChain)
{
	for (size_t i = 0; i < orgChain.size() / 2; i++)
	{
		mainChain.push_back(orgChain[i]);
		pendingChain.push_back(orgChain[i + orgChain.size() / 2]);
	}
	if (orgChain.size() % 2 == 1)
		pendingChain.push_back(orgChain.back());
}

int PmergeMe::sort(char** elements, size_t elemSize)
{
	if (parseElements(elements, elemSize) == 1)
	{
		std::cerr << "Error: Wrong input." << std::endl;
		return 1;
	}

	_sorted = _unsorted;
	mergeInsertion(_sorted);

	return 0;
}


void PmergeMe::mergeInsertion(chain_t& orgChain)
{
	chain_t mainChain;
	chain_t pendingChain;

	if (orgChain.size() == 1)
		return ;
	makeChains(orgChain, mainChain, pendingChain);
	mergeInsertion(mainChain);


	//debug
	printVector("mainChain", mainChain);
	printVector("pendingChain", pendingChain);
}