#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) : _unsortedV(other._unsortedV), _sortedV(other._sortedV), _unsortedD(other._unsortedD), _sortedD(other._sortedD), _maxLevel(other._maxLevel)
{}

PmergeMe PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		_unsortedV = other._unsortedV;
		_sortedV = other._sortedV;
		_unsortedD = other._unsortedD;
		_sortedD = other._sortedD;
		_maxLevel = other._maxLevel;
	}
	return *this;
}
PmergeMe::~PmergeMe() {}

//std::vector
void PmergeMe::printUintVec_t()
{
	std::cout << "Before	: ";
	for (size_t i = 0; i < _unsortedV.size(); i++)
		std::cout << _unsortedV[i] << " ";
	std::cout << std::endl;

	std::cout << "After	: ";
	for (size_t i = 0; i < _sortedV.size(); i++)
		std::cout << _sortedV[i] << " ";
	std::cout << std::endl;
}

void printChainsHead(std::string msg, chainsV_t c)
{
	std::cout << msg << " : ";
	for (size_t i = 0; i < c.size(); i++)
		std::cout << c[i][0] << " ";
	std::cout << std::endl;	
}


void PmergeMe::swapChain(uintVec_t& orgChain, size_t idx, size_t cmpOffset)
{
	unsigned int temp;

	for (size_t i = 0; i < cmpOffset; i++)
	{
		temp = orgChain[idx];
		orgChain[idx] = orgChain[idx + cmpOffset];
		orgChain[idx + cmpOffset] = temp;
		++idx;
	}
}

int PmergeMe::getMaxLevel()
{
	size_t ret = 1;
	int cnt = 0;
	while (ret <= _unsortedV.size())
	{
		ret *= 2;
		++cnt;
	}
	return cnt;
}

int PmergeMe::getSize()
{
	return _sortedV.size();
}

void PmergeMe::sort(int type)
{
	_maxLevel = getMaxLevel();

	if (type == VECTOR)
	{
		_sortedV = _unsortedV;
		mergeInsertion(_sortedV, _sortedV.size(), 1);
	}

	if (type == DEQUE)
	{
		_sortedD = _unsortedD;
		mergeInsertion(_sortedD, _sortedD.size(), 1);
	}
}

int PmergeMe::parseElements(char** elements, size_t elemSize)
{
	double temp;

	for (size_t i = 0; i < elemSize; i++)
	{
		temp = strtod(elements[i], NULL);
		if (temp <= 0.0 || temp != temp || temp > INT_MAX)
			return 1;
		_unsortedV.push_back(temp);
		_unsortedD.push_back(temp);
	}
	return 0;
}

chainsV_t PmergeMe::binaryInsertion(uintVec_t& orgChain, size_t truncatedChainSize, size_t chainSize)
{
	chainsV_t mainChain;
	chainsV_t pendingChain;
	size_t totalChainCnt = truncatedChainSize / chainSize;
	size_t remainFlag = totalChainCnt % 2;

	for (size_t i = 0; i < totalChainCnt; i++)
	{
		uintVec_t temp;
		for (size_t j = 0; j < chainSize; j++)
			temp.push_back(orgChain[i * chainSize + j]);
		if (i % 2 == 1 || (remainFlag && i == totalChainCnt - 1))
			pendingChain.push_back(temp);
		else
			mainChain.push_back(temp);
	}
	
	//printChainsHead("mainChain", mainChain);
	//printChainsHead("pendingChain", pendingChain);

	int remainIdx = pendingChain.size() - 1;

	int beforeJacobsthalIdx = -1;
	int jacobsthalIdx;
	int n = 1;
	while (mainChain.size() != totalChainCnt)
	{
		jacobsthalIdx = getJacobsthal(n, pendingChain.size()) - 1;
		for (int idx = jacobsthalIdx; idx > beforeJacobsthalIdx; idx--)
		{
			int rightLimit;
			if (remainFlag && idx == remainIdx)
				rightLimit = mainChain.size() - 1;
			else
				rightLimit = beforeJacobsthalIdx + jacobsthalIdx;
			int pos = binarySearch(mainChain, pendingChain[idx][0], rightLimit);
			mainChain.insert(mainChain.begin() + pos, pendingChain[idx]);
		}
		beforeJacobsthalIdx = jacobsthalIdx;
		++n;
	}

	//printChainsHead("insertion result", mainChain);
	return mainChain;
}

 int PmergeMe::binarySearch(chainsV_t& mainChain, const unsigned int value, int rightLimit)
 {
 	int left = 0;
 	int right = rightLimit;
 	int mid;

 	while (left <= right)
 	{
 		mid = (left + right) / 2;
		if (value == mainChain[mid][0])
			return mid;
 		else if (value > mainChain[mid][0])
 			left = mid + 1;
 		else
 			right = mid - 1;
 	}
 	return left;
 }

