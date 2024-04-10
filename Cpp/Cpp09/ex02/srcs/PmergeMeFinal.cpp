#include "PmergeMeFinal.hpp"

void printUintVec_t(std::string msg, uintVec_t v)
{
	std::cout << msg << " : ";
	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << " ";
	std::cout << std::endl;	
}

void printChainsHead(std::string msg, chains_t c)
{
	std::cout << msg << " : ";
	for (size_t i = 0; i < c.size(); i++)
		std::cout << c[i][0] << " ";
	std::cout << std::endl;	
}

PmergeMe::PmergeMe() {}

//TODO :: implement here
//PmergeMe::PmergeMe(const PmergeMe &other)
//{}

//PmergeMe PmergeMe::operator=(const PmergeMe &other)
//{}

PmergeMe::~PmergeMe() {}

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
	while (ret <= _unsorted.size())
	{
		ret *= 2;
		++cnt;
	}
	return cnt;
}

int PmergeMe::sort(char** elements, size_t elemSize)
{
	if (parseElements(elements, elemSize) == 1)
		return 1;

	_maxLevel = getMaxLevel();
	_sorted = _unsorted;
	mergeInsertion(_sorted, _sorted.size(), 1);

	std::cout << std::endl << std::endl;
	printUintVec_t("before", _unsorted);
	printUintVec_t("after", _sorted);
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

chains_t PmergeMe::binaryInsertion(uintVec_t& orgChain, size_t truncatedChainSize, size_t chainSize)
{
	chains_t mainChain;
	chains_t pendingChain;
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
	
	printChainsHead("mainChain", mainChain);
	printChainsHead("pendingChain", pendingChain);

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
			if (remainFlag && jacobsthalIdx == remainIdx)
				rightLimit = mainChain.size() - 1;
			else
				rightLimit = jacobsthalIdx;
			int pos = binarySearch(mainChain, pendingChain[idx][0], rightLimit);
			mainChain.insert(mainChain.begin() + pos, pendingChain[idx]);

			////debug
			//if (chainSize == 1)
			//{
			//	std::cout << std::endl;
			//	printChainsHead("insertion ING", mainChain);
			//}
		}
		beforeJacobsthalIdx = jacobsthalIdx;
		++n;
	}



	printChainsHead("insertion result", mainChain);
	return mainChain;//
}

 int PmergeMe::binarySearch(chains_t& mainChain, const unsigned int value, int rightLimit)
 {
 	int left = 0;
 	int right = rightLimit;
 	int mid;

 	while (left <= right)
 	{
 		mid = (left + right) / 2;
 		if (value > mainChain[mid][0])
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
	size_t chainSizeToMake = chainSize * 2; //만들려는 체인의 사이즈
	size_t iteration = orgChain.size() / chainSizeToMake;



	for (size_t i = 0; i < iteration; i++)
	{
		size_t idx = i * chainSizeToMake;
		if (orgChain[idx] < orgChain[idx + chainSize])
			swapChain(orgChain, idx, chainSize);
	}

	std::cout << "\033[1;31m" << "level : " << level << "\033[0;0m" << std::endl;
	std::cout << "chainSize : " << chainSize << std::endl;
	std::cout << "chainSizeToMake : " << chainSizeToMake << std::endl;
	printUintVec_t("merge", orgChain);
	std::cout << std::endl;

	mergeInsertion(orgChain, truncatedChainSize - (truncatedChainSize % chainSizeToMake), level + 1);

	std::cout << std::endl;
	std::cout << "\033[1;33m" << "level : " << level << "\033[0;0m" << std::endl;

	chains_t ret = binaryInsertion(orgChain, truncatedChainSize, chainSize);

	for (size_t i = 0; i < ret.size(); i++)
		for (size_t j = 0; j < chainSize; j++)
			orgChain[i * chainSize + j] = ret[i][j];

	//printUintVec_t("orgChain", orgChain);






	return ;
}

int PmergeMe::getJacobsthal(int n, int pendingCnt)
{	// n = 0 -> 0 | n = 1 -> 1
	int jacobsthal = (pow(2, n) - pow(-1, n)) / 3;
	return (jacobsthal <= pendingCnt ? jacobsthal : pendingCnt);
}

