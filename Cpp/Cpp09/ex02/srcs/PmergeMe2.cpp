#include "PmergeMe2.hpp"

//debug
void printPChain_t(std::string msg, pChain_t& v)
{
	std::cout << msg << " : ";
	for (size_t i = 0; i < v.size(); i++)
		std::cout << "{" << v[i].first << ", " << v[i].second << "} ";
	std::cout << std::endl;	
}

void printChain_t(std::string msg, chain_t v)
{
	std::cout << msg << " : ";
	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << " ";
	std::cout << std::endl;	
}

PmergeMe::PmergeMe() : _remainder(0) {}

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
	if (_remainder)
		_sorted.push_back(std::pair<unsigned int, unsigned int>(0, _remainder));
	//printPChain_t("first sort result", _sorted);	
	binaryInsertionPendings(_sorted);

	std::cout << std::endl;
	std::cout << "Sort Result : ";
	size_t end = (_remainder ? _sorted.size() - 1 : _sorted.size());
	for (size_t i = 0; i < end; i++)
		if (_sorted[i].first != 0)
			std::cout << _sorted[i].first << " ";
	std::cout << std::endl;
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

void PmergeMe::splitByValue()
{
	size_t halfSize = _unsorted.size() / 2;
	for (size_t i = 0; i < halfSize; i++)
	{
		unsigned int large = std::max(_unsorted[i], _unsorted[i + halfSize]);
		unsigned int small = std::min(_unsorted[i], _unsorted[i + halfSize]);

		_sorted.push_back(std::pair<unsigned int, unsigned int>(large, small));
	}
	if (_unsorted.size() % 2 == 1)
		_remainder = _unsorted.back();
}

void PmergeMe::makeChains(const pChain_t& orgChain, pChain_t& mainChain, pChain_t& pendingChain)
{
	size_t halfSize = orgChain.size() / 2;
	for (size_t i = 0; i < halfSize; i++)
	{
		pUintUint_t large = (orgChain[i].first >= orgChain[i + halfSize].first ? orgChain[i] : orgChain[i + halfSize]);
		pUintUint_t small = (orgChain[i].first >= orgChain[i + halfSize].first ? orgChain[i + halfSize] : orgChain[i]);

		mainChain.push_back(large);
		pendingChain.push_back(small);
	}
	if (orgChain.size() % 2 == 1)
		pendingChain.push_back(orgChain.back());
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

int PmergeMe::binarySearch(pChain_t& mainChain, const unsigned int& value, const int& rightLimit)
{
	int left = 0;
	int right = rightLimit;
	int mid;

	//std::cout << "rightlimit : " << rightLimit << std::endl;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (value > mainChain[mid].first)
			left = mid + 1;
		else
			right = mid - 1;
	}
	//std::cout << "ret : " << left << std::endl;
	return left;
}

void PmergeMe::binaryInsertion(pChain_t& mainChain, pChain_t& pendingChain, const int& offset, const int& rightLimit)
{
	int insertPos = binarySearch(mainChain, pendingChain[offset].first, rightLimit);
	mainChain.insert(mainChain.begin() + insertPos, pendingChain[offset]);
	//printPChain_t("insertionING : ", mainChain);
}

void PmergeMe::binaryInsertionPendings(pChain_t& orgChain)
{
	//TODO :: apply Jacobsthal
	pChain_t temp = orgChain;
	int repeat = orgChain.size() - 1;
	for (; repeat >= 0; repeat--)
	{
		int right = (_remainder ? temp.size() - 2 : temp.size() - 1);
		//std::cout << "repeat : " << repeat << std::endl;
		int left = 0;
		int mid;

		//std::cout << "rightlimit : " << rightLimit << std::endl;
		while (left <= right)
		{
			mid = (left + right) / 2;
			//std::cout << "temp[repeat] : " << temp[repeat].second << std::endl;
			if (temp[repeat].second > orgChain[mid].first)
				left = mid + 1;
			else
				right = mid - 1;
		}
		orgChain.insert(orgChain.begin() + left, std::pair<unsigned int, unsigned int>(temp[repeat].second, 0));
		//printPChain_t("ret : ", orgChain);
	}
}

void PmergeMe::mergeInsertion(pChain_t& orgChain)
{
	//TODO :: 1. swap pendingChain too
	//TODO :: 2. modify getInsertSize
	// remain pendings = present size - half size;
	pChain_t mainChain;
	pChain_t pendingChain;

	if (orgChain.size() == 1)
		return ;
	makeChains(orgChain, mainChain, pendingChain);
	mergeInsertion(mainChain);

	//debug
	//std::cout << std::endl;
	//printPChain_t("orgChain", orgChain);
	//printPChain_t("mainChain", mainChain);
	//printPChain_t("pendingChain", pendingChain);

	while (pendingChain.size())
	{
		const int rightLimit = mainChain.size() - 1; //TODO::is it correct??? ㅇㅑ코ㅂ스탈 수열이 필요없다고 한 이유가 혹시 자기 메인체인 앞에값까지만 비교하면 어차피 비교횟수 최대 n이 보장되기 때문인가?
		int insertSize = getInsertSize(mainChain.size(), pendingChain.size());
		int offset = insertSize - 1;

		//deubg
		//std::cout << "insertSize : " << insertSize << std::endl;
		for (; offset >= 0; offset--)
			binaryInsertion(mainChain, pendingChain, offset, rightLimit);

		pendingChain.erase(pendingChain.begin(), pendingChain.begin() + insertSize);

		//printPChain_t("mainChain here", mainChain);
		//printPChain_t("pendingChain here", pendingChain);
	}

	orgChain = mainChain;
}