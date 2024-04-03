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

int PmergeMe::sort(char** elements, size_t elemSize)
{
	if (parseElements(elements, elemSize) == 1)
		return 1;

	splitByValue();
	mergeInsertion(_sorted);

	return 0;
}

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

void PmergeMe::splitByValue()
{
	chain_t temp;
	size_t halfSize = _unsorted.size() / 2;
	for (size_t i = 0; i < halfSize; i++)
	{
		_sorted.push_back(std::max(_unsorted[i], _unsorted[i + halfSize]));
		temp.push_back(std::min(_unsorted[i], _unsorted[i + halfSize]));
	}
	if (_unsorted.size() % 2 == 1)
		temp.push_back(_unsorted.back());

	for (size_t i = 0; i < temp.size(); i++)
		_sorted.push_back(temp[i]);
}


size_t PmergeMe::getInsertSize(const size_t& mainSize, const size_t& pendingSize)
{
	size_t jacobsthal = 0;
	size_t ret;
	int n = 1;

	while (jacobsthal <= mainSize)
	{
		jacobsthal = (pow(2, n) - pow(-1, n)) / 3;
		++n;
	}
	//debug
	//std::cout << "inside jacob : " << jacobsthal << std::endl;
	ret = jacobsthal - mainSize;
	return (ret <= pendingSize ? ret : pendingSize);
}

int PmergeMe::binarySearch(chain_t& mainChain, const unsigned int& value)
{
	int left = 0;
	int right = mainChain.size() - 1;
	int mid;

	while (left <= right)
	{
		mid = (left + right) / 2;
		if (value > mainChain[mid])
			left = mid + 1;
		else
			right = mid - 1;
		//else
		//	return mid;
	}
	return left;
}

void PmergeMe::binaryInsertion(chain_t& mainChain, const unsigned int& value)
{
	int insertPos = binarySearch(mainChain, value);
	mainChain.insert(mainChain.begin() + insertPos, value);
}

void PmergeMe::mergeInsertion(chain_t& orgMainChain, chain_t& orgPendingChain)
{ //TODO :: swap pendingChain too
	//TODO :: modify insertSize
	chain_t mainChain;
	chain_t pendingChain;
	int insertSize;
	int offset;

	if (orgMainChain.size() == 1)
		return ;
	makeChains(orgMainChain, mainChain, pendingChain);
	mergeInsertion(mainChain, pendingChain);

	//debug
	std::cout << std::endl;
	//printVector("orgMainChain", orgMainChain);
	printVector("mainChain", mainChain);
	printVector("pendingChain", pendingChain);

	while (pendingChain.size())
	{
		insertSize = getInsertSize(mainChain.size(), pendingChain.size());
		offset = insertSize - 1;

		//deubg
		//std::cout << "insertSize : " << insertSize << std::endl;

		for (; offset >= 0; offset--)
			binaryInsertion(mainChain, pendingChain[offset]);

		pendingChain.erase(pendingChain.begin(), pendingChain.begin() + insertSize);

		printVector("mainChain here", mainChain);
		printVector("pendingChain here", pendingChain);
	}

	orgMainChain = mainChain;
}