void PmergeMe::mergeInsertion(uintVec_t& orgChain, size_t truncatedChainSize, int level)
{

	if (level == _maxLevel)
		return ;

	size_t chainSize = pow(2, level - 1);
	size_t chainSizeToMake = chainSize * 2;
	size_t iteration = orgChain.size() / chainSizeToMake;



	for (size_t i = 0; i < iteration; i++)
	{
		size_t idx = i * chainSizeToMake;
		if (orgChain[idx] < orgChain[idx + chainSize])
			swapChain(orgChain, idx, chainSize);
	}

	//std::cout << "\033[1;31m" << "level : " << level << "\033[0;0m" << std::endl;
	//std::cout << "chainSize : " << chainSize << std::endl;
	//std::cout << "chainSizeToMake : " << chainSizeToMake << std::endl;
	//printUintVec_t("merge", orgChain);
	//std::cout << std::endl;

	mergeInsertion(orgChain, truncatedChainSize - (truncatedChainSize % chainSizeToMake), level + 1);

	//std::cout << std::endl;
	//std::cout << "\033[1;33m" << "level : " << level << "\033[0;0m" << std::endl;

	chainsV_t ret = binaryInsertion(orgChain, truncatedChainSize, chainSize);

	for (size_t i = 0; i < ret.size(); i++)
		for (size_t j = 0; j < chainSize; j++)
			orgChain[i * chainSize + j] = ret[i][j];

	//printUintVec_t("orgChain", orgChain);
	return ;
}

int PmergeMe::getJacobsthal(int n, int pendingCnt)
{
	int jacobsthal = (pow(2, n) - pow(-1, n)) / 3;
	return (jacobsthal <= pendingCnt ? jacobsthal : pendingCnt);
}

//std::deque
void PmergeMe::printUintDeq_t()
{
	std::cout << "Before	: ";
	for (size_t i = 0; i < _unsortedD.size(); i++)
		std::cout << _unsortedD[i] << " ";
	std::cout << std::endl;

	std::cout << "After	: ";
	for (size_t i = 0; i < _sortedD.size(); i++)
		std::cout << _sortedD[i] << " ";
	std::cout << std::endl;
}

void PmergeMe::mergeInsertion(uintDeq_t& orgChain, size_t truncatedChainSize, int level)
{
	if (level == _maxLevel)
		return ;

	size_t chainSize = pow(2, level - 1);
	size_t chainSizeToMake = chainSize * 2;
	size_t iteration = orgChain.size() / chainSizeToMake;



	for (size_t i = 0; i < iteration; i++)
	{
		size_t idx = i * chainSizeToMake;
		if (orgChain[idx] < orgChain[idx + chainSize])
			swapChain(orgChain, idx, chainSize);
	}

	//std::cout << "\033[1;31m" << "level : " << level << "\033[0;0m" << std::endl;
	//std::cout << "chainSize : " << chainSize << std::endl;
	//std::cout << "chainSizeToMake : " << chainSizeToMake << std::endl;
	//printUintVec_t("merge", orgChain);
	//std::cout << std::endl;

	mergeInsertion(orgChain, truncatedChainSize - (truncatedChainSize % chainSizeToMake), level + 1);

	//std::cout << std::endl;
	//std::cout << "\033[1;33m" << "level : " << level << "\033[0;0m" << std::endl;

	chainsD_t ret = binaryInsertion(orgChain, truncatedChainSize, chainSize);

	for (size_t i = 0; i < ret.size(); i++)
		for (size_t j = 0; j < chainSize; j++)
			orgChain[i * chainSize + j] = ret[i][j];

	//printUintVec_t("orgChain", orgChain);
	return ;
}

void PmergeMe::swapChain(uintDeq_t& orgChain, size_t idx, size_t cmpOffset)
{
	unsigned int temp;

	for (size_t i = 0; i < cmpOffset; i++)
	{
		temp = orgChain[idx];
		orgChain[idx] = orgChain[idx + cmpOffset];
		orgChain[idx + cmpOffset] = temp;
		++idx;
	}
}

chainsD_t PmergeMe::binaryInsertion(uintDeq_t& orgChain, size_t truncatedChainSize, size_t chainSize)
{
	chainsD_t mainChain;
	chainsD_t pendingChain;
	size_t totalChainCnt = truncatedChainSize / chainSize;
	size_t remainFlag = totalChainCnt % 2;

	for (size_t i = 0; i < totalChainCnt; i++)
	{
		uintDeq_t temp;
		for (size_t j = 0; j < chainSize; j++)
			temp.push_back(orgChain[i * chainSize + j]);
		if (i % 2 == 1 || (remainFlag && i == totalChainCnt - 1))
			pendingChain.push_back(temp);
		else
			mainChain.push_back(temp);
	}
	
	//printChainsHead("mainChain", mainChain);
	//printChainsHead("pendingChain", pendingChain);

	int remainIdx = pendingChain.size() - 1;

	int beforeJacobsthalIdx = -1;
	int jacobsthalIdx;
	int n = 1;
	while (mainChain.size() != totalChainCnt)
	{
		jacobsthalIdx = getJacobsthal(n, pendingChain.size()) - 1;
		for (int idx = jacobsthalIdx; idx > beforeJacobsthalIdx; idx--)
		{
			int rightLimit;
			if (remainFlag && idx == remainIdx)
				rightLimit = mainChain.size() - 1;
			else
				rightLimit = beforeJacobsthalIdx + jacobsthalIdx;
			int pos = binarySearch(mainChain, pendingChain[idx][0], rightLimit);
			mainChain.insert(mainChain.begin() + pos, pendingChain[idx]);
		}
		beforeJacobsthalIdx = jacobsthalIdx;
		++n;
	}

	//printChainsHead("insertion result", mainChain);
	return mainChain;
}

 int PmergeMe::binarySearch(chainsD_t& mainChain, const unsigned int value, int rightLimit)
 {
 	int left = 0;
 	int right = rightLimit;
 	int mid;

 	while (left <= right)
 	{
 		mid = (left + right) / 2;
		if (value == mainChain[mid][0])
			return mid;
 		else if (value > mainChain[mid][0])
 			left = mid + 1;
 		else
 			right = mid - 1;
 	}
 	return left;
 }