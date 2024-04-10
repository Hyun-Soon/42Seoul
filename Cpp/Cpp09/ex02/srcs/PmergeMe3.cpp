#include "PmergeMe3.hpp"

void printChain_t(std::string msg, chain_t v)
{
	std::cout << msg << " : ";
	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << " ";
	std::cout << std::endl;	
}

PmergeMe::PmergeMe() {}

//TODO :: implement here
//PmergeMe::PmergeMe(const PmergeMe &other)
//{}

//PmergeMe PmergeMe::operator=(const PmergeMe &other)
//{}

PmergeMe::~PmergeMe() {}

void PmergeMe::swapChain(chain_t& orgChain, size_t idx, size_t cmpOffset)
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

 int PmergeMe::binarySearch(chain_t& orgChain, const unsigned int value, int rightLimit, int pendingSize)
 {
 	int left = 0;
 	int right = rightLimit;
 	int mid;

 	std::cout << "\033[1;31m" << "rightlimit : " << rightLimit << "\033[0;0m" << std::endl;
 	while (left <= right)
 	{
 		mid = (left + right) / 2;
		mid -= mid % pendingSize;
 		if (value > orgChain[mid])
 			left = mid + pendingSize;
 		else
 			right = mid - pendingSize;
 	}
 	return left;
 }

void PmergeMe::insertChain(chain_t& mainChain, chain_t& orgChain, int insertPos, int pendingSize, int presentPendingIdx)
{
	printChain_t("here", mainChain);
	if (orgChain.begin() + presentPendingIdx + pendingSize == orgChain.end())
		std::cout << "equal to end" << std::endl;
	std::cout << "inside insertPos : " << insertPos << std::endl;
	mainChain.insert(mainChain.begin() + insertPos, orgChain.begin() + presentPendingIdx, orgChain.begin() + presentPendingIdx + pendingSize);
	for (chain_t::iterator it = orgChain.begin() + presentPendingIdx; it != orgChain.begin() + presentPendingIdx + pendingSize; it++)
		std::cout << "wtf : " << *it << std::endl;
	printChain_t("here2", mainChain);
}

chain_t PmergeMe::binaryInsertion(chain_t& orgChain, int pairedPendingCnt, int remainPendingCnt, size_t pendingSize)
{
	int n = 1;
	int jacobsthal = -1;
	int beforeJacobsthal = 0;
	int totalpendingCnt = pairedPendingCnt + remainPendingCnt;
	chain_t mainChain;

	for (int i = 0; i < pairedPendingCnt; i++)
		for (size_t j = 0; j < pendingSize; j++)
			mainChain.push_back(orgChain[i * pendingSize * 2 + j]);

	chain_t ret = mainChain;
	int rightLimitCnt = 1;
	int insertRemainCnt = 0;
	//int insertCnt = 0;
	while (jacobsthal != totalpendingCnt)
	{
		jacobsthal = getJacobsthal(++n, totalpendingCnt);

		for (int i = jacobsthal; i > beforeJacobsthal; i--)
		{
			int presentPendingIdx;
			if (i <= pairedPendingCnt)
				presentPendingIdx = (i - 1) * pendingSize * 2 + pendingSize; // == 2i * pendingSize - pendingSize; == pendingSize * (2i - 1);
			else
			{
				presentPendingIdx = pairedPendingCnt * 2 * pendingSize + (i - pairedPendingCnt - 1) * pendingSize;
				++insertRemainCnt;
			}
			int rightLimit = (jacobsthal - 1) * pendingSize; // TODO :: find proper rightLimit
			
			printChain_t("mainChain", mainChain);
			int insertPos = binarySearch(mainChain, orgChain[presentPendingIdx], rightLimit, pendingSize);
			std::cout << "insertPos : " << insertPos << std::endl;
			insertChain(ret, orgChain, insertPos, pendingSize, presentPendingIdx);
			printChain_t("ret", ret);
			//insertCnt += pendingSize;
		}
		beforeJacobsthal = jacobsthal;
		++rightLimitCnt;
	}

	return ret;
}

int PmergeMe::getJacobsthal(int n, int pendingCnt)
{	
	int jacobsthal = (pow(2, n) - pow(-1, n)) / 3;
	return (jacobsthal <= pendingCnt ? jacobsthal : pendingCnt);
}

void PmergeMe::mergeInsertion(chain_t& orgChain, int level)
{

    if (level == _maxLevel)
        return ;

    size_t cmpOffset = pow(2, level - 1);
    size_t chainSize = cmpOffset * 2; //만들려는 체인의 사이즈
    size_t iteration = orgChain.size() / chainSize;
	int remainder = orgChain.size() % chainSize;



    for (size_t i = 0; i < iteration; i++)
    {
        size_t idx = i * chainSize;
        if (orgChain[idx] < orgChain[idx + cmpOffset])
            swapChain(orgChain, idx, cmpOffset);
    }

	std::cout << "level : " << level << std::endl;
    printChain_t("merge", orgChain);
	std::cout << std::endl;

	chain_t newChain;
	size_t newChainSize = orgChain.size() - remainder;
	for (size_t i = 0; i < newChainSize; i++)
		newChain.push_back(orgChain[i]);

	mergeInsertion(newChain, level + 1);

	std::cout << std::endl;
	std::cout << "level : " << level << std::endl;
	std::cout << "pendingSize : " << cmpOffset << std::endl;
	for (size_t idx = newChainSize; idx < orgChain.size(); idx++)
		newChain.push_back(orgChain[idx]);
	printChain_t("before insertion", newChain);
	newChain = binaryInsertion(newChain, newChain.size() / chainSize, remainder / cmpOffset, cmpOffset);
	printChain_t("after insertion", newChain);
	orgChain = newChain;
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
	mergeInsertion(_unsorted, 1);


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
